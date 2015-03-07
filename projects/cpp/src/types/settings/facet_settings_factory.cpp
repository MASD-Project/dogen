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
#include "dogen/dynamic/schema/types/content_extensions.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/settings/building_error.hpp"
#include "dogen/cpp/types/settings/facet_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("cpp.settings.facet_settings_factory"));

const std::string multiple_fields(
    "Facet has multiple fields with the same name: ");
const std::string no_default_value("Field does not have a default value: ");
const std::string missing_expected_field("Could not find expected field: ");

}

namespace dogen {
namespace cpp {
namespace settings {

void facet_settings_factory::
ensure_field_is_present(const bool found, const std::string& name) const {
    if (found)
        return;

    BOOST_LOG_SEV(lg, error) << missing_expected_field << name;
    BOOST_THROW_EXCEPTION(building_error(missing_expected_field + name));
}

global_facet_settings facet_settings_factory::create_global_settings_for_facet(
    const std::forward_list<dynamic::schema::field_definition>& facet_fields,
    const dynamic::schema::object& o) const {

    global_facet_settings r;
    bool found_enabled(false), found_directory(false), found_postfix(false),
        found_integrated_facet(false);
    const auto& enabled_trait(traits::facet::enabled());
    const auto& directory_trait(traits::facet::directory());
    const auto& postfix_trait(traits::facet::postfix());
    const auto& integrated_facet_trait(traits::facet::integrated_facet());

    for (const auto& fd : facet_fields) {
        using namespace dynamic::schema;
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
        } else if (fd.name().simple() == directory_trait) {
            if (found_directory) {
                const auto& n(fd.name().qualified());
                BOOST_LOG_SEV(lg, error) << multiple_fields << n;
                BOOST_THROW_EXCEPTION(building_error(multiple_fields + n));
            }
            found_directory = true;

            if (has_field(o, fd))
                r.directory(get_text_content(o, fd));
            else {
                if (!fd.default_value()) {
                    const auto& n(fd.name().qualified());
                    BOOST_LOG_SEV(lg, error) << no_default_value << n;
                    BOOST_THROW_EXCEPTION(building_error(no_default_value + n));
                }
                r.directory(get_text_content(*fd.default_value()));
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
        } else if (fd.name().simple() == integrated_facet_trait) {
            if (found_integrated_facet) {
                const auto& n(fd.name().qualified());
                BOOST_LOG_SEV(lg, error) << multiple_fields << n;
                BOOST_THROW_EXCEPTION(building_error(multiple_fields + n));
            }
            found_integrated_facet = true;
            if (has_field(o, fd)) {
                for (const auto s : get_text_collection_content(o, fd))
                    r.integrated_facets().insert(s);
            }
        }
    }

    ensure_field_is_present(found_enabled, enabled_trait);
    ensure_field_is_present(found_directory, directory_trait);
    ensure_field_is_present(found_postfix, postfix_trait);

    return r;
}

boost::optional<local_facet_settings> facet_settings_factory::
create_local_settings_for_facet(
    const std::forward_list<dynamic::schema::field_definition>& facet_fields,
    const dynamic::schema::object& o) const {

    local_facet_settings r;
    bool found_supported(false);
    bool found_any_field(false);
    const auto& supported_trait(traits::facet::supported());

    for (const auto fd : facet_fields) {
        using namespace dynamic::schema;
        if (fd.name().simple() == supported_trait) {
            if (found_supported) {
                const auto& n(fd.name().qualified());
                BOOST_LOG_SEV(lg, error) << multiple_fields << n;
                BOOST_THROW_EXCEPTION(building_error(multiple_fields + n));
            }
            found_supported = true;

            if (has_field(o, fd)) {
                r.supported(get_boolean_content(o, fd));
                found_any_field = true;
            } else {
                if (!fd.default_value()) {
                    const auto& n(fd.name().qualified());
                    BOOST_LOG_SEV(lg, error) << no_default_value << n;
                    BOOST_THROW_EXCEPTION(building_error(no_default_value + n));
                }
                r.supported(get_boolean_content(*fd.default_value()));
            }
        }

        if (found_any_field)
            return r;

        return boost::optional<local_facet_settings>();
    }

    return r;
}

std::unordered_map<std::string, global_facet_settings>
facet_settings_factory::make_global_settings(
    const std::unordered_map<std::string,
    std::forward_list<dynamic::schema::field_definition>>&
    field_definitions_by_facet_name,
    const dynamic::schema::object& o) const {

    std::unordered_map<std::string, global_facet_settings> r;
    for (const auto pair : field_definitions_by_facet_name) {
        const auto& facet_name(pair.first);
        const auto& facet_fields(pair.second);
        const auto s(create_global_settings_for_facet(facet_fields, o));
        r.insert(std::make_pair(facet_name, s));
    }
    return r;
}

std::unordered_map<std::string, local_facet_settings>
facet_settings_factory::make_local_settings(
    const std::unordered_map<std::string,
    std::forward_list<dynamic::schema::field_definition>>&
    field_definitions_by_facet_name,
    const dynamic::schema::object& o) const {

    std::unordered_map<std::string, local_facet_settings> r;
    for (const auto pair : field_definitions_by_facet_name) {
        const auto& facet_name(pair.first);
        const auto& facet_fields(pair.second);
        const auto s(create_local_settings_for_facet(facet_fields, o));
        if (s)
            r.insert(std::make_pair(facet_name, *s));
    }
    return r;
}

} } }
