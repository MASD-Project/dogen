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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/schema/types/field_selector.hpp"
#include "dogen/dynamic/schema/types/repository_selector.hpp"
#include "dogen/dynamic/expansion/types/options_copier.hpp"
#include "dogen/dynamic/expansion/types/expansion_error.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/formatters/workflow.hpp"
#include "dogen/cpp/types/expansion/enabled_flag_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.expansion.enabled_flag_expander"));

const std::string empty_formatter_name("Formatter name is empty.");
const std::string field_definitions_not_found(
    "Could not find expected field definitions for formatter: ");
}


namespace dogen {
namespace cpp {
namespace expansion {

enabled_flag_expander::~enabled_flag_expander() noexcept {}

enabled_flag_expander::field_definitions enabled_flag_expander::
make_field_definitions(const dynamic::schema::repository& rp,
    const dynamic::schema::ownership_hierarchy& oh) const {

    field_definitions r;
    const dynamic::schema::repository_selector s(rp);

    const auto fmtn(oh.formatter_name());
    r.formatter_enabled = s.select_field_by_name(fmtn, traits::enabled());

    const auto fctn(oh.facet_name());
    r.facet_enabled = s.select_field_by_name(fctn, traits::enabled());

    return r;
}

std::unordered_map<std::string, enabled_flag_expander::field_definitions>
enabled_flag_expander::make_field_definitions(
    const dynamic::schema::repository& rp,
    const formatters::container& fc) const {
    std::unordered_map<std::string, field_definitions> r;

    for (const auto f : fc.all_formatters()) {
        const auto& oh(f->ownership_hierarchy());
        if (oh.formatter_name().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_formatter_name;

            using dynamic::expansion::expansion_error;
            BOOST_THROW_EXCEPTION(expansion_error(empty_formatter_name));
        }
        r[oh.formatter_name()] = make_field_definitions(rp, oh);
    }

    return r;
}

std::string enabled_flag_expander::name() const {
    static std::string name("cpp.expansion.enabled_flag_expander");
    return name;
}

const std::forward_list<std::string>& enabled_flag_expander::
dependencies() const {
    using namespace dynamic::expansion;
    static std::forward_list<std::string> r { options_copier::static_name() };
    return r;
}

void enabled_flag_expander::
setup(const dynamic::expansion::expansion_context& ec) {
    formatters::workflow::registrar().validate();
    const auto& fc(formatters::workflow::registrar().formatter_container());
    const auto& rp(ec.repository());
    field_definitions_ = make_field_definitions(rp, fc);
}

void enabled_flag_expander::expand(const sml::qname& /*qn*/,
    const dynamic::schema::scope_types& /*st*/,
    dynamic::schema::object& o) const {

    for (const auto& pair : field_definitions_) {
        const auto& fd(pair.second);
        const dynamic::schema::field_selector fs(o);

        // formatter field has been set and so takes precedence.
        // nothing to do here.
        if (fs.has_field(fd.formatter_enabled)) {
            BOOST_LOG_SEV(lg, debug) << "Field overridden: "
                                     << fd.formatter_enabled.name().qualified();
            continue;
        }

        // formatter field has not been set; if facet field has been
        // set, take formatter's field value from it.
        if (fs.has_field(fd.facet_enabled)) {
            const auto fn(fd.formatter_enabled.name().qualified());
            BOOST_LOG_SEV(lg, debug) << "Copying facet field: '"
                                     << fd.facet_enabled.name().qualified()
                                     << "' to '" << fn << "'";

            o.fields()[fn] = fs.get_field(fd.facet_enabled);
            continue;
        }
    }
}

} } }
