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
#include "dogen/dynamic/types/content_extensions.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/settings/building_error.hpp"
#include "dogen/cpp/types/settings/formatter_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("cpp.settings.formatter_settings_factory"));

const std::string multiple_fields(
    "Facet has multiple fields with the same name: ");
const std::string no_default_value(
    "Field does not have a default value: ");

}

namespace dogen {
namespace cpp {
namespace settings {

formatter_settings formatter_settings_factory::
create_settings_for_formatter(
    const std::forward_list<dynamic::field_definition>& formatter_fields,
    const dynamic::object& o) const {
    using namespace dynamic;

    formatter_settings r;
    bool found_enabled(false), found_postfix(false);
    const auto& enabled_trait(traits::formatter::enabled());
    const auto& postfix_trait(traits::formatter::additional_postfix());

    for (const auto fd : formatter_fields) {
        using namespace dynamic;
        if (fd.name().simple() == enabled_trait) {
            if (found_enabled) {
                const auto& n(fd.name().qualified());
                BOOST_LOG_SEV(lg, error) << multiple_fields << n;
                BOOST_THROW_EXCEPTION(building_error(multiple_fields + n));
            }
            found_enabled = true;

            if (has_field(o, fd))
                r.enabled(get_boolean_content(o, fd));
            else {
                if (!fd.default_value()) {
                    const auto& n(fd.name().qualified());
                    BOOST_LOG_SEV(lg, error) << no_default_value << n;
                    BOOST_THROW_EXCEPTION(building_error(no_default_value + n));
                }
                r.enabled(get_boolean_content(*fd.default_value()));
            }
        } else if (fd.name().simple() == postfix_trait) {
            if (found_postfix) {
                const auto& n(fd.name().qualified());
                BOOST_LOG_SEV(lg, error) << multiple_fields << n;
                BOOST_THROW_EXCEPTION(building_error(multiple_fields + n));
            }
            found_postfix = true;

            if (has_field(o, fd))
                r.postfix(get_text_content(o, fd));
            else {
                if (!fd.default_value()) {
                    const auto& n(fd.name().qualified());
                    BOOST_LOG_SEV(lg, error) << no_default_value << n;
                    BOOST_THROW_EXCEPTION(building_error(no_default_value + n));
                }
                r.postfix(get_text_content(*fd.default_value()));
            }
        }
    }

    return r;
}

std::unordered_map<std::string, formatter_settings>
formatter_settings_factory::build(const std::unordered_map<std::string,
    std::forward_list<dynamic::field_definition>
    >& field_definitions_by_formatter_name,
    const dynamic::object& o) const {

    std::unordered_map<std::string, formatter_settings> r;
    for (const auto pair : field_definitions_by_formatter_name) {
        const auto& formatter_name(pair.first);
        const auto& formatter_fields(pair.second);
        const auto s(create_settings_for_formatter(formatter_fields, o));
        r.insert(std::make_pair(formatter_name, s));
    }
    return r;
}

} } }
