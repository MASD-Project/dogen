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
#include "dogen/dynamic/types/content_extensions.hpp"
#include "dogen/cpp/types/settings/field_definitions.hpp"
#include "dogen/cpp/types/settings/cpp_settings_factory.hpp"

namespace dogen {
namespace cpp {
namespace settings {

cpp_settings cpp_settings_factory::create_default_settings() const {
    using namespace dynamic;
    using fd = dogen::cpp::settings::field_definitions;

    cpp_settings r;
    r.enabled(get_boolean_content(*fd::enabled().default_value()));
    r.split_project(get_boolean_content(*fd::split_project().default_value()));
    r.source_directory(
        get_text_content(*fd::source_directory().default_value()));
    r.include_directory(
        get_text_content(*fd::include_directory().default_value()));
    r.header_file_extension(
        get_text_content(*fd::header_file_extension().default_value()));
    r.implementation_file_extension(
        get_text_content(*fd::implementation_file_extension().default_value()));
    r.enable_facet_folders(
        get_boolean_content(*fd::enable_facet_folders().default_value()));
    r.enable_unique_file_names(
        get_boolean_content(*fd::enable_unique_file_names().default_value()));
    return r;
}

cpp_settings_factory::cpp_settings_factory()
    : default_settings_(create_default_settings()) { }

cpp_settings cpp_settings_factory::make(const dynamic::object& o) const {
    cpp_settings r(default_settings_);

    using namespace dynamic;
    using fd = field_definitions;

    if (has_field(o, fd::enabled()))
        r.enabled(get_boolean_content(o, fd::enabled()));

    if (has_field(o, fd::split_project()))
        r.enabled(get_boolean_content(o, fd::split_project()));

    if (has_field(o, fd::source_directory()))
        r.source_directory(get_text_content(o, fd::source_directory()));

    if (has_field(o, fd::include_directory()))
        r.include_directory(get_text_content(o, fd::include_directory()));

    if (has_field(o, fd::header_file_extension()))
        r.header_file_extension(
            get_text_content(o, fd::header_file_extension()));

    if (has_field(o, fd::implementation_file_extension()))
        r.implementation_file_extension(
            get_text_content(o, fd::implementation_file_extension()));

    if (has_field(o, fd::enable_facet_folders()))
        r.enable_facet_folders(
            get_boolean_content(o, fd::enable_facet_folders()));

    if (has_field(o, fd::enable_unique_file_names()))
        r.enable_unique_file_names(
            get_boolean_content(o, fd::enable_unique_file_names()));

    return r;
}

} } }
