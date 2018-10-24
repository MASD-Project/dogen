/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include "dogen.utility/test_data/resolver.hpp"
#include "dogen.utility/test_data/validating_resolver.hpp"
#include "dogen.utility/test_data/external_json.hpp"

using boost::filesystem::path;

namespace {

path data_set("external.json");
path input("external.json/input");
path input_cpp_model_json("external.json/input/cpp_model.json");
path input_boost_model_json("external.json/input/boost_model.json");
path input_std_model_json("external.json/input/std_model.json");
path input_compressed_json("external.json/input/compressed.json");
path input_empty_json("external.json/input/empty.json");
path input_two_empty_layers_json("external.json/input/two_empty_layers.json");
path input_class_without_name_json("external.json/input/class_without_name.json");
path input_package_without_name_json("external.json/input/package_without_name.json");
path input_two_layers_with_objects_json(
    "external.json/input/two_layers_with_objects.json");
path input_disable_cmakelists_json("external.json/input/disable_cmakelists.json");
path input_disable_facet_folders_json("external.json/input/disable_facet_folders.json");
path input_enable_facet_types_json("external.json/input/enable_facet_types.json");
path input_enable_facet_hash_json("external.json/input/enable_facet_hash.json");
path input_enable_facet_io_json("external.json/input/enable_facet_io.json");
path input_enable_facet_serialization_json(
    "external.json/input/enable_facet_serialization.json"
    );
path input_all_path_and_directory_settings_json(
    "external.json/input/all_path_and_directory_settings.json");
path input_split_project_json("external.json/input/split_project.json");
path input_cpp_98_json("external.json/input/cpp_98.json");
path input_lam_model_json("external.json/input/lam_model.json");
path input_csharp_model_json("external.json/input/CSharpModel.json");


path expected("external.json/expected");
path actual("external.json/actual");

}

namespace dogen::utility::test_data {

path external_json::data_set() {
    return validating_resolver::resolve(::data_set);
}

path external_json::input() {
    return validating_resolver::resolve(::input);
}

path external_json::input_cpp_model_json() {
    return validating_resolver::resolve(::input_cpp_model_json);
}

path external_json::input_boost_model_json() {
    return validating_resolver::resolve(::input_boost_model_json);
}

path external_json::input_std_model_json() {
    return validating_resolver::resolve(::input_std_model_json);
}

path external_json::input_compressed_json() {
    return validating_resolver::resolve(::input_compressed_json);
}

path external_json::input_empty_json() {
    return validating_resolver::resolve(::input_empty_json);
}

path external_json::input_two_empty_layers_json() {
    return validating_resolver::resolve(::input_two_empty_layers_json);
}

path external_json::input_class_without_name_json() {
    return validating_resolver::resolve(::input_class_without_name_json);
}

path external_json::input_two_layers_with_objects_json() {
    return validating_resolver::resolve(::input_two_layers_with_objects_json);
}

path external_json::input_disable_cmakelists_json() {
    return validating_resolver::resolve(::input_disable_cmakelists_json);
}

path external_json::input_disable_facet_folders_json() {
    return validating_resolver::resolve(::input_disable_facet_folders_json);
}

path external_json::input_enable_facet_types_json() {
    return validating_resolver::resolve(::input_enable_facet_types_json);
}

path external_json::input_enable_facet_hash_json() {
    return validating_resolver::resolve(::input_enable_facet_hash_json);
}

path external_json::input_enable_facet_io_json() {
    return validating_resolver::resolve(::input_enable_facet_io_json);
}

path external_json::input_enable_facet_serialization_json() {
    return validating_resolver::resolve(
        ::input_enable_facet_serialization_json);
}

path external_json::input_all_path_and_directory_settings_json() {
    return validating_resolver::resolve(
        ::input_all_path_and_directory_settings_json);
}

path external_json::input_split_project_json() {
    return validating_resolver::resolve(::input_split_project_json);
}

path external_json::input_cpp_98_json() {
    return validating_resolver::resolve(::input_cpp_98_json);
}

path external_json::input_lam_model_json() {
    return validating_resolver::resolve(::input_lam_model_json);
}

path external_json::input_csharp_model_json() {
    return validating_resolver::resolve(::input_csharp_model_json);
}

path external_json::expected() {
    return validating_resolver::resolve(::expected);
}

path external_json::actual() {
    return validating_resolver::resolve(::actual);
}

}
