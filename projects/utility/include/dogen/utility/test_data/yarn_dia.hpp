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
#ifndef DOGEN_UTILITY_TEST_DATA_YARN_DIA_HPP
#define DOGEN_UTILITY_TEST_DATA_YARN_DIA_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>

namespace dogen {
namespace utility {
namespace test_data {

class yarn_dia {
public:
    yarn_dia() = delete;
    yarn_dia(const yarn_dia&) = delete;
    ~yarn_dia() = delete;
    yarn_dia(yarn_dia&&) = delete;
    yarn_dia& operator=(const yarn_dia&) = delete;

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
    static boost::filesystem::path input_disable_xml_serialization_dia();
    static boost::filesystem::path input_enable_facet_types_dia();
    static boost::filesystem::path input_enable_facet_hash_dia();
    static boost::filesystem::path input_enable_facet_io_dia();
    static boost::filesystem::path input_enable_facet_serialization_dia();
    static boost::filesystem::path input_rename_facet_folder_dia();
    static boost::filesystem::path input_all_builtins_dia();
    static boost::filesystem::path input_csharp_model_dia();
    static boost::filesystem::path input_trivial_inheritance_dia();
    static boost::filesystem::path input_trivial_association_dia();
    static boost::filesystem::path input_comments_dia();
    static boost::filesystem::path input_enumeration_dia();
    static boost::filesystem::path input_exception_dia();
    static boost::filesystem::path input_stereotypes_dia();

    static boost::filesystem::path expected();
    static boost::filesystem::path expected_class_in_a_package_dia_xml();
    static boost::filesystem::path expected_class_in_a_package_yarn_xml();
    static boost::filesystem::path expected_class_in_a_package_cpp_xml();
    static boost::filesystem::path expected_compressed_dia_xml();
    static boost::filesystem::path expected_empty_dia_xml();
    static boost::filesystem::path expected_empty_yarn_xml();
    static boost::filesystem::path expected_empty_cpp_xml();
    static boost::filesystem::path expected_two_empty_layers_dia_xml();
    static boost::filesystem::path expected_stand_alone_class_dia_xml();
    static boost::filesystem::path expected_empty_package_dia_xml();
    static boost::filesystem::path expected_empty_package_yarn_xml();
    static boost::filesystem::path expected_class_without_name_dia_xml();
    static boost::filesystem::path expected_classes_inout_package_dia_xml();
    static boost::filesystem::path expected_classes_inout_package_yarn_xml();
    static boost::filesystem::path expected_class_without_attributes_dia_xml();
    static boost::filesystem::path expected_class_without_attributes_yarn_xml();
    static boost::filesystem::path expected_class_without_package_dia_xml();
    static boost::filesystem::path expected_class_without_package_yarn_xml();
    static boost::filesystem::path expected_classes_in_a_package_dia_xml();
    static boost::filesystem::path expected_classes_without_package_dia_xml();
    static boost::filesystem::path expected_classes_without_package_yarn_xml();
    static boost::filesystem::path expected_package_without_name_dia_xml();
    static boost::filesystem::path expected_two_layers_with_objects_dia_xml();
    static boost::filesystem::path expected_two_layers_with_objects_yarn_xml();
    static boost::filesystem::path expected_class_in_a_package_stdout_txt();
    static boost::filesystem::path expected_all_builtins_dia_xml();
    static boost::filesystem::path expected_all_builtins_yarn_xml();
    static boost::filesystem::path expected_trivial_inheritance_dia_xml();
    static boost::filesystem::path expected_trivial_inheritance_yarn_xml();
    static boost::filesystem::path expected_comments_dia_xml();
    static boost::filesystem::path expected_comments_yarn_xml();
    static boost::filesystem::path expected_comments_cpp_xml();
    static boost::filesystem::path expected_enumeration_dia_xml();
    static boost::filesystem::path expected_enumeration_yarn_xml();
    static boost::filesystem::path expected_enumeration_cpp_xml();
    static boost::filesystem::path expected_exception_dia_xml();
    static boost::filesystem::path expected_exception_yarn_xml();
    static boost::filesystem::path expected_exception_cpp_xml();
    static boost::filesystem::path expected_std_model_dia_xml();
    static boost::filesystem::path expected_std_model_yarn_xml();
    static boost::filesystem::path expected_boost_model_dia_xml();
    static boost::filesystem::path expected_boost_model_yarn_xml();

    static boost::filesystem::path actual();
    static boost::filesystem::path actual_class_in_a_package_dia_xml();
    static boost::filesystem::path actual_class_in_a_package_yarn_xml();
    static boost::filesystem::path actual_class_in_a_package_cpp_xml();
    static boost::filesystem::path actual_compressed_dia_xml();
    static boost::filesystem::path actual_empty_dia_xml();
    static boost::filesystem::path actual_empty_yarn_xml();
    static boost::filesystem::path actual_empty_cpp_xml();
    static boost::filesystem::path actual_two_empty_layers_dia_xml();
    static boost::filesystem::path actual_stand_alone_class_dia_xml();
    static boost::filesystem::path actual_empty_package_dia_xml();
    static boost::filesystem::path actual_empty_package_yarn_xml();
    static boost::filesystem::path actual_class_without_name_dia_xml();
    static boost::filesystem::path actual_classes_inout_package_dia_xml();
    static boost::filesystem::path actual_classes_inout_package_yarn_xml();
    static boost::filesystem::path actual_class_without_attributes_dia_xml();
    static boost::filesystem::path actual_class_without_attributes_yarn_xml();
    static boost::filesystem::path actual_class_without_package_dia_xml();
    static boost::filesystem::path actual_class_without_package_yarn_xml();
    static boost::filesystem::path actual_classes_in_a_package_dia_xml();
    static boost::filesystem::path actual_classes_without_package_dia_xml();
    static boost::filesystem::path actual_classes_without_package_yarn_xml();
    static boost::filesystem::path actual_package_without_name_dia_xml();
    static boost::filesystem::path actual_two_layers_with_objects_dia_xml();
    static boost::filesystem::path actual_two_layers_with_objects_yarn_xml();
    static boost::filesystem::path actual_class_in_a_package_stdout_txt();
    static boost::filesystem::path actual_all_builtins_dia_xml();
    static boost::filesystem::path actual_all_builtins_yarn_xml();
    static boost::filesystem::path actual_trivial_inheritance_dia_xml();
    static boost::filesystem::path actual_trivial_inheritance_yarn_xml();
    static boost::filesystem::path actual_comments_dia_xml();
    static boost::filesystem::path actual_comments_yarn_xml();
    static boost::filesystem::path actual_comments_cpp_xml();
    static boost::filesystem::path actual_enumeration_dia_xml();
    static boost::filesystem::path actual_enumeration_yarn_xml();
    static boost::filesystem::path actual_enumeration_cpp_xml();
    static boost::filesystem::path actual_exception_dia_xml();
    static boost::filesystem::path actual_exception_yarn_xml();
    static boost::filesystem::path actual_exception_cpp_xml();
    static boost::filesystem::path actual_std_model_dia_xml();
    static boost::filesystem::path actual_std_model_yarn_xml();
    static boost::filesystem::path actual_boost_model_dia_xml();
    static boost::filesystem::path actual_boost_model_yarn_xml();
};

} } }

#endif
