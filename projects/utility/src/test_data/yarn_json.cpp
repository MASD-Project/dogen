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
#include "dogen/utility/test_data/resolver.hpp"
#include "dogen/utility/test_data/validating_resolver.hpp"
#include "dogen/utility/test_data/yarn_json.hpp"

using boost::filesystem::path;

namespace {

path data_set("yarn.json");
path input("yarn.json/input");
path input_boost_model_json("yarn.json/input/boost_model.json");
path input_std_model_json("yarn.json/input/std_model.json");
path input_class_in_a_package_json("yarn.json/input/class_in_a_package.json");
path input_compressed_json("yarn.json/input/compressed.json");
path input_empty_json("yarn.json/input/empty.json");
path input_two_empty_layers_json("yarn.json/input/two_empty_layers.json");
path input_stand_alone_class_json(
    "yarn.json/input/stand_alone_class.json");
path input_empty_package_json("yarn.json/input/empty_package.json");
path input_class_without_name_json("yarn.json/input/class_without_name.json");
path input_classes_inout_package_json(
    "yarn.json/input/classes_inout_package.json");
path input_class_without_attributes_json(
    "yarn.json/input/class_without_attributes.json");
path input_class_without_package_json("yarn.json/input/class_without_package.json");
path input_classes_in_a_package_json("yarn.json/input/classes_in_a_package.json");
path input_classes_without_package_json(
    "yarn.json/input/classes_without_package.json");
path input_package_without_name_json("yarn.json/input/package_without_name.json");
path input_two_layers_with_objects_json(
    "yarn.json/input/two_layers_with_objects.json");
path input_disable_cmakelists_json("yarn.json/input/disable_cmakelists.json");
path input_disable_full_ctor_json(
    "yarn.json/input/disable_full_ctor.json"
    );
path input_disable_facet_folders_json("yarn.json/input/disable_facet_folders.json");
path input_disable_xml_serialization_json(
    "yarn.json/input/disable_xml_serialization.json"
    );
path input_enable_facet_types_json("yarn.json/input/enable_facet_types.json");
path input_enable_facet_hash_json("yarn.json/input/enable_facet_hash.json");
path input_enable_facet_io_json("yarn.json/input/enable_facet_io.json");
path input_enable_facet_serialization_json(
    "yarn.json/input/enable_facet_serialization.json"
    );
path input_rename_facet_folder_json("yarn.json/input/rename_facet_folder.json");
path input_all_builtins_json("yarn.json/input/all_builtins.json");
path input_csharp_model_json("yarn.json/input/CSharpModel.json");
path input_trivial_inheritance_json("yarn.json/input/trivial_inheritance.json");
path input_trivial_association_json("yarn.json/input/trivial_association.json");
path input_comments_json("yarn.json/input/comments.json");
path input_enumeration_json("yarn.json/input/enumeration.json");
path input_exception_json("yarn.json/input/exception.json");
path input_stereotypes_json("yarn.json/input/stereotypes.json");

path expected("yarn.json/expected");
path actual("yarn.json/actual");

}

namespace dogen {
namespace utility {
namespace test_data {

path yarn_json::data_set() {
    return validating_resolver::resolve(::data_set);
}

path yarn_json::input() {
    return validating_resolver::resolve(::input);
}

path yarn_json::input_boost_model_json() {
    return validating_resolver::resolve(::input_boost_model_json);
}

path yarn_json::input_std_model_json() {
    return validating_resolver::resolve(::input_std_model_json);
}

path yarn_json::input_class_in_a_package_json() {
    return validating_resolver::resolve(::input_class_in_a_package_json);
}

path yarn_json::input_compressed_json() {
    return validating_resolver::resolve(::input_compressed_json);
}

path yarn_json::input_empty_json() {
    return validating_resolver::resolve(::input_empty_json);
}

path yarn_json::input_two_empty_layers_json() {
    return validating_resolver::resolve(::input_two_empty_layers_json);
}

path yarn_json::input_stand_alone_class_json() {
    return validating_resolver::resolve(::input_stand_alone_class_json);
}

path yarn_json::input_empty_package_json() {
    return validating_resolver::resolve(::input_empty_package_json);
}

path yarn_json::input_class_without_name_json() {
    return validating_resolver::resolve(::input_class_without_name_json);
}

path yarn_json::input_classes_inout_package_json() {
    return validating_resolver::resolve(
        ::input_classes_inout_package_json);
}

path yarn_json::input_class_without_attributes_json() {
    return validating_resolver::resolve(::input_class_without_attributes_json);
}

path yarn_json::input_class_without_package_json() {
    return validating_resolver::resolve(::input_class_without_package_json);
}

path yarn_json::input_classes_in_a_package_json() {
    return validating_resolver::resolve(::input_classes_in_a_package_json);
}

path yarn_json::input_classes_without_package_json() {
    return validating_resolver::resolve(::input_classes_without_package_json);
}

path yarn_json::input_package_without_name_json() {
    return validating_resolver::resolve(::input_package_without_name_json);
}

path yarn_json::input_two_layers_with_objects_json() {
    return validating_resolver::resolve(::input_two_layers_with_objects_json);
}

path yarn_json::input_disable_cmakelists_json() {
    return validating_resolver::resolve(::input_disable_cmakelists_json);
}

path yarn_json::input_disable_full_ctor_json() {
    return validating_resolver::resolve(
        ::input_disable_full_ctor_json);
}

path yarn_json::input_disable_facet_folders_json() {
    return validating_resolver::resolve(::input_disable_facet_folders_json);
}

path yarn_json::input_disable_xml_serialization_json() {
    return validating_resolver::resolve(::input_disable_xml_serialization_json);
}

path yarn_json::input_enable_facet_types_json() {
    return validating_resolver::resolve(::input_enable_facet_types_json);
}

path yarn_json::input_enable_facet_hash_json() {
    return validating_resolver::resolve(::input_enable_facet_hash_json);
}

path yarn_json::input_enable_facet_io_json() {
    return validating_resolver::resolve(::input_enable_facet_io_json);
}

path yarn_json::input_enable_facet_serialization_json() {
    return validating_resolver::resolve(::input_enable_facet_serialization_json);
}

path yarn_json::input_rename_facet_folder_json() {
    return validating_resolver::resolve(::input_rename_facet_folder_json);
}

path yarn_json::input_all_builtins_json() {
    return validating_resolver::resolve(::input_all_builtins_json);
}

path yarn_json::input_csharp_model_json() {
    return validating_resolver::resolve(::input_csharp_model_json);
}

path yarn_json::input_trivial_inheritance_json() {
    return validating_resolver::resolve(::input_trivial_inheritance_json);
}

path yarn_json::input_trivial_association_json() {
    return validating_resolver::resolve(::input_trivial_association_json);
}

path yarn_json::input_comments_json() {
    return validating_resolver::resolve(::input_comments_json);
}

path yarn_json::input_enumeration_json() {
    return validating_resolver::resolve(::input_enumeration_json);
}

path yarn_json::input_exception_json() {
    return validating_resolver::resolve(::input_exception_json);
}

path yarn_json::input_stereotypes_json() {
    return validating_resolver::resolve(::input_stereotypes_json);
}

path yarn_json::expected() {
    return validating_resolver::resolve(::expected);
}

path yarn_json::actual() {
    return validating_resolver::resolve(::actual);
}

} } }
