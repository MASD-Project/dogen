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
#include <cstdlib>
#include <boost/filesystem.hpp>
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/test_data/test_data_exception.hpp"
#include "masd.dogen.utility/types/test_data/dogen_generation.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("utility.dogen_generation"));

const std::string dogen_project_directory_env("MASD_DOGEN_PROJECT_DIRECTORY");

const std::string environment_variable_not_defined(
    "Expected environment variable not defined: ");
const std::string project_dir_not_found(
    "Could not find project directory: ");
const std::string not_initialized("Test data set is not initialized");
const std::string failed_delete("Failed to delete tracer data directory.");
const std::string failed_create("Failed to create tracer data directory.");

const std::string output_dir("masd.dogen.code_generation_test_output");

const std::string models_dia_dir("masd.dogen.models/dia");
const std::string models_json_dir("masd.dogen.models/json");

const std::string path_masd_dogen_annotations_dia("masd.dogen.annotations.dia");
const std::string path_masd_dogen_cli_dia("masd.dogen.cli.dia");
const std::string path_masd_dogen_coding_dia("masd.dogen.coding.dia");
const std::string path_masd_dogen_dia("masd.dogen.dia");
const std::string path_masd_dogen_dia_dia("masd.dogen.dia.dia");
const std::string path_masd_dogen_extraction_dia("masd.dogen.extraction.dia");
const std::string path_masd_dogen_generation_cpp_dia("masd.dogen.generation.cpp.dia");
const std::string path_masd_dogen_generation_csharp_dia("masd.dogen.generation.csharp.dia");
const std::string path_masd_dogen_generation_dia("masd.dogen.generation.dia");
const std::string path_masd_dogen_injection_dia("masd.dogen.injection.dia");
const std::string path_masd_dogen_injection_dia_dia("masd.dogen.injection.dia.dia");
const std::string path_masd_dogen_injection_json_dia("masd.dogen.injection.json.dia");
const std::string path_masd_dogen_orchestration_dia("masd.dogen.orchestration.dia");
const std::string path_masd_dogen_templating_dia("masd.dogen.templating.dia");
const std::string path_masd_dogen_tracing_dia("masd.dogen.tracing.dia");
const std::string path_masd_dogen_utility_dia("masd.dogen.utility.dia");

const std::string path_masd_dogen_cli_json("masd.dogen.cli.json");
const std::string path_masd_dogen_annotations_json("masd.dogen.annotations.json");
const std::string path_masd_dogen_coding_json("masd.dogen.coding.json");
const std::string path_masd_dogen_json("masd.dogen.json");
const std::string path_masd_dogen_dia_json("masd.dogen.dia.json");
const std::string path_masd_dogen_extraction_json("masd.dogen.extraction.json");
const std::string path_masd_dogen_generation_cpp_json("masd.dogen.generation.cpp.json");
const std::string path_masd_dogen_generation_csharp_json("masd.dogen.generation.csharp.json");
const std::string path_masd_dogen_generation_json("masd.dogen.generation.json");
const std::string path_masd_dogen_injection_json("masd.dogen.injection.json");
const std::string path_masd_dogen_injection_dia_json("masd.dogen.injection.dia.json");
const std::string path_masd_dogen_injection_json_json("masd.dogen.injection.json.json");
const std::string path_masd_dogen_orchestration_json("masd.dogen.orchestration.json");
const std::string path_masd_dogen_templating_json("masd.dogen.templating.json");
const std::string path_masd_dogen_tracing_json("masd.dogen.tracing.json");
const std::string path_masd_dogen_utility_json("masd.dogen.utility.json");

std::string get_env_var(const std::string& var_name) {
    const char* val = std::getenv(var_name.c_str());
    return val == NULL ? std::string() : std::string(val);
}

}

using boost::filesystem::path;

namespace masd::dogen::utility::test_data {

boost::filesystem::path dogen_generation::project_directory_;
boost::filesystem::path dogen_generation::output_directory_;

void dogen_generation::initialize() {
    const std::string proj_dir_env(get_env_var(dogen_project_directory_env));
    if (proj_dir_env.empty()) {
        BOOST_LOG_SEV(lg, error) << environment_variable_not_defined
                                 << dogen_project_directory_env;
        BOOST_THROW_EXCEPTION(
            test_data_exception(environment_variable_not_defined +
                dogen_project_directory_env));
    }

    project_directory_ = path(proj_dir_env);
    if (!boost::filesystem::exists(project_directory_)) {
        BOOST_LOG_SEV(lg, error) << project_dir_not_found
                                 << proj_dir_env;
        BOOST_THROW_EXCEPTION(
            test_data_exception(project_dir_not_found + proj_dir_env));
    }

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

path dogen_generation::input_masd_dogen_annotations_dia() {
    ensure_initialized();
    return project_directory_ / models_dia_dir /
        path_masd_dogen_annotations_dia;
}

path dogen_generation::input_masd_dogen_cli_dia() {
    ensure_initialized();
    return project_directory_ / models_dia_dir / path_masd_dogen_cli_dia;
}

path dogen_generation::input_masd_dogen_coding_dia() {
    ensure_initialized();
    return project_directory_ / models_dia_dir / path_masd_dogen_coding_dia;
}

path dogen_generation::input_masd_dogen_dia() {
    ensure_initialized();
    return project_directory_ / models_dia_dir / path_masd_dogen_dia;
}

path dogen_generation::input_masd_dogen_dia_dia() {
    ensure_initialized();
    return project_directory_ / models_dia_dir / path_masd_dogen_dia_dia;
}

path dogen_generation::input_masd_dogen_extraction_dia() {
    ensure_initialized();
    return project_directory_ / models_dia_dir / path_masd_dogen_extraction_dia;
}

path dogen_generation::input_masd_dogen_generation_cpp_dia() {
    ensure_initialized();
    return project_directory_ / models_dia_dir /
        path_masd_dogen_generation_cpp_dia;
}

path dogen_generation::input_masd_dogen_generation_csharp_dia() {
    ensure_initialized();
    return project_directory_ / models_dia_dir /
        path_masd_dogen_generation_csharp_dia;
}

path dogen_generation::input_masd_dogen_generation_dia() {
    ensure_initialized();
    return project_directory_ / models_dia_dir / path_masd_dogen_generation_dia;
}

path dogen_generation::input_masd_dogen_injection_dia() {
    ensure_initialized();
    return project_directory_ / models_dia_dir / path_masd_dogen_injection_dia;
}

path dogen_generation::input_masd_dogen_injection_dia_dia() {
    ensure_initialized();
    return project_directory_ / models_dia_dir /
        path_masd_dogen_injection_dia_dia;
}

path dogen_generation::input_masd_dogen_injection_json_dia() {
    ensure_initialized();
    return project_directory_ / models_dia_dir /
        path_masd_dogen_injection_json_dia;
}

path dogen_generation::input_masd_dogen_orchestration_dia() {
    ensure_initialized();
    return project_directory_ / models_dia_dir / path_masd_dogen_orchestration_dia;
}

path dogen_generation::input_masd_dogen_templating_dia() {
    ensure_initialized();
    return project_directory_ / models_dia_dir / path_masd_dogen_templating_dia;
}

path dogen_generation::input_masd_dogen_tracing_dia() {
    ensure_initialized();
    return project_directory_ / models_dia_dir / path_masd_dogen_tracing_dia;
}

path dogen_generation::input_masd_dogen_utility_dia() {
    ensure_initialized();
    return project_directory_ / models_dia_dir / path_masd_dogen_utility_dia;
}

path dogen_generation::input_masd_dogen_annotations_json() {
    ensure_initialized();
    return project_directory_ / models_dia_dir /
        path_masd_dogen_annotations_json;
}

path dogen_generation::input_masd_dogen_cli_json() {
    ensure_initialized();
    return project_directory_ / models_dia_dir / path_masd_dogen_cli_json;
}

path dogen_generation::input_masd_dogen_coding_json() {
    ensure_initialized();
    return project_directory_ / models_dia_dir / path_masd_dogen_coding_json;
}

path dogen_generation::input_masd_dogen_json() {
    ensure_initialized();
    return project_directory_ / models_dia_dir / path_masd_dogen_json;
}

path dogen_generation::input_masd_dogen_dia_json() {
    ensure_initialized();
    return project_directory_ / models_dia_dir / path_masd_dogen_dia_json;
}

path dogen_generation::input_masd_dogen_extraction_json() {
    ensure_initialized();
    return project_directory_ / models_dia_dir /
        path_masd_dogen_extraction_json;
}

path dogen_generation::input_masd_dogen_generation_cpp_json() {
    ensure_initialized();
    return project_directory_ / models_dia_dir /
        path_masd_dogen_generation_cpp_json;
}

path dogen_generation::input_masd_dogen_generation_csharp_json() {
    ensure_initialized();
    return project_directory_ / models_dia_dir /
        path_masd_dogen_generation_csharp_json;
}

path dogen_generation::input_masd_dogen_generation_json() {
    ensure_initialized();
    return project_directory_ / models_dia_dir /
        path_masd_dogen_generation_json;
}

path dogen_generation::input_masd_dogen_injection_json() {
    ensure_initialized();
    return project_directory_ / models_dia_dir /
        path_masd_dogen_injection_json;
}

path dogen_generation::input_masd_dogen_injection_dia_json() {
    ensure_initialized();
    return project_directory_ / models_dia_dir /
        path_masd_dogen_injection_dia_json;
}

path dogen_generation::input_masd_dogen_injection_json_json() {
    ensure_initialized();
    return project_directory_ / models_dia_dir /
        path_masd_dogen_injection_json_json;
}

path dogen_generation::input_masd_dogen_orchestration_json() {
    ensure_initialized();
    return project_directory_ / models_dia_dir /
        path_masd_dogen_orchestration_json;
}

path dogen_generation::input_masd_dogen_templating_json() {
    ensure_initialized();
    return project_directory_ / models_dia_dir /
        path_masd_dogen_templating_json;
}

path dogen_generation::input_masd_dogen_tracing_json() {
    ensure_initialized();
    return project_directory_ / models_dia_dir / path_masd_dogen_tracing_json;
}

path dogen_generation::input_masd_dogen_utility_json() {
    ensure_initialized();
    return project_directory_ / models_dia_dir / path_masd_dogen_utility_json;
}

}
