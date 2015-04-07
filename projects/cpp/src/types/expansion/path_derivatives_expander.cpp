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
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/dynamic/schema/types/field_instance_factory.hpp"
#include "dogen/dynamic/schema/types/field_selector.hpp"
#include "dogen/dynamic/expansion/types/options_copier.hpp"
#include "dogen/dynamic/expansion/types/expansion_error.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/formatters/workflow.hpp"
#include "dogen/cpp/types/expansion/path_derivatives_workflow.hpp"
#include "dogen/cpp/types/expansion/path_derivatives_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.expansion.path_derivatives_expander"));

const std::string no_fields_for_formatter(
    "Could not find any fields for formatter: ");
const std::string field_definition_not_found(
    "Could not find expected field definition: ");
const std::string field_definitions_not_found(
    "Could not find expected field definitions for formatter: ");
const std::string missing_path_settings(
    "Could not find any path settings for formatter: ");
const std::string no_path_derivatives_for_qn(
    "Could not find any path derivatives for qname: ");

}

namespace dogen {
namespace cpp {
namespace expansion {

path_derivatives_expander::path_derivatives_expander() : requires_file_path_expansion_(false) {}
path_derivatives_expander::~path_derivatives_expander() noexcept {}

path_derivatives_expander::field_definitions
path_derivatives_expander::field_definitions_for_formatter_name(
    const dynamic::schema::repository& rp,
    const std::string& formatter_name) const {

    const auto i(rp.field_definitions_by_formatter_name().find(formatter_name));
    if (i == rp.field_definitions_by_formatter_name().end()) {
        BOOST_LOG_SEV(lg, error) << no_fields_for_formatter << formatter_name;
        BOOST_THROW_EXCEPTION(dynamic::expansion::expansion_error(
                no_fields_for_formatter + formatter_name));
    }

    field_definitions r;
    bool found_file_path(false);
    for (const auto fd : i->second) {
        if (fd.name().simple() == traits::file_path()) {
            r.file_path = fd;
            found_file_path = true;
        } else if (fd.name().simple() == traits::inclusion_directive())
            r.inclusion_directive = fd;
        else if (fd.name().simple() == traits::header_guard())
            r.header_guard = fd;
        // else if (fd.name().simple() == cpp::traits::inclusion_dependency())
        //     r.inclusion_dependency = fd;
    }

    if (!found_file_path) {
        BOOST_LOG_SEV(lg, error) << field_definition_not_found
                                 << traits::file_path() << " for formatter: "
                                 << formatter_name;
        BOOST_THROW_EXCEPTION(
            dynamic::expansion::expansion_error(
                field_definition_not_found + traits::file_path()));
    }

    if (!r.inclusion_directive) {
        BOOST_LOG_SEV(lg, debug) << "Formatter does not support inclusion: "
                                 << formatter_name;
    }

    if (!r.header_guard) {
        BOOST_LOG_SEV(lg, debug) << "Formatter does not support header guards: "
                                 << formatter_name;
    }

    // if (!r.inclusion_dependency) {
    //     BOOST_LOG_SEV(lg, debug)
    //         << "Formatter does not support inclusion dependencies: "
    //         << formatter_name;
    // }

    return r;
}

std::unordered_map<std::string, path_derivatives_expander::field_definitions>
path_derivatives_expander::
setup_field_definitions(const dynamic::schema::repository& rp,
    const formatters::container& fc) const {

    std::unordered_map<std::string, field_definitions> r;
    for (const auto& f : fc.all_formatters()) {
        const auto oh(f->ownership_hierarchy());
        const auto& fn(oh.formatter_name());
        r[fn] = field_definitions_for_formatter_name(rp, fn);
    }
    return r;
}

void path_derivatives_expander::expand_file_path(const field_definitions& fd,
    const expansion::path_derivatives& pd,
    dynamic::schema::object& o) const {

    if (!requires_file_path_expansion_)
        return;

    dynamic::schema::field_instance_factory f;
    const auto& fp(pd.file_path());
    o.fields()[fd.file_path.name().qualified()] = f.make_text(fp);
}

void path_derivatives_expander::
expand_header_guard(const std::string& formatter_name,
    const field_definitions& fd, const path_derivatives& pd,
    dynamic::schema::object& o) const {

    const bool header_guard_not_supported(!fd.header_guard);
    if (header_guard_not_supported)
        return;

    using namespace dynamic::schema;
    const field_selector fs(o);
    const bool override_found(fs.has_field(*fd.header_guard));
    if (override_found) {
        BOOST_LOG_SEV(lg, debug) << "Header guard has been overriden: "
                                 << formatter_name;
        return;
    }

    dynamic::schema::field_instance_factory f;
    const auto& n(fd.header_guard->name().qualified());
    o.fields()[n] = f.make_text(pd.header_guard());
}

void path_derivatives_expander::
expand_include_directive(const std::string& formatter_name,
    const field_definitions& fd, const path_derivatives& pd,
    dynamic::schema::object& o) const {

    const bool inclusion_directive_not_supported(!fd.inclusion_directive);
    if (inclusion_directive_not_supported)
        return;

    using namespace dynamic::schema;
    const field_selector fs(o);
    const bool override_found(fs.has_field(*fd.inclusion_directive));
    if (override_found) {
        BOOST_LOG_SEV(lg, debug) << "Include directive has been overriden: "
                                 << formatter_name;
        return;
    }

    dynamic::schema::field_instance_factory f;
    const auto n(fd.inclusion_directive->name().qualified());
    o.fields()[n] = f.make_text(pd.inclusion_directive());
}

// void path_derivatives_expander::
// expand_include_dependencies(const std::string& formatter_name,
//     const field_definitions& fd, const path_derivatives& pd,
//     dynamic::schema::object& o) const {
//     const bool inclusion_dependencies_not_supported(!fd.inclusion_dependency);
//     if (inclusion_dependencies_not_supported)
//         return;

//     using namespace dynamic::schema;
//     const field_selector fs(o);
//     const bool override_found(fs.has_field(*fd.inclusion_dependency));
//     if (override_found) {
//         BOOST_LOG_SEV(lg, debug) << "Inclusion dependency has been overriden: "
//                                  << formatter_name;
//         return;
//     }

//     dynamic::schema::field_instance_factory f;
//     const auto n(fd.inclusion_dependency->name().qualified());
//     o.fields()[n] = f.make_text_collection(ei.inclusion_dependencies());
// }

std::string path_derivatives_expander::name() const {
    static std::string name("cpp.expansion.expander");
    return name;
}

const std::forward_list<std::string>&
path_derivatives_expander::dependencies() const {
    using namespace dynamic::expansion;
    static std::forward_list<std::string> r { options_copier::static_name() };
    return r;
}

void path_derivatives_expander::
setup(const dynamic::expansion::expansion_context& ec) {
    requires_file_path_expansion_ = ec.model().is_target();

    formatters::workflow::registrar().validate();
    const auto& fc(formatters::workflow::registrar().formatter_container());
    const auto& rp(ec.repository());
    field_definitions_ = setup_field_definitions(rp, fc);

    const auto& m(ec.model());
    const auto& opts(ec.cpp_options());
    path_derivatives_workflow w;
    path_derivatives_ = w.execute(opts, rp, m);
}

void path_derivatives_expander::
expand(const sml::qname& qn, const dynamic::schema::scope_types& /*st*/,
    dynamic::schema::object& o) const {
    const auto n(sml::string_converter::convert(qn));
    BOOST_LOG_SEV(lg, debug) << "Performing expansion for: " << n;

    const auto i(path_derivatives_.find(qn));
    if (i == path_derivatives_.end()) {
        BOOST_LOG_SEV(lg, error) << no_path_derivatives_for_qn << n;
        BOOST_THROW_EXCEPTION(dynamic::expansion::expansion_error(
                no_path_derivatives_for_qn + n));
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
        const auto& pd(pair.second);
        expand_file_path(fd, pd, o);
        expand_header_guard(formatter_name, fd, pd, o);
        expand_include_directive(formatter_name, fd, pd, o);
    }
    BOOST_LOG_SEV(lg, debug) << "Finished performing expansion for: " << n;
}

} } }
