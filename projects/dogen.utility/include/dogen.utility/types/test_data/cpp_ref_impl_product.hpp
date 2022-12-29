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
#ifndef DOGEN_UTILITY_TYPES_TEST_DATA_CPP_REF_IMPL_GENERATION_HPP
#define DOGEN_UTILITY_TYPES_TEST_DATA_CPP_REF_IMPL_GENERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>

namespace dogen::utility::test_data {

class cpp_ref_impl_product final {
public:
    cpp_ref_impl_product() = delete;
    cpp_ref_impl_product(const cpp_ref_impl_product&) = delete;
    cpp_ref_impl_product(cpp_ref_impl_product&&) = delete;
    ~cpp_ref_impl_product() = delete;
    cpp_ref_impl_product& operator=(const cpp_ref_impl_product&) = delete;

public:
    static void initialize();

private:
    static void ensure_initialized();

public:
    static boost::filesystem::path project_directory();
    static boost::filesystem::path output_directory();

public:
    static boost::filesystem::path input_cpp_ref_impl_boost_model_org();
    static boost::filesystem::path input_cpp_ref_impl_colours_org();
    static boost::filesystem::path input_cpp_ref_impl_cpp_98_org();
    static boost::filesystem::path input_cpp_ref_impl_cpp_model_org();
    static boost::filesystem::path input_cpp_ref_impl_directory_settings_org();
    static boost::filesystem::path input_cpp_ref_impl_disable_cmakelists_org();
    static boost::filesystem::path input_cpp_ref_impl_disable_facet_folders_org();
    static boost::filesystem::path input_cpp_ref_impl_enable_facet_hash_org();
    static boost::filesystem::path input_cpp_ref_impl_enable_facet_io_org();
    static boost::filesystem::path input_cpp_ref_impl_enable_facet_serialization_org();
    static boost::filesystem::path input_cpp_ref_impl_enable_facet_types_org();
    static boost::filesystem::path input_cpp_ref_impl_flat_directory_mode_org();
    static boost::filesystem::path input_cpp_ref_impl_lam_model_org();
    static boost::filesystem::path input_cpp_ref_impl_northwind_org();
    static boost::filesystem::path input_cpp_ref_impl_split_project_org();
    static boost::filesystem::path input_cpp_ref_impl_std_model_org();
    static boost::filesystem::path input_cpp_ref_impl_two_layers_with_objects_org();
    static boost::filesystem::path input_cpp_ref_impl_delete_extra_org();
    static boost::filesystem::path input_cpp_ref_impl_ignore_extra_org();
    static boost::filesystem::path input_cpp_ref_impl_force_write_org();
    static boost::filesystem::path input_cpp_ref_impl_out_of_sync_org();
    static boost::filesystem::path input_cpp_ref_impl_do_not_delete_empty_dirs_org();

private:
    static boost::filesystem::path project_directory_;
    static boost::filesystem::path org_models_directory_;
    static boost::filesystem::path output_directory_;
};

}

#endif
