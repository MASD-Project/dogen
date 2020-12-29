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
#ifndef DOGEN_UTILITY_TYPES_TEST_DATA_FROZEN_TEXT_HPP
#define DOGEN_UTILITY_TYPES_TEST_DATA_FROZEN_TEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>

namespace dogen::utility::test_data {

class frozen_product final {
public:
    frozen_product() = delete;
    frozen_product(const frozen_product&) = delete;
    frozen_product(frozen_product&&) = delete;
    ~frozen_product() = delete;
    frozen_product& operator=(const frozen_product&) = delete;

public:
    static void initialize();

private:
    static void ensure_initialized();

public:
    static boost::filesystem::path project_directory();
    static boost::filesystem::path output_directory();

public:
    static boost::filesystem::path input_frozen_dia();
    static boost::filesystem::path input_frozen_physical_dia();
    static boost::filesystem::path input_frozen_cli_dia();
    static boost::filesystem::path input_frozen_dia_dia();
    static boost::filesystem::path input_frozen_org_dia();
    static boost::filesystem::path input_frozen_tracing_dia();
    static boost::filesystem::path input_frozen_codec_dia();
    static boost::filesystem::path input_frozen_codec_dia_dia();
    static boost::filesystem::path input_frozen_text_dia();
    static boost::filesystem::path input_frozen_logical_dia();
    static boost::filesystem::path input_frozen_templating_dia();
    static boost::filesystem::path input_frozen_orchestration_dia();
    static boost::filesystem::path input_frozen_utility_dia();
    static boost::filesystem::path input_frozen_variability_dia();
    static boost::filesystem::path input_frozen_relational_dia();
    static boost::filesystem::path input_frozen_identification_dia();

public:
    static boost::filesystem::path input_frozen_org();
    static boost::filesystem::path input_frozen_physical_org();
    static boost::filesystem::path input_frozen_cli_org();
    static boost::filesystem::path input_frozen_dia_org();
    static boost::filesystem::path input_frozen_org_org();
    static boost::filesystem::path input_frozen_tracing_org();
    static boost::filesystem::path input_frozen_codec_org();
    static boost::filesystem::path input_frozen_codec_dia_org();
    static boost::filesystem::path input_frozen_text_org();
    static boost::filesystem::path input_frozen_logical_org();
    static boost::filesystem::path input_frozen_templating_org();
    static boost::filesystem::path input_frozen_orchestration_org();
    static boost::filesystem::path input_frozen_utility_org();
    static boost::filesystem::path input_frozen_variability_org();
    static boost::filesystem::path input_frozen_relational_org();
    static boost::filesystem::path input_frozen_identification_org();

public:
    static boost::filesystem::path input_frozen_json();
    static boost::filesystem::path input_frozen_physical_json();
    static boost::filesystem::path input_frozen_cli_json();
    static boost::filesystem::path input_frozen_dia_json();
    static boost::filesystem::path input_frozen_tracing_json();
    static boost::filesystem::path input_frozen_codec_json();
    static boost::filesystem::path input_frozen_codec_dia_json();
    static boost::filesystem::path input_frozen_codec_json_json();
    static boost::filesystem::path input_frozen_text_json();
    static boost::filesystem::path input_frozen_logical_json();
    static boost::filesystem::path input_frozen_orchestration_json();
    static boost::filesystem::path input_frozen_templating_json();
    static boost::filesystem::path input_frozen_utility_json();
    static boost::filesystem::path input_frozen_variability_json();
    static boost::filesystem::path input_frozen_relational_json();
    static boost::filesystem::path input_frozen_identification_json();

private:
    static boost::filesystem::path project_directory_;
    static boost::filesystem::path dia_models_directory_;
    static boost::filesystem::path org_models_directory_;
    static boost::filesystem::path json_models_directory_;
    static boost::filesystem::path output_directory_;
};

}

#endif
