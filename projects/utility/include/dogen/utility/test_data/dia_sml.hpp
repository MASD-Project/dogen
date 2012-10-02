/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_TEST_DATA_DIA_SML_HPP
#define DOGEN_UTILITY_TEST_DATA_DIA_SML_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>

namespace dogen {
namespace utility {
namespace test_data {

class dia_sml {
public:
    dia_sml() = delete;
    dia_sml(const dia_sml&) = delete;
    ~dia_sml() = delete;
    dia_sml(dia_sml&&) = delete;
    dia_sml& operator=(const dia_sml&) = delete;

public:
    static boost::filesystem::path data_set();
    static boost::filesystem::path non_existent_file();

    static boost::filesystem::path input();
    static boost::filesystem::path input_class_in_a_package_dia();
    static boost::filesystem::path input_compressed_dia();
    static boost::filesystem::path input_empty_dia();
    static boost::filesystem::path input_two_empty_layers_dia();
    static boost::filesystem::path input_stand_alone_class_dia();
    static boost::filesystem::path input_empty_package_dia();
    static boost::filesystem::path input_class_without_name_dia();
    static boost::filesystem::path input_classes_inout_package_dia();
    static boost::filesystem::path input_class_without_attributes_dia();
    static boost::filesystem::path input_class_without_package_dia();
    static boost::filesystem::path input_classes_in_a_package_dia();
    static boost::filesystem::path input_classes_without_package_dia();
    static boost::filesystem::path input_package_without_name_dia();
    static boost::filesystem::path input_two_layers_with_objects_dia();
    static boost::filesystem::path input_disable_cmakelists_dia();
    static boost::filesystem::path input_disable_complete_constructor_dia();
    static boost::filesystem::path input_disable_facet_folders_dia();
    static boost::filesystem::path input_disable_model_package_dia();
    static boost::filesystem::path input_disable_unique_file_names_dia();
    static boost::filesystem::path input_disable_xml_serialization_dia();
    static boost::filesystem::path input_enable_facet_domain_dia();
    static boost::filesystem::path input_enable_facet_hash_dia();
    static boost::filesystem::path input_enable_facet_io_dia();
    static boost::filesystem::path input_enable_facet_serialization_dia();
    static boost::filesystem::path input_rename_facet_folder_dia();
    static boost::filesystem::path input_use_integrated_io_dia();
    static boost::filesystem::path input_all_primitives_dia();

    static boost::filesystem::path expected();
    static boost::filesystem::path expected_class_in_a_package_dia_xml();
    static boost::filesystem::path expected_class_in_a_package_sml_xml();
    static boost::filesystem::path expected_compressed_dia_xml();
    static boost::filesystem::path expected_empty_dia_xml();
    static boost::filesystem::path expected_two_empty_layers_dia_xml();
    static boost::filesystem::path expected_stand_alone_class_dia_xml();
    static boost::filesystem::path expected_empty_package_dia_xml();
    static boost::filesystem::path expected_class_without_name_dia_xml();
    static boost::filesystem::path expected_classes_inout_package_dia_xml();
    static boost::filesystem::path expected_class_without_attributes_dia_xml();
    static boost::filesystem::path expected_class_without_package_dia_xml();
    static boost::filesystem::path expected_classes_in_a_package_dia_xml();
    static boost::filesystem::path expected_classes_without_package_dia_xml();
    static boost::filesystem::path expected_package_without_name_dia_xml();
    static boost::filesystem::path expected_two_layers_with_objects_dia_xml();
    static boost::filesystem::path expected_class_in_a_package_stdout_txt();

    static boost::filesystem::path actual();
    static boost::filesystem::path actual_class_in_a_package_dia_xml();
    static boost::filesystem::path actual_class_in_a_package_sml_xml();
    static boost::filesystem::path actual_compressed_dia_xml();
    static boost::filesystem::path actual_empty_dia_xml();
    static boost::filesystem::path actual_two_empty_layers_dia_xml();
    static boost::filesystem::path actual_stand_alone_class_dia_xml();
    static boost::filesystem::path actual_empty_package_dia_xml();
    static boost::filesystem::path actual_class_without_name_dia_xml();
    static boost::filesystem::path actual_classes_inout_package_dia_xml();
    static boost::filesystem::path actual_class_without_attributes_dia_xml();
    static boost::filesystem::path actual_class_without_package_dia_xml();
    static boost::filesystem::path actual_classes_in_a_package_dia_xml();
    static boost::filesystem::path actual_classes_without_package_dia_xml();
    static boost::filesystem::path actual_package_without_name_dia_xml();
    static boost::filesystem::path actual_two_layers_with_objects_dia_xml();
    static boost::filesystem::path actual_class_in_a_package_stdout_txt();
};

} } }

#endif
