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
#include "dogen/dynamic/schema/types/field_selector.hpp"
#include "dogen/cpp/types/settings/field_definitions.hpp"
#include "dogen/cpp/types/settings/cpp_settings_factory.hpp"

namespace dogen {
namespace cpp {
namespace settings {

cpp_settings_factory::cpp_settings_factory()
    : default_settings_(create_default_settings()) { }

cpp_settings cpp_settings_factory::create_default_settings() const {
    using namespace dynamic::schema;
    using fd = dogen::cpp::settings::field_definitions;

    cpp_settings r;
    r.enabled(field_selector::get_boolean_content(
            *fd::enabled().default_value()));
    r.split_project(field_selector::get_boolean_content(
            *fd::split_project().default_value()));
    r.include_directory_name(field_selector::get_text_content(
            *fd::include_directory_name().default_value()));
    r.source_directory_name(field_selector::get_text_content(
            *fd::source_directory_name().default_value()));
    r.split_project(field_selector::get_boolean_content(
            *fd::split_project().default_value()));
    r.header_file_extension(field_selector::get_text_content(
            *fd::header_file_extension().default_value()));
    r.implementation_file_extension(field_selector::get_text_content(
            *fd::implementation_file_extension().default_value()));
    r.enable_facet_folders(field_selector::get_boolean_content(
            *fd::enable_facet_folders().default_value()));
    r.enable_unique_file_names(field_selector::get_boolean_content(
            *fd::enable_unique_file_names().default_value()));
    return r;
}

void cpp_settings_factory::
populate(const dynamic::schema::object& o, cpp_settings& s) const {
    using namespace dynamic::schema;
    using fd = field_definitions;
    const field_selector fs(o);

    if (fs.has_field(fd::enabled()))
        s.enabled(fs.get_boolean_content(fd::enabled()));

    if (fs.has_field(fd::split_project()))
        s.enabled(fs.get_boolean_content(fd::split_project()));

    if (fs.has_field(fd::source_directory_name()))
        s.source_directory_name(
            fs.get_text_content(fd::source_directory_name()));

    if (fs.has_field(fd::include_directory_name()))
        s.include_directory_name(
            fs.get_text_content(fd::include_directory_name()));

    if (fs.has_field(fd::header_file_extension()))
        s.header_file_extension(
            fs.get_text_content(fd::header_file_extension()));

    if (fs.has_field(fd::implementation_file_extension()))
        s.implementation_file_extension(
            fs.get_text_content(fd::implementation_file_extension()));

    if (fs.has_field(fd::enable_facet_folders()))
        s.enable_facet_folders(
            fs.get_boolean_content(fd::enable_facet_folders()));

    if (fs.has_field(fd::enable_unique_file_names()))
        s.enable_unique_file_names(
            fs.get_boolean_content(fd::enable_unique_file_names()));
}

void cpp_settings_factory::
populate(const config::cpp_options& co, cpp_settings& s) const {
    s.project_directory_path(co.project_directory_path());
    s.source_directory_path(co.source_directory_path());
    s.include_directory_path(co.include_directory_path());
}

cpp_settings cpp_settings_factory::
make(const config::cpp_options& co, const dynamic::schema::object& o) const {
    cpp_settings r(default_settings_);
    populate (o, r);
    populate (co, r);
    return r;
}

} } }
