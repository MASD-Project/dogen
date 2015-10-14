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
#include "dogen/utility/test_data/tack_dia.hpp"

using boost::filesystem::path;

namespace {

path data_set("tack_dia");
path non_existent_file("tack_dia/input/non_existent_file.dia");
path input("tack_dia/input");
path input_boost_model_dia("tack_dia/input/boost_model.dia");
path input_std_model_dia("tack_dia/input/std_model.dia");
path input_class_in_a_package_dia("tack_dia/input/class_in_a_package.dia");
path input_compressed_dia("tack_dia/input/compressed.dia");
path input_empty_dia("tack_dia/input/empty.dia");
path input_two_empty_layers_dia("tack_dia/input/two_empty_layers.dia");
path input_stand_alone_class_dia(
    "tack_dia/input/stand_alone_class.dia");
path input_empty_package_dia("tack_dia/input/empty_package.dia");
path input_class_without_name_dia("tack_dia/input/class_without_name.dia");
path input_classes_inout_package_dia(
    "tack_dia/input/classes_inout_package.dia");
path input_class_without_attributes_dia(
    "tack_dia/input/class_without_attributes.dia");
path input_class_without_package_dia("tack_dia/input/class_without_package.dia");
path input_classes_in_a_package_dia("tack_dia/input/classes_in_a_package.dia");
path input_classes_without_package_dia(
    "tack_dia/input/classes_without_package.dia");
path input_package_without_name_dia("tack_dia/input/package_without_name.dia");
path input_two_layers_with_objects_dia(
    "tack_dia/input/two_layers_with_objects.dia");
path input_disable_cmakelists_dia("tack_dia/input/disable_cmakelists.dia");
path input_disable_full_ctor_dia(
    "tack_dia/input/disable_full_ctor.dia"
    );
path input_disable_facet_folders_dia("tack_dia/input/disable_facet_folders.dia");
path input_disable_unique_file_names_dia(
    "tack_dia/input/disable_unique_file_names.dia"
    );
path input_disable_xml_serialization_dia(
    "tack_dia/input/disable_xml_serialization.dia"
    );
path input_enable_facet_domain_dia("tack_dia/input/enable_facet_domain.dia");
path input_enable_facet_hash_dia("tack_dia/input/enable_facet_hash.dia");
path input_enable_facet_io_dia("tack_dia/input/enable_facet_io.dia");
path input_enable_facet_serialization_dia(
    "tack_dia/input/enable_facet_serialization.dia"
    );
path input_rename_facet_folder_dia("tack_dia/input/rename_facet_folder.dia");
path input_use_integrated_io_dia("tack_dia/input/use_integrated_io.dia");
path input_all_primitives_dia("tack_dia/input/all_primitives.dia");
path input_trivial_inheritance_dia("tack_dia/input/trivial_inheritance.dia");
path input_trivial_association_dia("tack_dia/input/trivial_association.dia");
path input_comments_dia("tack_dia/input/comments.dia");
path input_enumeration_dia("tack_dia/input/enumeration.dia");
path input_exception_dia("tack_dia/input/exception.dia");
path input_stereotypes_dia("tack_dia/input/stereotypes.dia");

path expected(
    "tack_dia/expected");
path expected_class_in_a_package_dia_xml(
    "tack_dia/expected/class_in_a_package.diaxml");
path expected_class_in_a_package_tack_xml(
    "tack_dia/expected/class_in_a_package.tackxml");
path expected_class_in_a_package_cpp_xml(
    "tack_dia/expected/class_in_a_package.cppxml");
path expected_compressed_dia_xml(
    "tack_dia/expected/compressed.diaxml");
path expected_empty_dia_xml(
    "tack_dia/expected/empty.diaxml");
path expected_empty_tack_xml(
    "tack_dia/expected/empty.tackxml");
path expected_empty_cpp_xml(
    "tack_dia/expected/empty.cppxml");
path expected_two_empty_layers_dia_xml(
    "tack_dia/expected/two_empty_layers.diaxml");
path expected_stand_alone_class_dia_xml(
    "tack_dia/expected/stand_alone_class.diaxml");
path expected_empty_package_dia_xml(
    "tack_dia/expected/empty_package.diaxml");
path expected_empty_package_tack_xml(
    "tack_dia/expected/empty_package.tackxml");
path expected_class_without_name_dia_xml(
    "tack_dia/expected/class_without_name.diaxml");
path expected_classes_inout_package_dia_xml(
    "tack_dia/expected/classes_inout_package.diaxml");
path expected_classes_inout_package_tack_xml(
    "tack_dia/expected/classes_inout_package.tackxml");
path expected_class_without_attributes_dia_xml(
    "tack_dia/expected/class_without_attributes.diaxml");
path expected_class_without_attributes_tack_xml(
    "tack_dia/expected/class_without_attributes.tackxml");
path expected_class_without_package_dia_xml(
    "tack_dia/expected/class_without_package.diaxml");
path expected_class_without_package_tack_xml(
    "tack_dia/expected/class_without_package.tackxml");
path expected_classes_in_a_package_dia_xml(
    "tack_dia/expected/classes_in_a_package.diaxml");
path expected_classes_in_a_package_tack_xml(
    "tack_dia/expected/classes_in_a_package.tackxml");
path expected_classes_without_package_dia_xml(
    "tack_dia/expected/classes_without_package.diaxml");
path expected_classes_without_package_tack_xml(
    "tack_dia/expected/classes_without_package.tackxml");
path expected_package_without_name_dia_xml(
    "tack_dia/expected/package_without_name.diaxml");
path expected_two_layers_with_objects_dia_xml(
    "tack_dia/expected/two_layers_with_objects.diaxml");
path expected_two_layers_with_objects_tack_xml(
    "tack_dia/expected/two_layers_with_objects.tackxml");
path expected_class_in_a_package_stdout_txt(
    "tack_dia/expected/class_in_a_package_stdout.txt");
path expected_all_primitives_dia_xml(
    "tack_dia/expected/all_primitives.diaxml");
path expected_all_primitives_tack_xml(
    "tack_dia/expected/all_primitives.tackxml");
path expected_trivial_inheritance_dia_xml(
    "tack_dia/expected/trivial_inheritance.diaxml");
path expected_trivial_inheritance_tack_xml(
    "tack_dia/expected/trivial_inheritance.tackxml");
path expected_trivial_association_dia_xml(
    "tack_dia/expected/trivial_association.diaxml");
path expected_trivial_association_tack_xml(
    "tack_dia/expected/trivial_association.tackxml");
path expected_comments_dia_xml(
    "tack_dia/expected/comments.diaxml");
path expected_comments_tack_xml(
    "tack_dia/expected/comments.tackxml");
path expected_comments_cpp_xml(
    "tack_dia/expected/comments.cppxml");
path expected_enumeration_dia_xml(
    "tack_dia/expected/enumeration.diaxml");
path expected_enumeration_tack_xml(
    "tack_dia/expected/enumeration.tackxml");
path expected_enumeration_cpp_xml(
    "tack_dia/expected/enumeration.cppxml");
path expected_exception_dia_xml(
    "tack_dia/expected/exception.diaxml");
path expected_exception_tack_xml(
    "tack_dia/expected/exception.tackxml");
path expected_exception_cpp_xml(
    "tack_dia/expected/exception.cppxml");
path expected_std_model_dia_xml(
    "tack_dia/expected/std_model.diaxml");
path expected_std_model_tack_xml(
    "tack_dia/expected/std_model.tackxml");
path expected_boost_model_dia_xml(
    "tack_dia/expected/boost_model.diaxml");
path expected_boost_model_tack_xml(
    "tack_dia/expected/boost_model.tackxml");

path actual(
    "tack_dia/actual");
path actual_class_in_a_package_dia_xml(
    "tack_dia/actual/class_in_a_package.diaxml");
path actual_class_in_a_package_tack_xml(
    "tack_dia/actual/class_in_a_package.tackxml");
path actual_class_in_a_package_cpp_xml(
    "tack_dia/actual/class_in_a_package.cppxml");
path actual_compressed_dia_xml(
    "tack_dia/actual/compressed.diaxml");
path actual_empty_dia_xml(
    "tack_dia/actual/empty.diaxml");
path actual_empty_tack_xml(
    "tack_dia/actual/empty.tackxml");
path actual_empty_cpp_xml(
    "tack_dia/actual/empty.cppxml");
path actual_two_empty_layers_dia_xml(
    "tack_dia/actual/two_empty_layers.diaxml");
path actual_stand_alone_class_dia_xml(
    "tack_dia/actual/stand_alone_class.diaxml");
path actual_empty_package_dia_xml(
    "tack_dia/actual/empty_package.diaxml");
path actual_empty_package_tack_xml(
    "tack_dia/actual/empty_package.tackxml");
path actual_class_without_name_dia_xml(
    "tack_dia/actual/class_without_name.diaxml");
path actual_classes_inout_package_dia_xml(
    "tack_dia/actual/classes_inout_package.diaxml");
path actual_classes_inout_package_tack_xml(
    "tack_dia/actual/classes_inout_package.tackxml");
path actual_class_without_attributes_dia_xml(
    "tack_dia/actual/class_without_attributes.diaxml");
path actual_class_without_attributes_tack_xml(
    "tack_dia/actual/class_without_attributes.tackxml");
path actual_class_without_package_dia_xml(
    "tack_dia/actual/class_without_package.diaxml");
path actual_class_without_package_tack_xml(
    "tack_dia/actual/class_without_package.tackxml");
path actual_classes_in_a_package_dia_xml(
    "tack_dia/actual/classes_in_a_package.diaxml");
path actual_classes_without_package_dia_xml(
    "tack_dia/actual/classes_without_package.diaxml");
path actual_classes_without_package_tack_xml(
    "tack_dia/actual/classes_without_package.tackxml");
path actual_package_without_name_dia_xml(
    "tack_dia/actual/package_without_name.diaxml");
path actual_two_layers_with_objects_dia_xml(
    "tack_dia/actual/two_layers_with_objects.diaxml");
path actual_two_layers_with_objects_tack_xml(
    "tack_dia/actual/two_layers_with_objects.tackxml");
path actual_class_in_a_package_stdout_txt(
    "tack_dia/actual/class_in_a_package_stdout.txt");
path actual_all_primitives_dia_xml(
    "tack_dia/actual/all_primitives.diaxml");
path actual_all_primitives_tack_xml(
    "tack_dia/actual/all_primitives.tackxml");
path actual_trivial_inheritance_dia_xml(
    "tack_dia/actual/trivial_inheritance.diaxml");
path actual_trivial_inheritance_tack_xml(
    "tack_dia/actual/trivial_inheritance.tackxml");
path actual_trivial_association_dia_xml(
    "tack_dia/actual/trivial_association.diaxml");
path actual_trivial_association_tack_xml(
    "tack_dia/actual/trivial_association.tackxml");
path actual_comments_dia_xml(
    "tack_dia/actual/comments.diaxml");
path actual_comments_tack_xml(
    "tack_dia/actual/comments.tackxml");
path actual_comments_cpp_xml(
    "tack_dia/actual/comments.cppxml");
path actual_enumeration_dia_xml(
    "tack_dia/actual/enumeration.diaxml");
path actual_enumeration_tack_xml(
    "tack_dia/actual/enumeration.tackxml");
path actual_enumeration_cpp_xml(
    "tack_dia/actual/enumeration.cppxml");
path actual_exception_dia_xml(
    "tack_dia/actual/exception.diaxml");
path actual_exception_tack_xml(
    "tack_dia/actual/exception.tackxml");
path actual_exception_cpp_xml(
    "tack_dia/actual/exception.cppxml");
path actual_std_model_dia_xml(
    "tack_dia/actual/std_model.diaxml");
path actual_std_model_tack_xml(
    "tack_dia/actual/std_model.tackxml");
path actual_boost_model_dia_xml(
    "tack_dia/actual/boost_model.diaxml");
path actual_boost_model_tack_xml(
    "tack_dia/actual/boost_model.tackxml");

}

namespace dogen {
namespace utility {
namespace test_data {

path tack_dia::data_set() {
    return validating_resolver::resolve(::data_set);
}

path tack_dia::non_existent_file() {
    return resolver::resolve(::non_existent_file);
}

path tack_dia::input() {
    return validating_resolver::resolve(::input);
}

path tack_dia::input_boost_model_dia() {
    return validating_resolver::resolve(::input_boost_model_dia);
}

path tack_dia::input_std_model_dia() {
    return validating_resolver::resolve(::input_std_model_dia);
}

path tack_dia::input_class_in_a_package_dia() {
    return validating_resolver::resolve(::input_class_in_a_package_dia);
}

path tack_dia::input_compressed_dia() {
    return validating_resolver::resolve(::input_compressed_dia);
}

path tack_dia::input_empty_dia() {
    return validating_resolver::resolve(::input_empty_dia);
}

path tack_dia::input_two_empty_layers_dia() {
    return validating_resolver::resolve(::input_two_empty_layers_dia);
}

path tack_dia::input_stand_alone_class_dia() {
    return validating_resolver::resolve(::input_stand_alone_class_dia);
}

path tack_dia::input_empty_package_dia() {
    return validating_resolver::resolve(::input_empty_package_dia);
}

path tack_dia::input_class_without_name_dia() {
    return validating_resolver::resolve(::input_class_without_name_dia);
}

path tack_dia::input_classes_inout_package_dia() {
    return validating_resolver::resolve(
        ::input_classes_inout_package_dia);
}

path tack_dia::input_class_without_attributes_dia() {
    return validating_resolver::resolve(::input_class_without_attributes_dia);
}

path tack_dia::input_class_without_package_dia() {
    return validating_resolver::resolve(::input_class_without_package_dia);
}

path tack_dia::input_classes_in_a_package_dia() {
    return validating_resolver::resolve(::input_classes_in_a_package_dia);
}

path tack_dia::input_classes_without_package_dia() {
    return validating_resolver::resolve(::input_classes_without_package_dia);
}

path tack_dia::input_package_without_name_dia() {
    return validating_resolver::resolve(::input_package_without_name_dia);
}

path tack_dia::input_two_layers_with_objects_dia() {
    return validating_resolver::resolve(::input_two_layers_with_objects_dia);
}

path tack_dia::input_disable_cmakelists_dia() {
    return validating_resolver::resolve(::input_disable_cmakelists_dia);
}

path tack_dia::input_disable_full_ctor_dia() {
    return validating_resolver::resolve(
        ::input_disable_full_ctor_dia);
}

path tack_dia::input_disable_facet_folders_dia() {
    return validating_resolver::resolve(::input_disable_facet_folders_dia);
}

path tack_dia::input_disable_unique_file_names_dia() {
    return validating_resolver::resolve(::input_disable_unique_file_names_dia);
}

path tack_dia::input_disable_xml_serialization_dia() {
    return validating_resolver::resolve(::input_disable_xml_serialization_dia);
}

path tack_dia::input_enable_facet_domain_dia() {
    return validating_resolver::resolve(::input_enable_facet_domain_dia);
}

path tack_dia::input_enable_facet_hash_dia() {
    return validating_resolver::resolve(::input_enable_facet_hash_dia);
}

path tack_dia::input_enable_facet_io_dia() {
    return validating_resolver::resolve(::input_enable_facet_io_dia);
}

path tack_dia::input_enable_facet_serialization_dia() {
    return validating_resolver::resolve(::input_enable_facet_serialization_dia);
}

path tack_dia::input_rename_facet_folder_dia() {
    return validating_resolver::resolve(::input_rename_facet_folder_dia);
}

path tack_dia::input_use_integrated_io_dia() {
    return validating_resolver::resolve(::input_use_integrated_io_dia);
}

path tack_dia::input_all_primitives_dia() {
    return validating_resolver::resolve(::input_all_primitives_dia);
}

path tack_dia::input_trivial_inheritance_dia() {
    return validating_resolver::resolve(::input_trivial_inheritance_dia);
}

path tack_dia::input_trivial_association_dia() {
    return validating_resolver::resolve(::input_trivial_association_dia);
}

path tack_dia::input_comments_dia() {
    return validating_resolver::resolve(::input_comments_dia);
}

path tack_dia::input_enumeration_dia() {
    return validating_resolver::resolve(::input_enumeration_dia);
}

path tack_dia::input_exception_dia() {
    return validating_resolver::resolve(::input_exception_dia);
}

path tack_dia::input_stereotypes_dia() {
    return validating_resolver::resolve(::input_stereotypes_dia);
}

path tack_dia::expected() {
    return validating_resolver::resolve(::expected);
}

path tack_dia::expected_class_in_a_package_dia_xml() {
    return validating_resolver::resolve(::expected_class_in_a_package_dia_xml);
}

path tack_dia::expected_class_in_a_package_tack_xml() {
    return validating_resolver::resolve(::expected_class_in_a_package_tack_xml);
}

path tack_dia::expected_class_in_a_package_cpp_xml() {
    return validating_resolver::resolve(::expected_class_in_a_package_cpp_xml);
}

path tack_dia::expected_compressed_dia_xml() {
    return validating_resolver::resolve(::expected_compressed_dia_xml);
}

path tack_dia::expected_empty_dia_xml() {
    return validating_resolver::resolve(::expected_empty_dia_xml);
}

path tack_dia::expected_empty_tack_xml() {
    return validating_resolver::resolve(::expected_empty_tack_xml);
}

path tack_dia::expected_empty_cpp_xml() {
    return resolver::resolve(::expected_empty_cpp_xml);
}

path tack_dia::expected_two_empty_layers_dia_xml() {
    return validating_resolver::resolve(::expected_two_empty_layers_dia_xml);
}

path tack_dia::expected_stand_alone_class_dia_xml() {
    return validating_resolver::resolve(
        ::expected_stand_alone_class_dia_xml);
}

path tack_dia::expected_empty_package_dia_xml() {
    return validating_resolver::resolve(::expected_empty_package_dia_xml);
}

path tack_dia::expected_empty_package_tack_xml() {
    return validating_resolver::resolve(::expected_empty_package_tack_xml);
}

path tack_dia::expected_class_without_name_dia_xml() {
    return validating_resolver::resolve(
        ::expected_class_without_name_dia_xml);
}

path tack_dia::expected_classes_inout_package_dia_xml() {
    return validating_resolver::resolve(
        ::expected_classes_inout_package_dia_xml);
}

path tack_dia::expected_classes_inout_package_tack_xml() {
    return validating_resolver::resolve(
        ::expected_classes_inout_package_tack_xml);
}

path tack_dia::expected_class_without_attributes_dia_xml() {
    return validating_resolver::resolve(
        ::expected_class_without_attributes_dia_xml);
}

path tack_dia::expected_class_without_attributes_tack_xml() {
    return validating_resolver::resolve(
        ::expected_class_without_attributes_tack_xml);
}

path tack_dia::expected_class_without_package_dia_xml() {
    return validating_resolver::resolve(
        ::expected_class_without_package_dia_xml);
}

path tack_dia::expected_class_without_package_tack_xml() {
    return validating_resolver::resolve(
        ::expected_class_without_package_tack_xml);
}

path tack_dia::expected_classes_in_a_package_dia_xml() {
    return validating_resolver::resolve(
        ::expected_classes_in_a_package_dia_xml);
}

path tack_dia::expected_classes_without_package_dia_xml() {
    return validating_resolver::resolve(
        ::expected_classes_without_package_dia_xml);
}

path tack_dia::expected_classes_without_package_tack_xml() {
    return validating_resolver::resolve(
        ::expected_classes_without_package_tack_xml);
}

path tack_dia::expected_package_without_name_dia_xml() {
    return validating_resolver::resolve(
        ::expected_package_without_name_dia_xml);
}

path tack_dia::expected_class_in_a_package_stdout_txt() {
    return validating_resolver::resolve(
        ::expected_class_in_a_package_stdout_txt);
}

path tack_dia::expected_two_layers_with_objects_dia_xml() {
    return validating_resolver::resolve(
        ::expected_two_layers_with_objects_dia_xml);
}

path tack_dia::expected_two_layers_with_objects_tack_xml() {
    return validating_resolver::resolve(
        ::expected_two_layers_with_objects_tack_xml);
}

path tack_dia::expected_all_primitives_dia_xml() {
    return validating_resolver::resolve(::expected_all_primitives_dia_xml);
}

path tack_dia::expected_all_primitives_tack_xml() {
    return validating_resolver::resolve(::expected_all_primitives_tack_xml);
}

path tack_dia::expected_trivial_inheritance_dia_xml() {
    return validating_resolver::resolve(::expected_trivial_inheritance_dia_xml);
}

path tack_dia::expected_trivial_inheritance_tack_xml() {
    return validating_resolver::resolve(::expected_trivial_inheritance_tack_xml);
}

path tack_dia::expected_comments_dia_xml() {
    return validating_resolver::resolve(::expected_comments_dia_xml);
}

path tack_dia::expected_comments_tack_xml() {
    return validating_resolver::resolve(::expected_comments_tack_xml);
}

path tack_dia::expected_comments_cpp_xml() {
    return validating_resolver::resolve(::expected_comments_cpp_xml);
}

path tack_dia::expected_enumeration_dia_xml() {
    return validating_resolver::resolve(::expected_enumeration_dia_xml);
}

path tack_dia::expected_enumeration_tack_xml() {
    return validating_resolver::resolve(::expected_enumeration_tack_xml);
}

path tack_dia::expected_enumeration_cpp_xml() {
    return resolver::resolve(::expected_enumeration_cpp_xml);
}

path tack_dia::expected_exception_dia_xml() {
    return resolver::resolve(::expected_exception_dia_xml);
}

path tack_dia::expected_exception_tack_xml() {
    return resolver::resolve(::expected_exception_tack_xml);
}

path tack_dia::expected_exception_cpp_xml() {
    return resolver::resolve(::expected_exception_cpp_xml);
}

path tack_dia::expected_std_model_dia_xml() {
    return validating_resolver::resolve(::expected_std_model_dia_xml);
}

path tack_dia::expected_std_model_tack_xml() {
    return validating_resolver::resolve(::expected_std_model_tack_xml);
}

path tack_dia::expected_boost_model_dia_xml() {
    return validating_resolver::resolve(::expected_boost_model_dia_xml);
}

path tack_dia::expected_boost_model_tack_xml() {
    return validating_resolver::resolve(::expected_boost_model_tack_xml);
}

path tack_dia::actual() {
    return validating_resolver::resolve(::actual);
}

path tack_dia::actual_class_in_a_package_dia_xml() {
    return resolver::resolve(::actual_class_in_a_package_dia_xml);
}

path tack_dia::actual_class_in_a_package_tack_xml() {
    return resolver::resolve(::actual_class_in_a_package_tack_xml);
}

path tack_dia::actual_class_in_a_package_cpp_xml() {
    return resolver::resolve(::actual_class_in_a_package_cpp_xml);
}

path tack_dia::actual_compressed_dia_xml() {
    return resolver::resolve(::actual_compressed_dia_xml);
}

path tack_dia::actual_empty_dia_xml() {
    return resolver::resolve(::actual_empty_dia_xml);
}

path tack_dia::actual_empty_tack_xml() {
    return resolver::resolve(::actual_empty_tack_xml);
}

path tack_dia::actual_empty_cpp_xml() {
    return resolver::resolve(::actual_empty_cpp_xml);
}

path tack_dia::actual_two_empty_layers_dia_xml() {
    return resolver::resolve(::actual_two_empty_layers_dia_xml);
}

path tack_dia::actual_stand_alone_class_dia_xml() {
    return resolver::resolve(::actual_stand_alone_class_dia_xml);
}

path tack_dia::actual_empty_package_dia_xml() {
    return resolver::resolve(::actual_empty_package_dia_xml);
}

path tack_dia::actual_empty_package_tack_xml() {
    return resolver::resolve(::actual_empty_package_tack_xml);
}

path tack_dia::actual_class_without_name_dia_xml() {
    return resolver::resolve(::actual_class_without_name_dia_xml);
}

path tack_dia::actual_classes_inout_package_dia_xml() {
    return resolver::resolve(::actual_classes_inout_package_dia_xml);
}

path tack_dia::actual_classes_inout_package_tack_xml() {
    return resolver::resolve(::actual_classes_inout_package_tack_xml);
}

path tack_dia::actual_class_without_attributes_dia_xml() {
    return resolver::resolve(::actual_class_without_attributes_dia_xml);
}

path tack_dia::actual_class_without_attributes_tack_xml() {
    return resolver::resolve(::actual_class_without_attributes_tack_xml);
}

path tack_dia::actual_class_without_package_dia_xml() {
    return resolver::resolve(::actual_class_without_package_dia_xml);
}

path tack_dia::actual_class_without_package_tack_xml() {
    return resolver::resolve(::actual_class_without_package_tack_xml);
}

path tack_dia::actual_classes_in_a_package_dia_xml() {
    return resolver::resolve(
        ::actual_classes_in_a_package_dia_xml);
}

path tack_dia::actual_classes_without_package_dia_xml() {
    return resolver::resolve(::actual_classes_without_package_dia_xml);
}

path tack_dia::actual_classes_without_package_tack_xml() {
    return resolver::resolve(::actual_classes_without_package_tack_xml);
}

path tack_dia::actual_package_without_name_dia_xml() {
    return resolver::resolve(::actual_package_without_name_dia_xml);
}

path tack_dia::actual_two_layers_with_objects_dia_xml() {
    return resolver::resolve(::actual_two_layers_with_objects_dia_xml);
}

path tack_dia::actual_two_layers_with_objects_tack_xml() {
    return resolver::resolve(::actual_two_layers_with_objects_tack_xml);
}

path tack_dia::actual_class_in_a_package_stdout_txt() {
    return resolver::resolve(::actual_class_in_a_package_stdout_txt);
}

path tack_dia::actual_trivial_inheritance_dia_xml() {
    return resolver::resolve(::actual_trivial_inheritance_dia_xml);
}

path tack_dia::actual_trivial_inheritance_tack_xml() {
    return resolver::resolve(::actual_trivial_inheritance_tack_xml);
}

path tack_dia::actual_all_primitives_dia_xml() {
    return resolver::resolve(::actual_all_primitives_dia_xml);
}

path tack_dia::actual_all_primitives_tack_xml() {
    return resolver::resolve(::actual_all_primitives_tack_xml);
}

path tack_dia::actual_comments_dia_xml() {
    return resolver::resolve(::actual_comments_dia_xml);
}

path tack_dia::actual_comments_tack_xml() {
    return resolver::resolve(::actual_comments_tack_xml);
}

path tack_dia::actual_comments_cpp_xml() {
    return resolver::resolve(::actual_comments_cpp_xml);
}

path tack_dia::actual_enumeration_dia_xml() {
    return resolver::resolve(::actual_enumeration_dia_xml);
}

path tack_dia::actual_enumeration_tack_xml() {
    return resolver::resolve(::actual_enumeration_tack_xml);
}

path tack_dia::actual_enumeration_cpp_xml() {
    return resolver::resolve(::actual_enumeration_cpp_xml);
}

path tack_dia::actual_exception_dia_xml() {
    return resolver::resolve(::actual_exception_dia_xml);
}

path tack_dia::actual_exception_tack_xml() {
    return resolver::resolve(::actual_exception_tack_xml);
}

path tack_dia::actual_exception_cpp_xml() {
    return resolver::resolve(::actual_exception_cpp_xml);
}

path tack_dia::actual_std_model_dia_xml() {
    return resolver::resolve(::actual_std_model_dia_xml);
}

path tack_dia::actual_std_model_tack_xml() {
    return resolver::resolve(::actual_std_model_tack_xml);
}

path tack_dia::actual_boost_model_dia_xml() {
    return resolver::resolve(::actual_boost_model_dia_xml);
}

path tack_dia::actual_boost_model_tack_xml() {
    return resolver::resolve(::actual_boost_model_tack_xml);
}

} } }
