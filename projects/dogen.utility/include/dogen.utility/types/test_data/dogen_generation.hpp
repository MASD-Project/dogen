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
#ifndef DOGEN_UTILITY_TYPES_TEST_DATA_DOGEN_GENERATION_HPP
#define DOGEN_UTILITY_TYPES_TEST_DATA_DOGEN_GENERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>

namespace dogen::utility::test_data {

class dogen_generation final {
public:
    dogen_generation() = delete;
    dogen_generation(const dogen_generation&) = delete;
    dogen_generation(dogen_generation&&) = delete;
    ~dogen_generation() = delete;
    dogen_generation& operator=(const dogen_generation&) = delete;

public:
    static void initialize();

private:
    static void ensure_initialized();

public:
    static boost::filesystem::path project_directory();
    static boost::filesystem::path output_directory();

public:
    static boost::filesystem::path input_dogen_variability_dia();
    static boost::filesystem::path input_dogen_cli_dia();
    static boost::filesystem::path input_dogen_logical_dia();
    static boost::filesystem::path input_dogen_dia();
    static boost::filesystem::path input_dogen_dia_dia();
    static boost::filesystem::path input_dogen_extraction_dia();
    static boost::filesystem::path input_dogen_generation_cpp_dia();
    static boost::filesystem::path input_dogen_generation_csharp_dia();
    static boost::filesystem::path input_dogen_generation_dia();
    static boost::filesystem::path input_dogen_injection_dia();
    static boost::filesystem::path input_dogen_injection_dia_dia();
    static boost::filesystem::path input_dogen_injection_json_dia();
    static boost::filesystem::path input_dogen_orchestration_dia();
    static boost::filesystem::path input_dogen_templating_dia();
    static boost::filesystem::path input_dogen_tracing_dia();
    static boost::filesystem::path input_dogen_utility_dia();

public:
    static boost::filesystem::path input_dogen_variability_json();
    static boost::filesystem::path input_dogen_cli_json();
    static boost::filesystem::path input_dogen_logical_json();
    static boost::filesystem::path input_dogen_json();
    static boost::filesystem::path input_dogen_dia_json();
    static boost::filesystem::path input_dogen_extraction_json();
    static boost::filesystem::path input_dogen_generation_cpp_json();
    static boost::filesystem::path input_dogen_generation_csharp_json();
    static boost::filesystem::path input_dogen_generation_json();
    static boost::filesystem::path input_dogen_injection_json();
    static boost::filesystem::path input_dogen_injection_dia_json();
    static boost::filesystem::path input_dogen_injection_json_json();
    static boost::filesystem::path input_dogen_orchestration_json();
    static boost::filesystem::path input_dogen_templating_json();
    static boost::filesystem::path input_dogen_tracing_json();
    static boost::filesystem::path input_dogen_utility_json();

private:
    static boost::filesystem::path project_directory_;
    static boost::filesystem::path dia_models_directory_;
    static boost::filesystem::path json_models_directory_;
    static boost::filesystem::path output_directory_;
};

}

#endif
