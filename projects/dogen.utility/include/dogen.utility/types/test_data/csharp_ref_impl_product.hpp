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
#ifndef DOGEN_UTILITY_TYPES_TEST_DATA_CSHARP_REF_IMPL_GENERATION_HPP
#define DOGEN_UTILITY_TYPES_TEST_DATA_CSHARP_REF_IMPL_GENERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>

namespace dogen::utility::test_data {

class csharp_ref_impl_product final {
public:
    csharp_ref_impl_product() = delete;
    csharp_ref_impl_product(const csharp_ref_impl_product&) = delete;
    csharp_ref_impl_product(csharp_ref_impl_product&&) = delete;
    ~csharp_ref_impl_product() = delete;
    csharp_ref_impl_product& operator=(const csharp_ref_impl_product&) = delete;

public:
    static void initialize();

private:
    static void ensure_initialized();

public:
    static boost::filesystem::path project_directory();
    static boost::filesystem::path output_directory();

public:
    static boost::filesystem::path input_csharprefimpl_csharpmodel_org();
    static boost::filesystem::path input_csharprefimpl_directory_settings_org();
    static boost::filesystem::path input_csharprefimpl_lammodel_org();

private:
    static boost::filesystem::path project_directory_;
    static boost::filesystem::path org_models_directory_;
    static boost::filesystem::path output_directory_;
};

}

#endif
