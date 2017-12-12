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
#include "dogen.utility/test_data/yarn_dia.hpp"

using boost::filesystem::path;

namespace {

path data_set("yarn.dia");
path non_existent_file("yarn.dia/input/non_existent_file.dia");
path input("yarn.dia/input");
path input_cpp_model_dia("yarn.dia/input/cpp_model.dia");
path input_boost_model_dia("yarn.dia/input/boost_model.dia");
path input_std_model_dia("yarn.dia/input/std_model.dia");
path input_compressed_dia("yarn.dia/input/compressed.dia");
path input_empty_dia("yarn.dia/input/empty.dia");
path input_two_empty_layers_dia("yarn.dia/input/two_empty_layers.dia");
path input_class_without_name_dia("yarn.dia/input/class_without_name.dia");
path input_package_without_name_dia("yarn.dia/input/package_without_name.dia");
path input_two_layers_with_objects_dia(
    "yarn.dia/input/two_layers_with_objects.dia");
path input_disable_cmakelists_dia("yarn.dia/input/disable_cmakelists.dia");
path input_disable_full_ctor_dia(
    "yarn.dia/input/disable_full_ctor.dia"
    );
path input_disable_facet_folders_dia("yarn.dia/input/disable_facet_folders.dia");
path input_enable_facet_types_dia("yarn.dia/input/enable_facet_types.dia");
path input_enable_facet_hash_dia("yarn.dia/input/enable_facet_hash.dia");
path input_enable_facet_io_dia("yarn.dia/input/enable_facet_io.dia");
path input_enable_facet_serialization_dia(
    "yarn.dia/input/enable_facet_serialization.dia"
    );
path input_all_path_and_directory_settings_dia(
    "yarn.dia/input/all_path_and_directory_settings.dia");
path input_split_project_dia("yarn.dia/input/split_project.dia");
path input_cpp_98_dia("yarn.dia/input/cpp_98.dia");
path input_lam_model_dia("yarn.dia/input/lam_model.dia");
path input_csharp_model_dia("yarn.dia/input/CSharpModel.dia");

path expected("yarn.dia/expected");
path expected_cpp_model_dia_xml(
    "yarn.dia/expected/cpp_model.diaxml");
path expected_cpp_model_yarn_xml(
    "yarn.dia/expected/cpp_model.yarnxml");
path expected_compressed_dia_xml(
    "yarn.dia/expected/compressed.diaxml");
path expected_empty_dia_xml(
    "yarn.dia/expected/empty.diaxml");
path expected_empty_yarn_xml(
    "yarn.dia/expected/empty.yarnxml");
path expected_empty_cpp_xml(
    "yarn.dia/expected/empty.cppxml");
path expected_package_without_name_dia_xml(
    "yarn.dia/expected/package_without_name.diaxml");
path expected_class_without_name_dia_xml(
    "yarn.dia/expected/class_without_name.diaxml");
path expected_two_empty_layers_dia_xml(
    "yarn.dia/expected/two_empty_layers.diaxml");
path expected_two_layers_with_objects_dia_xml(
    "yarn.dia/expected/two_layers_with_objects.diaxml");
path expected_two_layers_with_objects_yarn_xml(
    "yarn.dia/expected/two_layers_with_objects.yarnxml");
path expected_std_model_dia_xml(
    "yarn.dia/expected/std_model.diaxml");
path expected_std_model_yarn_xml(
    "yarn.dia/expected/std_model.yarnxml");
path expected_boost_model_dia_xml(
    "yarn.dia/expected/boost_model.diaxml");
path expected_boost_model_yarn_xml(
    "yarn.dia/expected/boost_model.yarnxml");
path expected_csharp_model_dia_xml(
    "yarn.dia/expected/csharp_model.diaxml");
path expected_csharp_model_yarn_xml(
    "yarn.dia/expected/csharp_model.yarnxml");

path actual("yarn.dia/actual");
path actual_cpp_model_dia_xml(
    "yarn.dia/actual/cpp_model.diaxml");
path actual_cpp_model_yarn_xml(
    "yarn.dia/actual/cpp_model.yarnxml");
path actual_compressed_dia_xml(
    "yarn.dia/actual/compressed.diaxml");
path actual_empty_dia_xml(
    "yarn.dia/actual/empty.diaxml");
path actual_empty_yarn_xml(
    "yarn.dia/actual/empty.yarnxml");
path actual_empty_cpp_xml(
    "yarn.dia/actual/empty.cppxml");
path actual_class_without_name_dia_xml(
    "yarn.dia/actual/class_without_name.diaxml");
path actual_two_empty_layers_dia_xml(
    "yarn.dia/actual/two_empty_layers.diaxml");
path actual_package_without_name_dia_xml(
    "yarn.dia/actual/package_without_name.diaxml");
path actual_two_layers_with_objects_dia_xml(
    "yarn.dia/actual/two_layers_with_objects.diaxml");
path actual_two_layers_with_objects_yarn_xml(
    "yarn.dia/actual/two_layers_with_objects.yarnxml");
path actual_std_model_dia_xml(
    "yarn.dia/actual/std_model.diaxml");
path actual_std_model_yarn_xml(
    "yarn.dia/actual/std_model.yarnxml");
path actual_boost_model_dia_xml(
    "yarn.dia/actual/boost_model.diaxml");
path actual_boost_model_yarn_xml(
    "yarn.dia/actual/boost_model.yarnxml");
path actual_csharp_model_dia_xml(
    "yarn.dia/actual/csharp_model.diaxml");
path actual_csharp_model_yarn_xml(
    "yarn.dia/actual/csharp_model.yarnxml");

}

namespace dogen {
namespace utility {
namespace test_data {

path yarn_dia::data_set() {
    return validating_resolver::resolve(::data_set);
}

path yarn_dia::non_existent_file() {
    return resolver::resolve(::non_existent_file);
}

path yarn_dia::input() {
    return validating_resolver::resolve(::input);
}

path yarn_dia::input_cpp_model_dia() {
    return validating_resolver::resolve(::input_cpp_model_dia);
}

path yarn_dia::input_boost_model_dia() {
    return validating_resolver::resolve(::input_boost_model_dia);
}

path yarn_dia::input_std_model_dia() {
    return validating_resolver::resolve(::input_std_model_dia);
}

path yarn_dia::input_compressed_dia() {
    return validating_resolver::resolve(::input_compressed_dia);
}

path yarn_dia::input_empty_dia() {
    return validating_resolver::resolve(::input_empty_dia);
}

path yarn_dia::input_two_empty_layers_dia() {
    return validating_resolver::resolve(::input_two_empty_layers_dia);
}

path yarn_dia::input_class_without_name_dia() {
    return validating_resolver::resolve(::input_class_without_name_dia);
}

path yarn_dia::input_package_without_name_dia() {
    return validating_resolver::resolve(::input_package_without_name_dia);
}

path yarn_dia::input_two_layers_with_objects_dia() {
    return validating_resolver::resolve(::input_two_layers_with_objects_dia);
}

path yarn_dia::input_disable_cmakelists_dia() {
    return validating_resolver::resolve(::input_disable_cmakelists_dia);
}

path yarn_dia::input_disable_facet_folders_dia() {
    return validating_resolver::resolve(::input_disable_facet_folders_dia);
}

path yarn_dia::input_enable_facet_types_dia() {
    return validating_resolver::resolve(::input_enable_facet_types_dia);
}

path yarn_dia::input_enable_facet_hash_dia() {
    return validating_resolver::resolve(::input_enable_facet_hash_dia);
}

path yarn_dia::input_enable_facet_io_dia() {
    return validating_resolver::resolve(::input_enable_facet_io_dia);
}

path yarn_dia::input_enable_facet_serialization_dia() {
    return validating_resolver::resolve(::input_enable_facet_serialization_dia);
}

path yarn_dia::input_all_path_and_directory_settings_dia() {
    return resolver::resolve(::input_all_path_and_directory_settings_dia);
}

path yarn_dia::input_split_project_dia() {
    return resolver::resolve(::input_split_project_dia);
}

path yarn_dia::input_cpp_98_dia() {
    return resolver::resolve(::input_cpp_98_dia);
}

path yarn_dia::input_lam_model_dia() {
    return resolver::resolve(::input_lam_model_dia);
}

path yarn_dia::input_csharp_model_dia() {
    return validating_resolver::resolve(::input_csharp_model_dia);
}

path yarn_dia::expected() {
    return validating_resolver::resolve(::expected);
}

path yarn_dia::expected_cpp_model_dia_xml() {
    return validating_resolver::resolve(::expected_cpp_model_dia_xml);
}

path yarn_dia::expected_cpp_model_yarn_xml() {
    return validating_resolver::resolve(::expected_cpp_model_yarn_xml);
}

path yarn_dia::expected_compressed_dia_xml() {
    return validating_resolver::resolve(::expected_compressed_dia_xml);
}

path yarn_dia::expected_empty_dia_xml() {
    return validating_resolver::resolve(::expected_empty_dia_xml);
}

path yarn_dia::expected_empty_yarn_xml() {
    return validating_resolver::resolve(::expected_empty_yarn_xml);
}

path yarn_dia::expected_empty_cpp_xml() {
    return resolver::resolve(::expected_empty_cpp_xml);
}

path yarn_dia::expected_package_without_name_dia_xml() {
    return validating_resolver::resolve(
        ::expected_package_without_name_dia_xml);
}

path yarn_dia::expected_class_without_name_dia_xml() {
    return validating_resolver::resolve(
        ::expected_class_without_name_dia_xml);
}

path yarn_dia::expected_two_empty_layers_dia_xml() {
    return validating_resolver::resolve(::expected_two_empty_layers_dia_xml);
}

path yarn_dia::expected_two_layers_with_objects_dia_xml() {
    return validating_resolver::resolve(
        ::expected_two_layers_with_objects_dia_xml);
}

path yarn_dia::expected_two_layers_with_objects_yarn_xml() {
    return validating_resolver::resolve(
        ::expected_two_layers_with_objects_yarn_xml);
}

path yarn_dia::expected_std_model_dia_xml() {
    return validating_resolver::resolve(::expected_std_model_dia_xml);
}

path yarn_dia::expected_std_model_yarn_xml() {
    return validating_resolver::resolve(::expected_std_model_yarn_xml);
}

path yarn_dia::expected_boost_model_dia_xml() {
    return validating_resolver::resolve(::expected_boost_model_dia_xml);
}

path yarn_dia::expected_boost_model_yarn_xml() {
    return validating_resolver::resolve(::expected_boost_model_yarn_xml);
}

path yarn_dia::expected_csharp_model_dia_xml() {
    return validating_resolver::resolve(::expected_csharp_model_dia_xml);
}

path yarn_dia::expected_csharp_model_yarn_xml() {
    return validating_resolver::resolve(::expected_csharp_model_yarn_xml);
}

path yarn_dia::actual() {
    return validating_resolver::resolve(::actual);
}

path yarn_dia::actual_cpp_model_dia_xml() {
    return resolver::resolve(::actual_cpp_model_dia_xml);
}

path yarn_dia::actual_cpp_model_yarn_xml() {
    return resolver::resolve(::actual_cpp_model_yarn_xml);
}

path yarn_dia::actual_compressed_dia_xml() {
    return resolver::resolve(::actual_compressed_dia_xml);
}

path yarn_dia::actual_empty_dia_xml() {
    return resolver::resolve(::actual_empty_dia_xml);
}

path yarn_dia::actual_class_without_name_dia_xml() {
    return resolver::resolve(::actual_class_without_name_dia_xml);
}

path yarn_dia::actual_empty_yarn_xml() {
    return resolver::resolve(::actual_empty_yarn_xml);
}

path yarn_dia::actual_empty_cpp_xml() {
    return resolver::resolve(::actual_empty_cpp_xml);
}

path yarn_dia::actual_package_without_name_dia_xml() {
    return resolver::resolve(::actual_package_without_name_dia_xml);
}

path yarn_dia::actual_two_empty_layers_dia_xml() {
    return resolver::resolve(::actual_two_empty_layers_dia_xml);
}

path yarn_dia::actual_two_layers_with_objects_dia_xml() {
    return resolver::resolve(::actual_two_layers_with_objects_dia_xml);
}

path yarn_dia::actual_two_layers_with_objects_yarn_xml() {
    return resolver::resolve(::actual_two_layers_with_objects_yarn_xml);
}

path yarn_dia::actual_std_model_dia_xml() {
    return resolver::resolve(::actual_std_model_dia_xml);
}

path yarn_dia::actual_std_model_yarn_xml() {
    return resolver::resolve(::actual_std_model_yarn_xml);
}

path yarn_dia::actual_boost_model_dia_xml() {
    return resolver::resolve(::actual_boost_model_dia_xml);
}

path yarn_dia::actual_boost_model_yarn_xml() {
    return resolver::resolve(::actual_boost_model_yarn_xml);
}

path yarn_dia::actual_csharp_model_dia_xml() {
    return resolver::resolve(::actual_csharp_model_dia_xml);
}

path yarn_dia::actual_csharp_model_yarn_xml() {
    return resolver::resolve(::actual_csharp_model_yarn_xml);
}

} } }
