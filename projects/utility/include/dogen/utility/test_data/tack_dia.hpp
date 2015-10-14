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
#ifndef DOGEN_UTILITY_TEST_DATA_TACK_DIA_HPP
#define DOGEN_UTILITY_TEST_DATA_TACK_DIA_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>

namespace dogen {
namespace utility {
namespace test_data {

class tack_dia {
public:
    tack_dia() = delete;
    tack_dia(const tack_dia&) = delete;
    ~tack_dia() = delete;
    tack_dia(tack_dia&&) = delete;
    tack_dia& operator=(const tack_dia&) = delete;

public:
    static boost::filesystem::path data_set();
    static boost::filesystem::path non_existent_file();

    static boost::filesystem::path input();
    static boost::filesystem::path input_boost_model_dia();
    static boost::filesystem::path input_std_model_dia();
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
    static boost::filesystem::path input_disable_full_ctor_dia();
    static boost::filesystem::path input_disable_facet_folders_dia();
    static boost::filesystem::path input_disable_unique_file_names_dia();
    static boost::filesystem::path input_disable_xml_serialization_dia();
    static boost::filesystem::path input_enable_facet_domain_dia();
    static boost::filesystem::path input_enable_facet_hash_dia();
    static boost::filesystem::path input_enable_facet_io_dia();
    static boost::filesystem::path input_enable_facet_serialization_dia();
        static boost::filesystem::path input_rename_facet_folder_dia();
    static boost::filesystem::path input_use_integrated_io_dia();
    static boost::filesystem::path input_all_primitives_dia();
    static boost::filesystem::path input_trivial_inheritance_dia();
    static boost::filesystem::path input_trivial_association_dia();
    static boost::filesystem::path input_comments_dia();
    static boost::filesystem::path input_enumeration_dia();
    static boost::filesystem::path input_exception_dia();
    static boost::filesystem::path input_stereotypes_dia();

    static boost::filesystem::path expected();
    static boost::filesystem::path expected_class_in_a_package_dia_xml();
    static boost::filesystem::path expected_class_in_a_package_tack_xml();
    static boost::filesystem::path expected_class_in_a_package_cpp_xml();
    static boost::filesystem::path expected_compressed_dia_xml();
    static boost::filesystem::path expected_empty_dia_xml();
    static boost::filesystem::path expected_empty_tack_xml();
    static boost::filesystem::path expected_empty_cpp_xml();
    static boost::filesystem::path expected_two_empty_layers_dia_xml();
    static boost::filesystem::path expected_stand_alone_class_dia_xml();
    static boost::filesystem::path expected_empty_package_dia_xml();
    static boost::filesystem::path expected_empty_package_tack_xml();
    static boost::filesystem::path expected_class_without_name_dia_xml();
    static boost::filesystem::path expected_classes_inout_package_dia_xml();
    static boost::filesystem::path expected_classes_inout_package_tack_xml();
    static boost::filesystem::path expected_class_without_attributes_dia_xml();
    static boost::filesystem::path expected_class_without_attributes_tack_xml();
    static boost::filesystem::path expected_class_without_package_dia_xml();
    static boost::filesystem::path expected_class_without_package_tack_xml();
    static boost::filesystem::path expected_classes_in_a_package_dia_xml();
    static boost::filesystem::path expected_classes_without_package_dia_xml();
    static boost::filesystem::path expected_classes_without_package_tack_xml();
    static boost::filesystem::path expected_package_without_name_dia_xml();
    static boost::filesystem::path expected_two_layers_with_objects_dia_xml();
    static boost::filesystem::path expected_two_layers_with_objects_tack_xml();
    static boost::filesystem::path expected_class_in_a_package_stdout_txt();
    static boost::filesystem::path expected_all_primitives_dia_xml();
    static boost::filesystem::path expected_all_primitives_tack_xml();
    static boost::filesystem::path expected_trivial_inheritance_dia_xml();
    static boost::filesystem::path expected_trivial_inheritance_tack_xml();
    static boost::filesystem::path expected_comments_dia_xml();
    static boost::filesystem::path expected_comments_tack_xml();
    static boost::filesystem::path expected_comments_cpp_xml();
    static boost::filesystem::path expected_enumeration_dia_xml();
    static boost::filesystem::path expected_enumeration_tack_xml();
    static boost::filesystem::path expected_enumeration_cpp_xml();
    static boost::filesystem::path expected_exception_dia_xml();
    static boost::filesystem::path expected_exception_tack_xml();
    static boost::filesystem::path expected_exception_cpp_xml();
    static boost::filesystem::path expected_std_model_dia_xml();
    static boost::filesystem::path expected_std_model_tack_xml();
    static boost::filesystem::path expected_boost_model_dia_xml();
    static boost::filesystem::path expected_boost_model_tack_xml();

    static boost::filesystem::path actual();
    static boost::filesystem::path actual_class_in_a_package_dia_xml();
    static boost::filesystem::path actual_class_in_a_package_tack_xml();
    static boost::filesystem::path actual_class_in_a_package_cpp_xml();
    static boost::filesystem::path actual_compressed_dia_xml();
    static boost::filesystem::path actual_empty_dia_xml();
    static boost::filesystem::path actual_empty_tack_xml();
    static boost::filesystem::path actual_empty_cpp_xml();
    static boost::filesystem::path actual_two_empty_layers_dia_xml();
    static boost::filesystem::path actual_stand_alone_class_dia_xml();
    static boost::filesystem::path actual_empty_package_dia_xml();
    static boost::filesystem::path actual_empty_package_tack_xml();
    static boost::filesystem::path actual_class_without_name_dia_xml();
    static boost::filesystem::path actual_classes_inout_package_dia_xml();
    static boost::filesystem::path actual_classes_inout_package_tack_xml();
    static boost::filesystem::path actual_class_without_attributes_dia_xml();
    static boost::filesystem::path actual_class_without_attributes_tack_xml();
    static boost::filesystem::path actual_class_without_package_dia_xml();
    static boost::filesystem::path actual_class_without_package_tack_xml();
    static boost::filesystem::path actual_classes_in_a_package_dia_xml();
    static boost::filesystem::path actual_classes_without_package_dia_xml();
    static boost::filesystem::path actual_classes_without_package_tack_xml();
    static boost::filesystem::path actual_package_without_name_dia_xml();
    static boost::filesystem::path actual_two_layers_with_objects_dia_xml();
    static boost::filesystem::path actual_two_layers_with_objects_tack_xml();
    static boost::filesystem::path actual_class_in_a_package_stdout_txt();
    static boost::filesystem::path actual_all_primitives_dia_xml();
    static boost::filesystem::path actual_all_primitives_tack_xml();
    static boost::filesystem::path actual_trivial_inheritance_dia_xml();
    static boost::filesystem::path actual_trivial_inheritance_tack_xml();
    static boost::filesystem::path actual_comments_dia_xml();
    static boost::filesystem::path actual_comments_tack_xml();
    static boost::filesystem::path actual_comments_cpp_xml();
    static boost::filesystem::path actual_enumeration_dia_xml();
    static boost::filesystem::path actual_enumeration_tack_xml();
    static boost::filesystem::path actual_enumeration_cpp_xml();
    static boost::filesystem::path actual_exception_dia_xml();
    static boost::filesystem::path actual_exception_tack_xml();
    static boost::filesystem::path actual_exception_cpp_xml();
    static boost::filesystem::path actual_std_model_dia_xml();
    static boost::filesystem::path actual_std_model_tack_xml();
    static boost::filesystem::path actual_boost_model_dia_xml();
    static boost::filesystem::path actual_boost_model_tack_xml();
};

} } }

#endif
