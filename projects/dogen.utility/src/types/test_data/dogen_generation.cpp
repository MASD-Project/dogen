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
#include <boost/filesystem.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/environment/variable_reader.hpp"
#include "dogen.utility/types/test_data/test_data_exception.hpp"
#include "dogen.utility/types/test_data/dogen_generation.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("utility.dogen_generation"));

const std::string dogen_project_directory_env("DOGEN_PROJECTS_DIRECTORY");

const std::string project_dir_not_found(
    "Could not find project directory: ");
const std::string not_initialized("Test data set is not initialized");
const std::string failed_delete("Failed to delete output directory.");
const std::string failed_create("Failed to create output directory.");

const std::string output_dir("dogen.code_generation_test_output");

const std::string models_dia_dir("dogen.models/dia");
const std::string models_json_dir("dogen.models/json");

const std::string path_dogen_variability_dia("dogen.variability.dia");
const std::string path_dogen_cli_dia("dogen.cli.dia");
const std::string path_dogen_logical_dia("dogen.logical.dia");
const std::string path_dogen_dia("dogen.dia");
const std::string path_dogen_dia_dia("dogen.dia.dia");
const std::string path_dogen_extraction_dia("dogen.extraction.dia");
const std::string path_dogen_generation_cpp_dia("dogen.generation.cpp.dia");
const std::string path_dogen_generation_csharp_dia("dogen.generation.csharp.dia");
const std::string path_dogen_generation_dia("dogen.generation.dia");
const std::string path_dogen_injection_dia("dogen.injection.dia");
const std::string path_dogen_injection_dia_dia("dogen.injection.dia.dia");
const std::string path_dogen_injection_json_dia("dogen.injection.json.dia");
const std::string path_dogen_orchestration_dia("dogen.orchestration.dia");
const std::string path_dogen_templating_dia("dogen.templating.dia");
const std::string path_dogen_tracing_dia("dogen.tracing.dia");
const std::string path_dogen_utility_dia("dogen.utility.dia");

const std::string path_dogen_cli_json("dogen.cli.json");
const std::string path_dogen_variability_json("dogen.variability.json");
const std::string path_dogen_logical_json("dogen.logical.json");
const std::string path_dogen_json("dogen.json");
const std::string path_dogen_dia_json("dogen.dia.json");
const std::string path_dogen_extraction_json("dogen.extraction.json");
const std::string path_dogen_generation_cpp_json("dogen.generation.cpp.json");
const std::string path_dogen_generation_csharp_json("dogen.generation.csharp.json");
const std::string path_dogen_generation_json("dogen.generation.json");
const std::string path_dogen_injection_json("dogen.injection.json");
const std::string path_dogen_injection_dia_json("dogen.injection.dia.json");
const std::string path_dogen_injection_json_json("dogen.injection.json.json");
const std::string path_dogen_orchestration_json("dogen.orchestration.json");
const std::string path_dogen_templating_json("dogen.templating.json");
const std::string path_dogen_tracing_json("dogen.tracing.json");
const std::string path_dogen_utility_json("dogen.utility.json");

}

using boost::filesystem::path;

namespace dogen::utility::test_data {

path dogen_generation::project_directory_;
path dogen_generation::dia_models_directory_;
path dogen_generation::json_models_directory_;
path dogen_generation::output_directory_;

void dogen_generation::initialize() {
    using environment::variable_reader;
    const std::string proj_dir_env(
        variable_reader::strict_read_environment_variable(
            dogen_project_directory_env));

    project_directory_ = path(proj_dir_env);
    if (!boost::filesystem::exists(project_directory_)) {
        BOOST_LOG_SEV(lg, error) << project_dir_not_found
                                 << proj_dir_env;
        BOOST_THROW_EXCEPTION(
            test_data_exception(project_dir_not_found + proj_dir_env));
    }

    dia_models_directory_ = project_directory_ / models_dia_dir;
    json_models_directory_ = project_directory_ / models_json_dir;

    output_directory_ = boost::filesystem::absolute(output_dir);
    if (boost::filesystem::exists(output_directory_)) {
        BOOST_LOG_SEV(lg, debug) << "Output directory already exists: "
                                 << output_directory_.generic_string();

        boost::system::error_code ec;
        boost::filesystem::remove_all(output_directory_, ec);
        if (ec) {
            BOOST_LOG_SEV(lg, error) << failed_delete;
            BOOST_THROW_EXCEPTION(test_data_exception(failed_delete));
        }
        BOOST_LOG_SEV(lg, debug) << "Deleted output data directory.";
    }

    boost::system::error_code ec;
    boost::filesystem::create_directories(output_directory_, ec);
    if (ec) {
        BOOST_LOG_SEV(lg, error) << failed_create;
        BOOST_THROW_EXCEPTION(test_data_exception(failed_create));
    }
    BOOST_LOG_SEV(lg, debug) << "Created output data directory: "
                             << output_directory_.generic_string();
}

void dogen_generation::ensure_initialized() {
    if (project_directory_.empty())
        BOOST_THROW_EXCEPTION(test_data_exception(not_initialized));
}

path dogen_generation::project_directory() {
    ensure_initialized();
    return project_directory_;
}

path dogen_generation::output_directory() {
    ensure_initialized();
    return output_directory_;
}

path dogen_generation::input_dogen_variability_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_variability_dia;
}

path dogen_generation::input_dogen_cli_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_cli_dia;
}

path dogen_generation::input_dogen_logical_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_logical_dia;
}

path dogen_generation::input_dogen_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_dia;
}

path dogen_generation::input_dogen_dia_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_dia_dia;
}

path dogen_generation::input_dogen_extraction_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_extraction_dia;
}

path dogen_generation::input_dogen_generation_cpp_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_generation_cpp_dia;
}

path dogen_generation::input_dogen_generation_csharp_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_generation_csharp_dia;
}

path dogen_generation::input_dogen_generation_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_generation_dia;
}

path dogen_generation::input_dogen_injection_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_injection_dia;
}

path dogen_generation::input_dogen_injection_dia_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_injection_dia_dia;
}

path dogen_generation::input_dogen_injection_json_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_injection_json_dia;
}

path dogen_generation::input_dogen_orchestration_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_orchestration_dia;
}

path dogen_generation::input_dogen_templating_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_templating_dia;
}

path dogen_generation::input_dogen_tracing_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_tracing_dia;
}

path dogen_generation::input_dogen_utility_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_utility_dia;
}

path dogen_generation::input_dogen_variability_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_variability_json;
}

path dogen_generation::input_dogen_cli_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_cli_json;
}

path dogen_generation::input_dogen_logical_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_logical_json;
}

path dogen_generation::input_dogen_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_json;
}

path dogen_generation::input_dogen_dia_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_dia_json;
}

path dogen_generation::input_dogen_extraction_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_extraction_json;
}

path dogen_generation::input_dogen_generation_cpp_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_generation_cpp_json;
}

path dogen_generation::input_dogen_generation_csharp_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_generation_csharp_json;
}

path dogen_generation::input_dogen_generation_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_generation_json;
}

path dogen_generation::input_dogen_injection_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_injection_json;
}

path dogen_generation::input_dogen_injection_dia_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_injection_dia_json;
}

path dogen_generation::input_dogen_injection_json_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_injection_json_json;
}

path dogen_generation::input_dogen_orchestration_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_orchestration_json;
}

path dogen_generation::input_dogen_templating_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_templating_json;
}

path dogen_generation::input_dogen_tracing_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_tracing_json;
}

path dogen_generation::input_dogen_utility_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_utility_json;
}

}
