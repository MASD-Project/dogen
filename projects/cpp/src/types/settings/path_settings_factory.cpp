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
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/formatters/file_types.hpp"
#include "dogen/cpp/types/formatters/workflow.hpp"
#include "dogen/cpp/types/settings/building_error.hpp"
#include "dogen/cpp/types/settings/path_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "cpp.settings.path_settings_factory"));

const std::string multiple_fields(
    "Facet has multiple fields with the same name: ");
const std::string missing_expected_field("Could not find expected field: ");
const std::string no_fields_for_facet("Could not find any fields for facet: ");
const std::string no_fields_for_formatter(
    "Could not find any fields for formatter: ");
const std::string field_not_found("Could not find expected field: ");
const std::string field_definition_not_found(
    "Could not find expected field definition: ");
const std::string inclusion_not_supported(
    "Attempting to get inclusion properties for a formatter "
    "that does not support them: ");

}

namespace dogen {
namespace cpp {
namespace settings {

path_settings_factory::
path_settings_factory(const config::cpp_options& o,
    const dynamic::schema::repository& rp)
    : options_(o), formatter_properties_(make_formatter_properties(rp)) { }

dynamic::schema::field_definition path_settings_factory::
field_definition_for_name(const dynamic::schema::repository& rp,
    const std::string& field_name) const {
    const auto i(rp.field_definitions_by_name().find(field_name));
    if (i == rp.field_definitions_by_name().end()) {
        BOOST_LOG_SEV(lg, error) << field_not_found << field_name;
        BOOST_THROW_EXCEPTION(building_error(field_not_found + field_name));
    }
    return i->second;
}

void path_settings_factory::setup_top_level_fields(
    const dynamic::schema::repository& rp, formatter_properties& fp) const {

    fp.include_directory_name =
        field_definition_for_name(rp, traits::include_directory_name());

    fp.source_directory_name =
        field_definition_for_name(rp, traits::source_directory_name());

    fp.header_file_extension =
        field_definition_for_name(rp, traits::header_file_extension());

    fp.implementation_file_extension =
        field_definition_for_name(rp, traits::implementation_file_extension());
}

void path_settings_factory::setup_facet_fields(
    const dynamic::schema::repository& rp,
    const std::string& facet_name,
    path_settings_factory::formatter_properties& fp) const {

    const auto i(rp.field_definitions_by_facet_name().find(facet_name));
    if (i == rp.field_definitions_by_facet_name().end()) {
        BOOST_LOG_SEV(lg, error) << no_fields_for_facet << facet_name;
        BOOST_THROW_EXCEPTION(building_error(no_fields_for_facet + facet_name));
    }

    bool found_directory(false), found_postfix(false);
    for (const auto fd : i->second) {
        if (fd.name().simple() == traits::directory()) {
            fp.facet_directory = fd;
            found_directory = true;
        } else if (fd.name().simple() == traits::postfix()) {
            fp.facet_postfix = fd;
            found_postfix = true;
        }
    }

    if (!found_directory) {
        BOOST_LOG_SEV(lg, error) << field_definition_not_found << " '"
                                 << traits::directory() << "' for facet: "
                                 << facet_name;
        BOOST_THROW_EXCEPTION(
            building_error(field_definition_not_found + traits::directory()));
    }

    if (!found_postfix) {
        BOOST_LOG_SEV(lg, error) << field_definition_not_found << " '"
                                 << traits::postfix() << "' for facet: "
                                 << facet_name;
        BOOST_THROW_EXCEPTION(
            building_error(field_definition_not_found + traits::directory()));
    }
}

void path_settings_factory::setup_formatter_fields(
    const dynamic::schema::repository& rp,
    const std::string& formatter_name,
    path_settings_factory::formatter_properties& fp) const {

    const auto i(rp.field_definitions_by_formatter_name().find(formatter_name));
    if (i == rp.field_definitions_by_facet_name().end()) {
        BOOST_LOG_SEV(lg, error) << no_fields_for_formatter << formatter_name;
        BOOST_THROW_EXCEPTION(
            building_error(no_fields_for_formatter + formatter_name));
    }

    bool found_postfix(false);

    for (const auto fd : i->second) {
        if (fd.name().simple() == traits::postfix()) {
            fp.formatter_postfix = fd;
            found_postfix = true;
        }
    }

    if (!found_postfix) {
        BOOST_LOG_SEV(lg, error) << field_definition_not_found << " '"
                                 << traits::postfix() << "' for formatter: "
                                 << formatter_name;
        BOOST_THROW_EXCEPTION(
            building_error(field_definition_not_found + traits::postfix()));
    }
}

path_settings_factory::formatter_properties
path_settings_factory::make_formatter_properties(
    const dynamic::schema::repository& rp,
    const formatters::formatter_interface& f) const {

    formatter_properties r;
    r.file_type = f.file_type();
    r.formatter_name = f.formatter_name();
    setup_top_level_fields(rp, r);
    setup_facet_fields(rp, f.facet_name(), r);
    setup_formatter_fields(rp, f.formatter_name(), r);

    return r;
}

std::unordered_map<std::string, path_settings_factory::formatter_properties>
path_settings_factory::make_formatter_properties(
    const dynamic::schema::repository& rp) const {
    const auto& c(formatters::workflow::registrar().formatter_container());
    std::unordered_map<std::string, formatter_properties> r;

    for (const auto& f : c.all_formatters())
        r[f->formatter_name()] = make_formatter_properties(rp, *f);

    return r;
}

path_settings path_settings_factory::
create_settings_for_formatter(const formatter_properties& fp,
    const dynamic::schema::object& o) const {

    path_settings r;
    r.file_type(fp.file_type);

    r.split_project(options_.split_project());
    r.project_directory_path(options_.project_directory_path());
    r.source_directory_path(options_.source_directory_path());
    r.include_directory_path(options_.include_directory_path());

    using namespace dynamic::schema;
    const field_selector fs(o);

    r.facet_directory(fs.get_text_content_or_default(fp.facet_directory));
    r.facet_postfix(fs.get_text_content_or_default(fp.facet_postfix));
    r.formatter_postfix(fs.get_text_content_or_default(fp.formatter_postfix));

    if (fp.file_type == formatters::file_types::cpp_header) {
        r.extension(fs.get_text_content_or_default(fp.header_file_extension));
    } else if (fp.file_type == formatters::file_types::cpp_header) {
        r.extension(fs.get_text_content_or_default(
                fp.implementation_file_extension));
    }

    r.include_directory_name(
        fs.get_text_content_or_default(fp.include_directory_name));
    r.source_directory_name(
        fs.get_text_content_or_default(fp.source_directory_name));

    return r;
}

std::unordered_map<std::string, path_settings> path_settings_factory::
make(const dynamic::schema::object& o) const {
    std::unordered_map<std::string, path_settings> r;
    for (const auto& pair : formatter_properties_) {
        const auto& fp(pair.second);
        const auto s(create_settings_for_formatter(fp, o));
        r.insert(std::make_pair(fp.formatter_name, s));
    }
    return r;
}

} } }
