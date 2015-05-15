/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/schema/types/field_selector.hpp"
#include "dogen/dynamic/schema/types/repository_selector.hpp"
#include "dogen/dynamic/schema/types/field_instance_factory.hpp"
#include "dogen/dynamic/expansion/types/expansion_error.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/formatters/workflow.hpp"
#include "dogen/cpp/types/formattables/path_derivatives_expander.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_repository_factory.hpp"
#include "dogen/cpp/types/formattables/inclusion_dependencies_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "cpp.formattables.inclusion_dependencies_expander"));

const std::string field_definition_not_found(
    "Could not find expected field definition: ");
const std::string field_definitions_not_found(
    "Could not find expected field definitions for formatter: ");
const std::string no_inclusion_dependencies_for_qn(
    "Could not find any inclusion dependencies for qname: ");

}

namespace dogen {
namespace cpp {
namespace formattables {

inclusion_dependencies_expander::~inclusion_dependencies_expander() noexcept {}

inclusion_dependencies_expander::field_definitions
inclusion_dependencies_expander::
field_definitions_for_formatter_name(const dynamic::schema::repository& rp,
    const std::string& formatter_name) const {

    field_definitions r;
    const auto& fn(formatter_name);
    const auto& id(cpp::traits::inclusion_dependency());
    const dynamic::schema::repository_selector s(rp);
    r.inclusion_dependency = s.try_select_field_by_name(fn, id);

    if (!r.inclusion_dependency) {
        BOOST_LOG_SEV(lg, debug)
            << "Formatter does not support inclusion dependencies: "
            << formatter_name;
    }

    return r;
}

std::unordered_map<
    std::string,
    inclusion_dependencies_expander::field_definitions
    >
inclusion_dependencies_expander::setup_field_definitions(
    const dynamic::schema::repository& rp,
    const formatters::container& fc) const {
    std::unordered_map<std::string, field_definitions> r;
    for (const auto& f : fc.all_formatters()) {
        const auto oh(f->ownership_hierarchy());
        const auto& fn(oh.formatter_name());
        r[fn] = field_definitions_for_formatter_name(rp, fn);
    }
    return r;
}

void inclusion_dependencies_expander::
expand_inclusion_dependencies(const std::string& formatter_name,
    const field_definitions& fd, const std::list<std::string>& deps,
    dynamic::schema::object& o) const {

    const bool inclusion_dependency_not_supported(!fd.inclusion_dependency);
    if (inclusion_dependency_not_supported)
        return;

    using namespace dynamic::schema;
    const field_selector fs(o);
    const bool override_found(fs.has_field(*fd.inclusion_dependency));
    if (override_found) {
        // FIXME: we need to merge the containers if overriden.
        BOOST_LOG_SEV(lg, debug) << "Inclusion dependency has been overriden: "
                                 << formatter_name;
        return;
    }

    dynamic::schema::field_instance_factory f;
    const auto& n(fd.inclusion_dependency->name().qualified());
    o.fields()[n] = f.make_text_collection(deps);
}

std::string inclusion_dependencies_expander::name() const {
    static std::string name("cpp.formattables.inclusion_dependencies_expander");
    return name;
}

const std::forward_list<std::string>&
inclusion_dependencies_expander::dependencies() const {
    using namespace dynamic::expansion;
    static std::forward_list<std::string> r {
        path_derivatives_expander::static_name()
    };
    return r;
}

void inclusion_dependencies_expander::
setup(const dynamic::expansion::expansion_context& ec) {
    const auto& fc(formatters::workflow::registrar().formatter_container());
    const auto& rp(ec.repository());
    field_definitions_ = setup_field_definitions(rp, fc);
    inclusion_dependencies_repository_factory f;
    const auto id_rp(f.execute(rp, fc, ec.model()));
    inclusion_dependencies_ = id_rp.inclusion_dependencies_by_qname();
}

void inclusion_dependencies_expander::expand(
    const sml::qname& qn, const dynamic::schema::scope_types& /*st*/,
    dynamic::schema::object& o) const {

    const auto n(sml::string_converter::convert(qn));
    BOOST_LOG_SEV(lg, debug) << "Performing expansion for: " << n;

    const auto i(inclusion_dependencies_.find(qn));
    if (i == inclusion_dependencies_.end() || i->second.empty()) {
        BOOST_LOG_SEV(lg, warn) << no_inclusion_dependencies_for_qn << n;
        return;
    }

    for (const auto& pair : i->second) {
        const auto& formatter_name(pair.first);
        const auto j(field_definitions_.find(formatter_name));
        if (j == field_definitions_.end()) {
            BOOST_LOG_SEV(lg, error) << field_definitions_not_found
                                     << "'" << formatter_name << "'";
            BOOST_THROW_EXCEPTION(dynamic::expansion::expansion_error(
                    field_definition_not_found + formatter_name));
        }

        const auto& fd(j->second);
        const auto& deps(pair.second);
        expand_inclusion_dependencies(formatter_name, fd, deps, o);
    }
    BOOST_LOG_SEV(lg, debug) << "Finished performing expansion for: " << n;
}

} } }
