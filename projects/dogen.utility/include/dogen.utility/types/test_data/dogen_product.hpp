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
#ifndef DOGEN_UTILITY_TYPES_TEST_DATA_DOGEN_TEXT_HPP
#define DOGEN_UTILITY_TYPES_TEST_DATA_DOGEN_TEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>

namespace dogen::utility::test_data {

class dogen_product final {
public:
    dogen_product() = delete;
    dogen_product(const dogen_product&) = delete;
    dogen_product(dogen_product&&) = delete;
    ~dogen_product() = delete;
    dogen_product& operator=(const dogen_product&) = delete;

public:
    static void initialize();

private:
    static void ensure_initialized();

public:
    static boost::filesystem::path project_directory();
    static boost::filesystem::path output_directory();
    static const std::vector<boost::filesystem::path>& reference_directories();

public:
    static boost::filesystem::path input_dogen_org();
    static boost::filesystem::path input_dogen_physical_org();
    static boost::filesystem::path input_dogen_cli_org();
    static boost::filesystem::path input_dogen_dia_org();
    static boost::filesystem::path input_dogen_org_org();
    static boost::filesystem::path input_dogen_tracing_org();
    static boost::filesystem::path input_dogen_codec_org();
    static boost::filesystem::path input_dogen_text_org();
    static boost::filesystem::path input_dogen_logical_org();
    static boost::filesystem::path input_dogen_templating_org();
    static boost::filesystem::path input_dogen_orchestration_org();
    static boost::filesystem::path input_dogen_utility_org();
    static boost::filesystem::path input_dogen_variability_org();
    static boost::filesystem::path input_dogen_relational_org();
    static boost::filesystem::path input_dogen_identification_org();

private:
    static boost::filesystem::path project_directory_;
    static boost::filesystem::path org_models_directory_;
    static boost::filesystem::path output_directory_;
    static std::vector<boost::filesystem::path> reference_directories_;
};

}

#endif
