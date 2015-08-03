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
#include "dogen/utility/test_data/resolver.hpp"
#include "dogen/utility/test_data/validating_resolver.hpp"
#include "dogen/utility/test_data/dia_tack.hpp"

using boost::filesystem::path;

namespace {

path data_set("dia_tack");
path non_existent_file("dia_tack/input/non_existent_file.dia");
path input("dia_tack/input");
path input_boost_model_dia("dia_tack/input/boost_model.dia");
path input_std_model_dia("dia_tack/input/std_model.dia");
path input_class_in_a_package_dia("dia_tack/input/class_in_a_package.dia");
path input_compressed_dia("dia_tack/input/compressed.dia");
path input_empty_dia("dia_tack/input/empty.dia");
path input_two_empty_layers_dia("dia_tack/input/two_empty_layers.dia");
path input_stand_alone_class_dia(
    "dia_tack/input/stand_alone_class.dia");
path input_empty_package_dia("dia_tack/input/empty_package.dia");
path input_class_without_name_dia("dia_tack/input/class_without_name.dia");
path input_classes_inout_package_dia(
    "dia_tack/input/classes_inout_package.dia");
path input_class_without_attributes_dia(
    "dia_tack/input/class_without_attributes.dia");
path input_class_without_package_dia("dia_tack/input/class_without_package.dia");
path input_classes_in_a_package_dia("dia_tack/input/classes_in_a_package.dia");
path input_classes_without_package_dia(
    "dia_tack/input/classes_without_package.dia");
path input_package_without_name_dia("dia_tack/input/package_without_name.dia");
path input_two_layers_with_objects_dia(
    "dia_tack/input/two_layers_with_objects.dia");
path input_disable_cmakelists_dia("dia_tack/input/disable_cmakelists.dia");
path input_disable_full_ctor_dia(
    "dia_tack/input/disable_full_ctor.dia"
    );
path input_disable_facet_folders_dia("dia_tack/input/disable_facet_folders.dia");
path input_disable_unique_file_names_dia(
    "dia_tack/input/disable_unique_file_names.dia"
    );
path input_disable_xml_serialization_dia(
    "dia_tack/input/disable_xml_serialization.dia"
    );
path input_enable_facet_domain_dia("dia_tack/input/enable_facet_domain.dia");
path input_enable_facet_hash_dia("dia_tack/input/enable_facet_hash.dia");
path input_enable_facet_io_dia("dia_tack/input/enable_facet_io.dia");
path input_enable_facet_serialization_dia(
    "dia_tack/input/enable_facet_serialization.dia"
    );
path input_enable_eos_serialization_dia("dia_tack/input/eos_serialization.dia");
path input_rename_facet_folder_dia("dia_tack/input/rename_facet_folder.dia");
path input_use_integrated_io_dia("dia_tack/input/use_integrated_io.dia");
path input_all_primitives_dia("dia_tack/input/all_primitives.dia");
path input_split_project_dia("dia_tack/input/split_project.dia");
path input_trivial_inheritance_dia("dia_tack/input/trivial_inheritance.dia");
path input_trivial_association_dia("dia_tack/input/trivial_association.dia");
path input_comments_dia("dia_tack/input/comments.dia");
path input_enumeration_dia("dia_tack/input/enumeration.dia");
path input_exception_dia("dia_tack/input/exception.dia");
path input_stereotypes_dia("dia_tack/input/stereotypes.dia");

path expected(
    "dia_tack/expected");
path expected_class_in_a_package_dia_xml(
    "dia_tack/expected/class_in_a_package.diaxml");
path expected_class_in_a_package_tack_xml(
    "dia_tack/expected/class_in_a_package.tackxml");
path expected_class_in_a_package_cpp_xml(
    "dia_tack/expected/class_in_a_package.cppxml");
path expected_compressed_dia_xml(
    "dia_tack/expected/compressed.diaxml");
path expected_empty_dia_xml(
    "dia_tack/expected/empty.diaxml");
path expected_empty_tack_xml(
    "dia_tack/expected/empty.tackxml");
path expected_empty_cpp_xml(
    "dia_tack/expected/empty.cppxml");
path expected_two_empty_layers_dia_xml(
    "dia_tack/expected/two_empty_layers.diaxml");
path expected_stand_alone_class_dia_xml(
    "dia_tack/expected/stand_alone_class.diaxml");
path expected_empty_package_dia_xml(
    "dia_tack/expected/empty_package.diaxml");
path expected_empty_package_tack_xml(
    "dia_tack/expected/empty_package.tackxml");
path expected_class_without_name_dia_xml(
    "dia_tack/expected/class_without_name.diaxml");
path expected_classes_inout_package_dia_xml(
    "dia_tack/expected/classes_inout_package.diaxml");
path expected_classes_inout_package_tack_xml(
    "dia_tack/expected/classes_inout_package.tackxml");
path expected_class_without_attributes_dia_xml(
    "dia_tack/expected/class_without_attributes.diaxml");
path expected_class_without_attributes_tack_xml(
    "dia_tack/expected/class_without_attributes.tackxml");
path expected_class_without_package_dia_xml(
    "dia_tack/expected/class_without_package.diaxml");
path expected_class_without_package_tack_xml(
    "dia_tack/expected/class_without_package.tackxml");
path expected_classes_in_a_package_dia_xml(
    "dia_tack/expected/classes_in_a_package.diaxml");
path expected_classes_in_a_package_tack_xml(
    "dia_tack/expected/classes_in_a_package.tackxml");
path expected_classes_without_package_dia_xml(
    "dia_tack/expected/classes_without_package.diaxml");
path expected_classes_without_package_tack_xml(
    "dia_tack/expected/classes_without_package.tackxml");
path expected_package_without_name_dia_xml(
    "dia_tack/expected/package_without_name.diaxml");
path expected_two_layers_with_objects_dia_xml(
    "dia_tack/expected/two_layers_with_objects.diaxml");
path expected_two_layers_with_objects_tack_xml(
    "dia_tack/expected/two_layers_with_objects.tackxml");
path expected_class_in_a_package_stdout_txt(
    "dia_tack/expected/class_in_a_package_stdout.txt");
path expected_all_primitives_dia_xml(
    "dia_tack/expected/all_primitives.diaxml");
path expected_all_primitives_tack_xml(
    "dia_tack/expected/all_primitives.tackxml");
path expected_trivial_inheritance_dia_xml(
    "dia_tack/expected/trivial_inheritance.diaxml");
path expected_trivial_inheritance_tack_xml(
    "dia_tack/expected/trivial_inheritance.tackxml");
path expected_trivial_association_dia_xml(
    "dia_tack/expected/trivial_association.diaxml");
path expected_trivial_association_tack_xml(
    "dia_tack/expected/trivial_association.tackxml");
path expected_comments_dia_xml(
    "dia_tack/expected/comments.diaxml");
path expected_comments_tack_xml(
    "dia_tack/expected/comments.tackxml");
path expected_comments_cpp_xml(
    "dia_tack/expected/comments.cppxml");
path expected_enumeration_dia_xml(
    "dia_tack/expected/enumeration.diaxml");
path expected_enumeration_tack_xml(
    "dia_tack/expected/enumeration.tackxml");
path expected_enumeration_cpp_xml(
    "dia_tack/expected/enumeration.cppxml");
path expected_exception_dia_xml(
    "dia_tack/expected/exception.diaxml");
path expected_exception_tack_xml(
    "dia_tack/expected/exception.tackxml");
path expected_exception_cpp_xml(
    "dia_tack/expected/exception.cppxml");
path expected_std_model_dia_xml(
    "dia_tack/expected/std_model.diaxml");
path expected_std_model_tack_xml(
    "dia_tack/expected/std_model.tackxml");
path expected_boost_model_dia_xml(
    "dia_tack/expected/boost_model.diaxml");
path expected_boost_model_tack_xml(
    "dia_tack/expected/boost_model.tackxml");

path actual(
    "dia_tack/actual");
path actual_class_in_a_package_dia_xml(
    "dia_tack/actual/class_in_a_package.diaxml");
path actual_class_in_a_package_tack_xml(
    "dia_tack/actual/class_in_a_package.tackxml");
path actual_class_in_a_package_cpp_xml(
    "dia_tack/actual/class_in_a_package.cppxml");
path actual_compressed_dia_xml(
    "dia_tack/actual/compressed.diaxml");
path actual_empty_dia_xml(
    "dia_tack/actual/empty.diaxml");
path actual_empty_tack_xml(
    "dia_tack/actual/empty.tackxml");
path actual_empty_cpp_xml(
    "dia_tack/actual/empty.cppxml");
path actual_two_empty_layers_dia_xml(
    "dia_tack/actual/two_empty_layers.diaxml");
path actual_stand_alone_class_dia_xml(
    "dia_tack/actual/stand_alone_class.diaxml");
path actual_empty_package_dia_xml(
    "dia_tack/actual/empty_package.diaxml");
path actual_empty_package_tack_xml(
    "dia_tack/actual/empty_package.tackxml");
path actual_class_without_name_dia_xml(
    "dia_tack/actual/class_without_name.diaxml");
path actual_classes_inout_package_dia_xml(
    "dia_tack/actual/classes_inout_package.diaxml");
path actual_classes_inout_package_tack_xml(
    "dia_tack/actual/classes_inout_package.tackxml");
path actual_class_without_attributes_dia_xml(
    "dia_tack/actual/class_without_attributes.diaxml");
path actual_class_without_attributes_tack_xml(
    "dia_tack/actual/class_without_attributes.tackxml");
path actual_class_without_package_dia_xml(
    "dia_tack/actual/class_without_package.diaxml");
path actual_class_without_package_tack_xml(
    "dia_tack/actual/class_without_package.tackxml");
path actual_classes_in_a_package_dia_xml(
    "dia_tack/actual/classes_in_a_package.diaxml");
path actual_classes_without_package_dia_xml(
    "dia_tack/actual/classes_without_package.diaxml");
path actual_classes_without_package_tack_xml(
    "dia_tack/actual/classes_without_package.tackxml");
path actual_package_without_name_dia_xml(
    "dia_tack/actual/package_without_name.diaxml");
path actual_two_layers_with_objects_dia_xml(
    "dia_tack/actual/two_layers_with_objects.diaxml");
path actual_two_layers_with_objects_tack_xml(
    "dia_tack/actual/two_layers_with_objects.tackxml");
path actual_class_in_a_package_stdout_txt(
    "dia_tack/actual/class_in_a_package_stdout.txt");
path actual_all_primitives_dia_xml(
    "dia_tack/actual/all_primitives.diaxml");
path actual_all_primitives_tack_xml(
    "dia_tack/actual/all_primitives.tackxml");
path actual_trivial_inheritance_dia_xml(
    "dia_tack/actual/trivial_inheritance.diaxml");
path actual_trivial_inheritance_tack_xml(
    "dia_tack/actual/trivial_inheritance.tackxml");
path actual_trivial_association_dia_xml(
    "dia_tack/actual/trivial_association.diaxml");
path actual_trivial_association_tack_xml(
    "dia_tack/actual/trivial_association.tackxml");
path actual_comments_dia_xml(
    "dia_tack/actual/comments.diaxml");
path actual_comments_tack_xml(
    "dia_tack/actual/comments.tackxml");
path actual_comments_cpp_xml(
    "dia_tack/actual/comments.cppxml");
path actual_enumeration_dia_xml(
    "dia_tack/actual/enumeration.diaxml");
path actual_enumeration_tack_xml(
    "dia_tack/actual/enumeration.tackxml");
path actual_enumeration_cpp_xml(
    "dia_tack/actual/enumeration.cppxml");
path actual_exception_dia_xml(
    "dia_tack/actual/exception.diaxml");
path actual_exception_tack_xml(
    "dia_tack/actual/exception.tackxml");
path actual_exception_cpp_xml(
    "dia_tack/actual/exception.cppxml");
path actual_std_model_dia_xml(
    "dia_tack/actual/std_model.diaxml");
path actual_std_model_tack_xml(
    "dia_tack/actual/std_model.tackxml");
path actual_boost_model_dia_xml(
    "dia_tack/actual/boost_model.diaxml");
path actual_boost_model_tack_xml(
    "dia_tack/actual/boost_model.tackxml");

}

namespace dogen {
namespace utility {
namespace test_data {

path dia_tack::data_set() {
    return validating_resolver::resolve(::data_set);
}

path dia_tack::non_existent_file() {
    return resolver::resolve(::non_existent_file);
}

path dia_tack::input() {
    return validating_resolver::resolve(::input);
}

path dia_tack::input_boost_model_dia() {
    return validating_resolver::resolve(::input_boost_model_dia);
}

path dia_tack::input_std_model_dia() {
    return validating_resolver::resolve(::input_std_model_dia);
}

path dia_tack::input_class_in_a_package_dia() {
    return validating_resolver::resolve(::input_class_in_a_package_dia);
}

path dia_tack::input_compressed_dia() {
    return validating_resolver::resolve(::input_compressed_dia);
}

path dia_tack::input_empty_dia() {
    return validating_resolver::resolve(::input_empty_dia);
}

path dia_tack::input_two_empty_layers_dia() {
    return validating_resolver::resolve(::input_two_empty_layers_dia);
}

path dia_tack::input_stand_alone_class_dia() {
    return validating_resolver::resolve(::input_stand_alone_class_dia);
}

path dia_tack::input_empty_package_dia() {
    return validating_resolver::resolve(::input_empty_package_dia);
}

path dia_tack::input_class_without_name_dia() {
    return validating_resolver::resolve(::input_class_without_name_dia);
}

path dia_tack::input_classes_inout_package_dia() {
    return validating_resolver::resolve(
        ::input_classes_inout_package_dia);
}

path dia_tack::input_class_without_attributes_dia() {
    return validating_resolver::resolve(::input_class_without_attributes_dia);
}

path dia_tack::input_class_without_package_dia() {
    return validating_resolver::resolve(::input_class_without_package_dia);
}

path dia_tack::input_classes_in_a_package_dia() {
    return validating_resolver::resolve(::input_classes_in_a_package_dia);
}

path dia_tack::input_classes_without_package_dia() {
    return validating_resolver::resolve(::input_classes_without_package_dia);
}

path dia_tack::input_package_without_name_dia() {
    return validating_resolver::resolve(::input_package_without_name_dia);
}

path dia_tack::input_two_layers_with_objects_dia() {
    return validating_resolver::resolve(::input_two_layers_with_objects_dia);
}

path dia_tack::input_disable_cmakelists_dia() {
    return validating_resolver::resolve(::input_disable_cmakelists_dia);
}

path dia_tack::input_disable_full_ctor_dia() {
    return validating_resolver::resolve(
        ::input_disable_full_ctor_dia);
}

path dia_tack::input_disable_facet_folders_dia() {
    return validating_resolver::resolve(::input_disable_facet_folders_dia);
}

path dia_tack::input_disable_unique_file_names_dia() {
    return validating_resolver::resolve(::input_disable_unique_file_names_dia);
}

path dia_tack::input_disable_xml_serialization_dia() {
    return validating_resolver::resolve(::input_disable_xml_serialization_dia);
}

path dia_tack::input_enable_facet_domain_dia() {
    return validating_resolver::resolve(::input_enable_facet_domain_dia);
}

path dia_tack::input_enable_facet_hash_dia() {
    return validating_resolver::resolve(::input_enable_facet_hash_dia);
}

path dia_tack::input_enable_facet_io_dia() {
    return validating_resolver::resolve(::input_enable_facet_io_dia);
}

path dia_tack::input_enable_facet_serialization_dia() {
    return validating_resolver::resolve(::input_enable_facet_serialization_dia);
}

path dia_tack::input_enable_eos_serialization_dia() {
    return validating_resolver::resolve(::input_enable_eos_serialization_dia);
}

path dia_tack::input_rename_facet_folder_dia() {
    return validating_resolver::resolve(::input_rename_facet_folder_dia);
}

path dia_tack::input_use_integrated_io_dia() {
    return validating_resolver::resolve(::input_use_integrated_io_dia);
}

path dia_tack::input_all_primitives_dia() {
    return validating_resolver::resolve(::input_all_primitives_dia);
}

path dia_tack::input_trivial_inheritance_dia() {
    return validating_resolver::resolve(::input_trivial_inheritance_dia);
}

path dia_tack::input_trivial_association_dia() {
    return validating_resolver::resolve(::input_trivial_association_dia);
}

path dia_tack::input_comments_dia() {
    return validating_resolver::resolve(::input_comments_dia);
}

path dia_tack::input_enumeration_dia() {
    return validating_resolver::resolve(::input_enumeration_dia);
}

path dia_tack::input_exception_dia() {
    return validating_resolver::resolve(::input_exception_dia);
}

path dia_tack::input_split_project_dia() {
    return validating_resolver::resolve(::input_split_project_dia);
}

path dia_tack::input_stereotypes_dia() {
    return validating_resolver::resolve(::input_stereotypes_dia);
}

path dia_tack::expected() {
    return validating_resolver::resolve(::expected);
}

path dia_tack::expected_class_in_a_package_dia_xml() {
    return validating_resolver::resolve(::expected_class_in_a_package_dia_xml);
}

path dia_tack::expected_class_in_a_package_tack_xml() {
    return validating_resolver::resolve(::expected_class_in_a_package_tack_xml);
}

path dia_tack::expected_class_in_a_package_cpp_xml() {
    return validating_resolver::resolve(::expected_class_in_a_package_cpp_xml);
}

path dia_tack::expected_compressed_dia_xml() {
    return validating_resolver::resolve(::expected_compressed_dia_xml);
}

path dia_tack::expected_empty_dia_xml() {
    return validating_resolver::resolve(::expected_empty_dia_xml);
}

path dia_tack::expected_empty_tack_xml() {
    return validating_resolver::resolve(::expected_empty_tack_xml);
}

path dia_tack::expected_empty_cpp_xml() {
    return resolver::resolve(::expected_empty_cpp_xml);
}

path dia_tack::expected_two_empty_layers_dia_xml() {
    return validating_resolver::resolve(::expected_two_empty_layers_dia_xml);
}

path dia_tack::expected_stand_alone_class_dia_xml() {
    return validating_resolver::resolve(
        ::expected_stand_alone_class_dia_xml);
}

path dia_tack::expected_empty_package_dia_xml() {
    return validating_resolver::resolve(::expected_empty_package_dia_xml);
}

path dia_tack::expected_empty_package_tack_xml() {
    return validating_resolver::resolve(::expected_empty_package_tack_xml);
}

path dia_tack::expected_class_without_name_dia_xml() {
    return validating_resolver::resolve(
        ::expected_class_without_name_dia_xml);
}

path dia_tack::expected_classes_inout_package_dia_xml() {
    return validating_resolver::resolve(
        ::expected_classes_inout_package_dia_xml);
}

path dia_tack::expected_classes_inout_package_tack_xml() {
    return validating_resolver::resolve(
        ::expected_classes_inout_package_tack_xml);
}

path dia_tack::expected_class_without_attributes_dia_xml() {
    return validating_resolver::resolve(
        ::expected_class_without_attributes_dia_xml);
}

path dia_tack::expected_class_without_attributes_tack_xml() {
    return validating_resolver::resolve(
        ::expected_class_without_attributes_tack_xml);
}

path dia_tack::expected_class_without_package_dia_xml() {
    return validating_resolver::resolve(
        ::expected_class_without_package_dia_xml);
}

path dia_tack::expected_class_without_package_tack_xml() {
    return validating_resolver::resolve(
        ::expected_class_without_package_tack_xml);
}

path dia_tack::expected_classes_in_a_package_dia_xml() {
    return validating_resolver::resolve(
        ::expected_classes_in_a_package_dia_xml);
}

path dia_tack::expected_classes_without_package_dia_xml() {
    return validating_resolver::resolve(
        ::expected_classes_without_package_dia_xml);
}

path dia_tack::expected_classes_without_package_tack_xml() {
    return validating_resolver::resolve(
        ::expected_classes_without_package_tack_xml);
}

path dia_tack::expected_package_without_name_dia_xml() {
    return validating_resolver::resolve(
        ::expected_package_without_name_dia_xml);
}

path dia_tack::expected_class_in_a_package_stdout_txt() {
    return validating_resolver::resolve(
        ::expected_class_in_a_package_stdout_txt);
}

path dia_tack::expected_two_layers_with_objects_dia_xml() {
    return validating_resolver::resolve(
        ::expected_two_layers_with_objects_dia_xml);
}

path dia_tack::expected_two_layers_with_objects_tack_xml() {
    return validating_resolver::resolve(
        ::expected_two_layers_with_objects_tack_xml);
}

path dia_tack::expected_all_primitives_dia_xml() {
    return validating_resolver::resolve(::expected_all_primitives_dia_xml);
}

path dia_tack::expected_all_primitives_tack_xml() {
    return validating_resolver::resolve(::expected_all_primitives_tack_xml);
}

path dia_tack::expected_trivial_inheritance_dia_xml() {
    return validating_resolver::resolve(::expected_trivial_inheritance_dia_xml);
}

path dia_tack::expected_trivial_inheritance_tack_xml() {
    return validating_resolver::resolve(::expected_trivial_inheritance_tack_xml);
}

path dia_tack::expected_comments_dia_xml() {
    return validating_resolver::resolve(::expected_comments_dia_xml);
}

path dia_tack::expected_comments_tack_xml() {
    return validating_resolver::resolve(::expected_comments_tack_xml);
}

path dia_tack::expected_comments_cpp_xml() {
    return validating_resolver::resolve(::expected_comments_cpp_xml);
}

path dia_tack::expected_enumeration_dia_xml() {
    return validating_resolver::resolve(::expected_enumeration_dia_xml);
}

path dia_tack::expected_enumeration_tack_xml() {
    return validating_resolver::resolve(::expected_enumeration_tack_xml);
}

path dia_tack::expected_enumeration_cpp_xml() {
    return resolver::resolve(::expected_enumeration_cpp_xml);
}

path dia_tack::expected_exception_dia_xml() {
    return resolver::resolve(::expected_exception_dia_xml);
}

path dia_tack::expected_exception_tack_xml() {
    return resolver::resolve(::expected_exception_tack_xml);
}

path dia_tack::expected_exception_cpp_xml() {
    return resolver::resolve(::expected_exception_cpp_xml);
}

path dia_tack::expected_std_model_dia_xml() {
    return validating_resolver::resolve(::expected_std_model_dia_xml);
}

path dia_tack::expected_std_model_tack_xml() {
    return validating_resolver::resolve(::expected_std_model_tack_xml);
}

path dia_tack::expected_boost_model_dia_xml() {
    return validating_resolver::resolve(::expected_boost_model_dia_xml);
}

path dia_tack::expected_boost_model_tack_xml() {
    return validating_resolver::resolve(::expected_boost_model_tack_xml);
}

path dia_tack::actual() {
    return validating_resolver::resolve(::actual);
}

path dia_tack::actual_class_in_a_package_dia_xml() {
    return resolver::resolve(::actual_class_in_a_package_dia_xml);
}

path dia_tack::actual_class_in_a_package_tack_xml() {
    return resolver::resolve(::actual_class_in_a_package_tack_xml);
}

path dia_tack::actual_class_in_a_package_cpp_xml() {
    return resolver::resolve(::actual_class_in_a_package_cpp_xml);
}

path dia_tack::actual_compressed_dia_xml() {
    return resolver::resolve(::actual_compressed_dia_xml);
}

path dia_tack::actual_empty_dia_xml() {
    return resolver::resolve(::actual_empty_dia_xml);
}

path dia_tack::actual_empty_tack_xml() {
    return resolver::resolve(::actual_empty_tack_xml);
}

path dia_tack::actual_empty_cpp_xml() {
    return resolver::resolve(::actual_empty_cpp_xml);
}

path dia_tack::actual_two_empty_layers_dia_xml() {
    return resolver::resolve(::actual_two_empty_layers_dia_xml);
}

path dia_tack::actual_stand_alone_class_dia_xml() {
    return resolver::resolve(::actual_stand_alone_class_dia_xml);
}

path dia_tack::actual_empty_package_dia_xml() {
    return resolver::resolve(::actual_empty_package_dia_xml);
}

path dia_tack::actual_empty_package_tack_xml() {
    return resolver::resolve(::actual_empty_package_tack_xml);
}

path dia_tack::actual_class_without_name_dia_xml() {
    return resolver::resolve(::actual_class_without_name_dia_xml);
}

path dia_tack::actual_classes_inout_package_dia_xml() {
    return resolver::resolve(::actual_classes_inout_package_dia_xml);
}

path dia_tack::actual_classes_inout_package_tack_xml() {
    return resolver::resolve(::actual_classes_inout_package_tack_xml);
}

path dia_tack::actual_class_without_attributes_dia_xml() {
    return resolver::resolve(::actual_class_without_attributes_dia_xml);
}

path dia_tack::actual_class_without_attributes_tack_xml() {
    return resolver::resolve(::actual_class_without_attributes_tack_xml);
}

path dia_tack::actual_class_without_package_dia_xml() {
    return resolver::resolve(::actual_class_without_package_dia_xml);
}

path dia_tack::actual_class_without_package_tack_xml() {
    return resolver::resolve(::actual_class_without_package_tack_xml);
}

path dia_tack::actual_classes_in_a_package_dia_xml() {
    return resolver::resolve(
        ::actual_classes_in_a_package_dia_xml);
}

path dia_tack::actual_classes_without_package_dia_xml() {
    return resolver::resolve(::actual_classes_without_package_dia_xml);
}

path dia_tack::actual_classes_without_package_tack_xml() {
    return resolver::resolve(::actual_classes_without_package_tack_xml);
}

path dia_tack::actual_package_without_name_dia_xml() {
    return resolver::resolve(::actual_package_without_name_dia_xml);
}

path dia_tack::actual_two_layers_with_objects_dia_xml() {
    return resolver::resolve(::actual_two_layers_with_objects_dia_xml);
}

path dia_tack::actual_two_layers_with_objects_tack_xml() {
    return resolver::resolve(::actual_two_layers_with_objects_tack_xml);
}

path dia_tack::actual_class_in_a_package_stdout_txt() {
    return resolver::resolve(::actual_class_in_a_package_stdout_txt);
}

path dia_tack::actual_trivial_inheritance_dia_xml() {
    return resolver::resolve(::actual_trivial_inheritance_dia_xml);
}

path dia_tack::actual_trivial_inheritance_tack_xml() {
    return resolver::resolve(::actual_trivial_inheritance_tack_xml);
}

path dia_tack::actual_all_primitives_dia_xml() {
    return resolver::resolve(::actual_all_primitives_dia_xml);
}

path dia_tack::actual_all_primitives_tack_xml() {
    return resolver::resolve(::actual_all_primitives_tack_xml);
}

path dia_tack::actual_comments_dia_xml() {
    return resolver::resolve(::actual_comments_dia_xml);
}

path dia_tack::actual_comments_tack_xml() {
    return resolver::resolve(::actual_comments_tack_xml);
}

path dia_tack::actual_comments_cpp_xml() {
    return resolver::resolve(::actual_comments_cpp_xml);
}

path dia_tack::actual_enumeration_dia_xml() {
    return resolver::resolve(::actual_enumeration_dia_xml);
}

path dia_tack::actual_enumeration_tack_xml() {
    return resolver::resolve(::actual_enumeration_tack_xml);
}

path dia_tack::actual_enumeration_cpp_xml() {
    return resolver::resolve(::actual_enumeration_cpp_xml);
}

path dia_tack::actual_exception_dia_xml() {
    return resolver::resolve(::actual_exception_dia_xml);
}

path dia_tack::actual_exception_tack_xml() {
    return resolver::resolve(::actual_exception_tack_xml);
}

path dia_tack::actual_exception_cpp_xml() {
    return resolver::resolve(::actual_exception_cpp_xml);
}

path dia_tack::actual_std_model_dia_xml() {
    return resolver::resolve(::actual_std_model_dia_xml);
}

path dia_tack::actual_std_model_tack_xml() {
    return resolver::resolve(::actual_std_model_tack_xml);
}

path dia_tack::actual_boost_model_dia_xml() {
    return resolver::resolve(::actual_boost_model_dia_xml);
}

path dia_tack::actual_boost_model_tack_xml() {
    return resolver::resolve(::actual_boost_model_tack_xml);
}

} } }
