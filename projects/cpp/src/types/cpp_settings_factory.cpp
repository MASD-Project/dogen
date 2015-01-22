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
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/meta_data/reader.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/cpp_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("cpp.cpp_settings_factory"));

const std::string default_source_directory("src");
const std::string default_include_directory("include");
const std::string default_header_file_extension(".hpp");
const std::string default_implementation_file_extension(".cpp");

}

namespace dogen {
namespace cpp {

cpp_settings cpp_settings_factory::create_default_settings() const {
    cpp_settings r;
    r.enabled(true);
    r.split_project(true);
    r.source_directory(default_source_directory);
    r.include_directory(default_include_directory);
    r.header_file_extension(default_header_file_extension);
    r.implementation_file_extension(default_implementation_file_extension);
    r.enable_facet_folders(true);
    r.enable_unique_file_names(true);
    return r;
}

cpp_settings cpp_settings_factory::
build(const boost::property_tree::ptree& meta_data) const {
    cpp_settings r(create_default_settings());

    sml::meta_data::reader reader(meta_data);
    if (reader.has_key(traits::enabled())) {
        const auto value(reader.get(traits::enabled()));
        r.enabled(value == traits::bool_true());
    }

    if (reader.has_key(traits::split_project())) {
        const auto value(reader.get(traits::split_project()));
        r.split_project(value == traits::bool_true());
    }

    if (reader.has_key(traits::source_directory())) {
        const auto value(reader.get(traits::source_directory()));
        r.source_directory(value);
    }

    if (reader.has_key(traits::include_directory())) {
        const auto value(reader.get(traits::include_directory()));
        r.include_directory(value);
    }

    if (reader.has_key(traits::header_file_extension())) {
        const auto value(reader.get(traits::header_file_extension()));
        r.header_file_extension(value);
    }

    if (reader.has_key(traits::implementation_file_extension())) {
        const auto value(reader.get(traits::implementation_file_extension()));
        r.implementation_file_extension(value);
    }

    if (reader.has_key(traits::enable_facet_folders())) {
        const auto value(reader.get(traits::enable_facet_folders()));
        r.enable_facet_folders(value == traits::bool_true());
    }

    if (reader.has_key(traits::enable_unique_file_names())) {
        const auto value(reader.get(traits::enable_unique_file_names()));
        r.enable_unique_file_names(value == traits::bool_true());
    }

    return r;
}

} }
