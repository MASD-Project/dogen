/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/utility/test_data/resolver.hpp"
#include "dogen/utility/test_data/validating_resolver.hpp"
#include "dogen/utility/test_data/dia_sml.hpp"

using boost::filesystem::path;

namespace {

path data_set("dia_sml");
path non_existent_file("dia_sml/input/non_existent_file.dia");
path input("dia_sml/input");
path input_class_in_a_package_dia("dia_sml/input/class_in_a_package.dia");
path input_compressed_dia("dia_sml/input/compressed.dia");
path input_empty_dia("dia_sml/input/empty.dia");
path input_two_empty_layers_dia("dia_sml/input/two_empty_layers.dia");
path input_stand_alone_class_dia(
    "dia_sml/input/stand_alone_class.dia");
path input_empty_package_dia("dia_sml/input/empty_package.dia");
path input_class_without_name_dia("dia_sml/input/class_without_name.dia");
path input_classes_inout_package_dia(
    "dia_sml/input/classes_inout_package.dia");
path input_class_without_attributes_dia(
    "dia_sml/input/class_without_attributes.dia");
path input_class_without_package_dia("dia_sml/input/class_without_package.dia");
path input_classes_in_a_package_dia("dia_sml/input/classes_in_a_package.dia");
path input_classes_without_package_dia(
    "dia_sml/input/classes_without_package.dia");
path input_package_without_name_dia("dia_sml/input/package_without_name.dia");
path input_two_layers_with_objects_dia(
    "dia_sml/input/two_layers_with_objects.dia");
path input_disable_cmakelists_dia("dia_sml/input/disable_cmakelists.dia");
path input_disable_complete_constructor_dia(
    "dia_sml/input/disable_complete_constructor.dia"
    );
path input_disable_facet_folders_dia("dia_sml/input/disable_facet_folders.dia");
path input_disable_model_package_dia("dia_sml/input/disable_model_package.dia");
path input_disable_unique_file_names_dia(
    "dia_sml/input/disable_unique_file_names.dia"
    );
path input_disable_xml_serialization_dia(
    "dia_sml/input/disable_xml_serialization.dia"
    );
path input_enable_facet_domain_dia("dia_sml/input/enable_facet_domain.dia");
path input_enable_facet_hash_dia("dia_sml/input/enable_facet_hash.dia");
path input_enable_facet_io_dia("dia_sml/input/enable_facet_io.dia");
path input_enable_facet_serialization_dia(
    "dia_sml/input/enable_facet_serialization.dia"
    );
path input_rename_facet_folder_dia("dia_sml/input/rename_facet_folder.dia");
path input_use_integrated_io_dia("dia_sml/input/use_integrated_io.dia");
path input_all_primitives_dia("dia_sml/input/all_primitives.dia");
path input_split_project_dia("dia_sml/input/split_project.dia");

path expected(
    "dia_sml/expected");
path expected_class_in_a_package_dia_xml(
    "dia_sml/expected/class_in_a_package.diaxml");
path expected_class_in_a_package_sml_xml(
    "dia_sml/expected/class_in_a_package.smlxml");
path expected_compressed_dia_xml(
    "dia_sml/expected/compressed.diaxml");
path expected_empty_dia_xml(
    "dia_sml/expected/empty.diaxml");
path expected_two_empty_layers_dia_xml(
    "dia_sml/expected/two_empty_layers.diaxml");
path expected_stand_alone_class_dia_xml(
    "dia_sml/expected/stand_alone_class.diaxml");
path expected_empty_package_dia_xml(
    "dia_sml/expected/empty_package.diaxml");
path expected_class_without_name_dia_xml(
    "dia_sml/expected/class_without_name.diaxml");
path expected_classes_inout_package_dia_xml(
    "dia_sml/expected/classes_inout_package.diaxml");
path expected_class_without_attributes_dia_xml(
    "dia_sml/expected/class_without_attributes.diaxml");
path expected_class_without_package_dia_xml(
    "dia_sml/expected/class_without_package.diaxml");
path expected_classes_in_a_package_dia_xml(
    "dia_sml/expected/classes_in_a_package.diaxml");
path expected_classes_without_package_dia_xml(
    "dia_sml/expected/classes_without_package.diaxml");
path expected_package_without_name_dia_xml(
    "dia_sml/expected/package_without_name.diaxml");
path expected_two_layers_with_objects_dia_xml(
    "dia_sml/expected/two_layers_with_objects.diaxml");
path expected_class_in_a_package_stdout_txt(
    "dia_sml/expected/class_in_a_package_stdout.txt");

path actual(
    "dia_sml/actual");
path actual_class_in_a_package_dia_xml(
    "dia_sml/actual/class_in_a_package.diaxml");
path actual_class_in_a_package_sml_xml(
    "dia_sml/actual/class_in_a_package.smlxml");
path actual_compressed_dia_xml(
    "dia_sml/actual/compressed.diaxml");
path actual_empty_dia_xml(
    "dia_sml/actual/empty.diaxml");
path actual_two_empty_layers_dia_xml(
    "dia_sml/actual/two_empty_layers.diaxml");
path actual_stand_alone_class_dia_xml(
    "dia_sml/actual/stand_alone_class.diaxml");
path actual_empty_package_dia_xml(
    "dia_sml/actual/empty_package.diaxml");
path actual_class_without_name_dia_xml(
    "dia_sml/actual/class_without_name.diaxml");
path actual_classes_inout_package_dia_xml(
    "dia_sml/actual/classes_inout_package.diaxml");
path actual_class_without_attributes_dia_xml(
    "dia_sml/actual/class_without_attributes.diaxml");
path actual_class_without_package_dia_xml(
    "dia_sml/actual/class_without_package.diaxml");
path actual_classes_in_a_package_dia_xml(
    "dia_sml/actual/classes_in_a_package.diaxml");
path actual_classes_without_package_dia_xml(
    "dia_sml/actual/classes_without_package.diaxml");
path actual_package_without_name_dia_xml(
    "dia_sml/actual/package_without_name.diaxml");
path actual_two_layers_with_objects_dia_xml(
    "dia_sml/actual/two_layers_with_objects.diaxml");
path actual_class_in_a_package_stdout_txt(
    "dia_sml/actual/class_in_a_package_stdout.txt");

}

namespace dogen {
namespace utility {
namespace test_data {

path dia_sml::data_set() {
    return validating_resolver::resolve(::data_set);
}

path dia_sml::non_existent_file() {
    return resolver::resolve(::non_existent_file);
}

path dia_sml::input() {
    return validating_resolver::resolve(::input);
}

path dia_sml::input_class_in_a_package_dia() {
    return validating_resolver::resolve(::input_class_in_a_package_dia);
}

path dia_sml::input_compressed_dia() {
    return validating_resolver::resolve(::input_compressed_dia);
}

path dia_sml::input_empty_dia() {
    return validating_resolver::resolve(::input_empty_dia);
}

path dia_sml::input_two_empty_layers_dia() {
    return validating_resolver::resolve(::input_two_empty_layers_dia);
}

path dia_sml::input_stand_alone_class_dia() {
    return validating_resolver::resolve(
        ::input_stand_alone_class_dia);
}

path dia_sml::input_empty_package_dia() {
    return validating_resolver::resolve(::input_empty_package_dia);
}

path dia_sml::input_class_without_name_dia() {
    return validating_resolver::resolve(::input_class_without_name_dia);
}

path dia_sml::input_classes_inout_package_dia() {
    return validating_resolver::resolve(
        ::input_classes_inout_package_dia);
}

path dia_sml::input_class_without_attributes_dia() {
    return validating_resolver::resolve(::input_class_without_attributes_dia);
}

path dia_sml::input_class_without_package_dia() {
    return validating_resolver::resolve(::input_class_without_package_dia);
}

path dia_sml::input_classes_in_a_package_dia() {
    return validating_resolver::resolve(::input_classes_in_a_package_dia);
}

path dia_sml::input_classes_without_package_dia() {
    return validating_resolver::resolve(::input_classes_without_package_dia);
}

path dia_sml::input_package_without_name_dia() {
    return validating_resolver::resolve(::input_package_without_name_dia);
}

path dia_sml::input_two_layers_with_objects_dia() {
    return validating_resolver::resolve(::input_two_layers_with_objects_dia);
}

path dia_sml::input_disable_cmakelists_dia() {
    return validating_resolver::resolve(::input_disable_cmakelists_dia);
}

path dia_sml::input_disable_complete_constructor_dia() {
    return validating_resolver::resolve(
        ::input_disable_complete_constructor_dia);
}

path dia_sml::input_disable_facet_folders_dia() {
    return validating_resolver::resolve(::input_disable_facet_folders_dia);
}

path dia_sml::input_disable_model_package_dia() {
    return validating_resolver::resolve(::input_disable_model_package_dia);
}

path dia_sml::input_disable_unique_file_names_dia() {
    return validating_resolver::resolve(::input_disable_unique_file_names_dia);
}

path dia_sml::input_disable_xml_serialization_dia() {
    return validating_resolver::resolve(::input_disable_xml_serialization_dia);
}

path dia_sml::input_enable_facet_domain_dia() {
    return validating_resolver::resolve(::input_enable_facet_domain_dia);
}

path dia_sml::input_enable_facet_hash_dia() {
    return validating_resolver::resolve(::input_enable_facet_hash_dia);
}

path dia_sml::input_enable_facet_io_dia() {
    return validating_resolver::resolve(::input_enable_facet_io_dia);
}

path dia_sml::input_enable_facet_serialization_dia() {
    return validating_resolver::resolve(::input_enable_facet_serialization_dia);
}

path dia_sml::input_rename_facet_folder_dia() {
    return validating_resolver::resolve(::input_rename_facet_folder_dia);
}

path dia_sml::input_use_integrated_io_dia() {
    return validating_resolver::resolve(::input_use_integrated_io_dia);
}

path dia_sml::input_all_primitives_dia() {
    return validating_resolver::resolve(::input_all_primitives_dia);
}

path dia_sml::input_split_project_dia() {
    return validating_resolver::resolve(::input_split_project_dia);
}

path dia_sml::expected() {
    return validating_resolver::resolve(::expected);
}

path dia_sml::expected_class_in_a_package_dia_xml() {
    return validating_resolver::resolve(::expected_class_in_a_package_dia_xml);
}

path dia_sml::expected_class_in_a_package_sml_xml() {
    return validating_resolver::resolve(::expected_class_in_a_package_sml_xml);
}

path dia_sml::expected_compressed_dia_xml() {
    return validating_resolver::resolve(::expected_compressed_dia_xml);
}

path dia_sml::expected_empty_dia_xml() {
    return validating_resolver::resolve(::expected_empty_dia_xml);
}

path dia_sml::expected_two_empty_layers_dia_xml() {
    return validating_resolver::resolve(::expected_two_empty_layers_dia_xml);
}

path dia_sml::expected_stand_alone_class_dia_xml() {
    return validating_resolver::resolve(
        ::expected_stand_alone_class_dia_xml);
}

path dia_sml::expected_empty_package_dia_xml() {
    return validating_resolver::resolve(
        ::expected_empty_package_dia_xml);
}

path dia_sml::expected_class_without_name_dia_xml() {
    return validating_resolver::resolve(
        ::expected_class_without_name_dia_xml);
}

path dia_sml::expected_classes_inout_package_dia_xml() {
    return validating_resolver::resolve(
        ::expected_classes_inout_package_dia_xml);
}

path dia_sml::expected_class_without_attributes_dia_xml() {
    return validating_resolver::resolve(
        ::expected_class_without_attributes_dia_xml);
}

path dia_sml::expected_class_without_package_dia_xml() {
    return validating_resolver::resolve(
        ::expected_class_without_package_dia_xml);
}

path dia_sml::expected_classes_in_a_package_dia_xml() {
    return validating_resolver::resolve(
        ::expected_classes_in_a_package_dia_xml);
}

path dia_sml::expected_classes_without_package_dia_xml() {
    return validating_resolver::resolve(
        ::expected_classes_without_package_dia_xml);
}

path dia_sml::expected_package_without_name_dia_xml() {
    return validating_resolver::resolve(
        ::expected_package_without_name_dia_xml);
}

path dia_sml::expected_class_in_a_package_stdout_txt() {
    return validating_resolver::resolve(
        ::expected_class_in_a_package_stdout_txt);
}

path dia_sml::expected_two_layers_with_objects_dia_xml() {
    return validating_resolver::resolve(
        ::expected_two_layers_with_objects_dia_xml);
}

path dia_sml::actual() {
    return validating_resolver::resolve(::actual);
}

path dia_sml::actual_class_in_a_package_dia_xml() {
    return resolver::resolve(::actual_class_in_a_package_dia_xml);
}

path dia_sml::actual_class_in_a_package_sml_xml() {
    return resolver::resolve(::actual_class_in_a_package_sml_xml);
}

path dia_sml::actual_compressed_dia_xml() {
    return resolver::resolve(::actual_compressed_dia_xml);
}

path dia_sml::actual_empty_dia_xml() {
    return resolver::resolve(::actual_empty_dia_xml);
}

path dia_sml::actual_two_empty_layers_dia_xml() {
    return resolver::resolve(::actual_two_empty_layers_dia_xml);
}

path dia_sml::actual_stand_alone_class_dia_xml() {
    return resolver::resolve(
        ::actual_stand_alone_class_dia_xml);
}

path dia_sml::actual_empty_package_dia_xml() {
    return resolver::resolve(
        ::actual_empty_package_dia_xml);
}

path dia_sml::actual_class_without_name_dia_xml() {
    return resolver::resolve(
        ::actual_class_without_name_dia_xml);
}

path dia_sml::actual_classes_inout_package_dia_xml() {
    return resolver::resolve(
        ::actual_classes_inout_package_dia_xml);
}

path dia_sml::actual_class_without_attributes_dia_xml() {
    return resolver::resolve(
        ::actual_class_without_attributes_dia_xml);
}

path dia_sml::actual_class_without_package_dia_xml() {
    return resolver::resolve(
        ::actual_class_without_package_dia_xml);
}

path dia_sml::actual_classes_in_a_package_dia_xml() {
    return resolver::resolve(
        ::actual_classes_in_a_package_dia_xml);
}

path dia_sml::actual_classes_without_package_dia_xml() {
    return resolver::resolve(
        ::actual_classes_without_package_dia_xml);
}

path dia_sml::actual_package_without_name_dia_xml() {
    return resolver::resolve(
        ::actual_package_without_name_dia_xml);
}

path dia_sml::actual_two_layers_with_objects_dia_xml() {
    return resolver::resolve(
        ::actual_two_layers_with_objects_dia_xml);
}

path dia_sml::actual_class_in_a_package_stdout_txt() {
    return resolver::resolve(
        ::actual_class_in_a_package_stdout_txt);
}

} } }
