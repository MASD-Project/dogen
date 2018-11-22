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
#ifndef MASD_DOGEN_UTILITY_TEST_DATA_INJECTION_JSON_HPP
#define MASD_DOGEN_UTILITY_TEST_DATA_INJECTION_JSON_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>

namespace masd::dogen::utility::test_data {

class injection_json {
public:
    injection_json() = delete;
    injection_json(const injection_json&) = delete;
    ~injection_json() = delete;
    injection_json(injection_json&&) = delete;
    injection_json& operator=(const injection_json&) = delete;

public:
    static boost::filesystem::path data_set();

    static boost::filesystem::path input();
    static boost::filesystem::path input_cpp_model_json();
    static boost::filesystem::path input_boost_model_json();
    static boost::filesystem::path input_std_model_json();
    static boost::filesystem::path input_compressed_json();
    static boost::filesystem::path input_empty_json();
    static boost::filesystem::path input_two_empty_layers_json();
    static boost::filesystem::path input_class_without_name_json();
    static boost::filesystem::path input_package_without_name_json();
    static boost::filesystem::path input_two_layers_with_objects_json();
    static boost::filesystem::path input_disable_cmakelists_json();
    static boost::filesystem::path input_disable_facet_folders_json();
    static boost::filesystem::path input_enable_facet_types_json();
    static boost::filesystem::path input_enable_facet_hash_json();
    static boost::filesystem::path input_enable_facet_io_json();
    static boost::filesystem::path input_enable_facet_serialization_json();
    static boost::filesystem::path input_all_path_and_directory_settings_json();
    static boost::filesystem::path input_split_project_json();
    static boost::filesystem::path input_cpp_98_json();
    static boost::filesystem::path input_lam_model_json();
    static boost::filesystem::path input_csharp_model_json();

    static boost::filesystem::path expected();
    static boost::filesystem::path actual();
};

}

#endif
