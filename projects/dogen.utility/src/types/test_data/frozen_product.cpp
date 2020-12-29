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
#include "dogen.utility/types/test_data/frozen_product.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("utility.frozen_product"));

const std::string frozen_project_directory_env("FROZEN_PROJECTS_DIRECTORY");

const std::string project_dir_not_found(
    "Could not find project directory: ");
const std::string not_initialized("Test data set is not initialized");
const std::string failed_delete("Failed to delete output directory.");
const std::string failed_create("Failed to create output directory.");

const std::string output_dir("dogen.code_generation_test_output");

const std::string models_dia_dir("dogen.models/dia");
const std::string models_org_dir("dogen.models/org");
const std::string models_json_dir("dogen.models/json");

const std::string path_dogen_dia("dogen.dia");
const std::string path_dogen_physical_dia("dogen.physical.dia");
const std::string path_dogen_cli_dia("dogen.cli.dia");
const std::string path_dogen_dia_dia("dogen.dia.dia");
const std::string path_dogen_org_dia("dogen.org.dia");
const std::string path_dogen_tracing_dia("dogen.tracing.dia");
const std::string path_dogen_codec_dia("dogen.codec.dia");
const std::string path_dogen_codec_dia_dia("dogen.codec.dia.dia");
const std::string path_dogen_text_dia("dogen.text.dia");
const std::string path_dogen_logical_dia("dogen.logical.dia");
const std::string path_dogen_templating_dia("dogen.templating.dia");
const std::string path_dogen_orchestration_dia("dogen.orchestration.dia");
const std::string path_dogen_utility_dia("dogen.utility.dia");
const std::string path_dogen_variability_dia("dogen.variability.dia");
const std::string path_dogen_relational_dia("dogen.relational.dia");
const std::string path_dogen_identification_dia("dogen.identification.dia");

const std::string path_dogen_org("dogen.org");
const std::string path_dogen_physical_org("dogen.physical.org");
const std::string path_dogen_cli_org("dogen.cli.org");
const std::string path_dogen_dia_org("dogen.dia.org");
const std::string path_dogen_org_org("dogen.org.org");
const std::string path_dogen_tracing_org("dogen.tracing.org");
const std::string path_dogen_codec_org("dogen.codec.org");
const std::string path_dogen_codec_dia_org("dogen.codec.dia.org");
const std::string path_dogen_text_org("dogen.text.org");
const std::string path_dogen_logical_org("dogen.logical.org");
const std::string path_dogen_templating_org("dogen.templating.org");
const std::string path_dogen_orchestration_org("dogen.orchestration.org");
const std::string path_dogen_utility_org("dogen.utility.org");
const std::string path_dogen_variability_org("dogen.variability.org");
const std::string path_dogen_relational_org("dogen.relational.org");
const std::string path_dogen_identification_org("dogen.identification.org");

const std::string path_dogen_json("dogen.json");
const std::string path_dogen_physical_json("dogen.physical.json");
const std::string path_dogen_cli_json("dogen.cli.json");
const std::string path_dogen_dia_json("dogen.dia.json");
const std::string path_dogen_tracing_json("dogen.tracing.json");
const std::string path_dogen_codec_json("dogen.codec.json");
const std::string path_dogen_codec_dia_json("dogen.codec.dia.json");
const std::string path_dogen_codec_json_json("dogen.codec.json.json");
const std::string path_dogen_text_json("dogen.text.json");
const std::string path_dogen_logical_json("dogen.logical.json");
const std::string path_dogen_templating_json("dogen.templating.json");
const std::string path_dogen_utility_json("dogen.utility.json");
const std::string path_dogen_variability_json("dogen.variability.json");
const std::string path_dogen_orchestration_json("dogen.orchestration.json");
const std::string path_dogen_relational_json("dogen.relational.json");
const std::string path_dogen_identification_json("dogen.identification.json");

}

using boost::filesystem::path;

namespace dogen::utility::test_data {

path frozen_product::project_directory_;
path frozen_product::dia_models_directory_;
path frozen_product::org_models_directory_;
path frozen_product::json_models_directory_;
path frozen_product::output_directory_;

void frozen_product::initialize() {
    using environment::variable_reader;
    const std::string proj_dir_env(
        variable_reader::strict_read_environment_variable(
            frozen_project_directory_env));

    project_directory_ = path(proj_dir_env);
    if (!boost::filesystem::exists(project_directory_)) {
        BOOST_LOG_SEV(lg, error) << project_dir_not_found
                                 << proj_dir_env;
        BOOST_THROW_EXCEPTION(
            test_data_exception(project_dir_not_found + proj_dir_env));
    }

    dia_models_directory_ = project_directory_ / models_dia_dir;
    org_models_directory_ = project_directory_ / models_org_dir;
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

void frozen_product::ensure_initialized() {
    if (project_directory_.empty())
        BOOST_THROW_EXCEPTION(test_data_exception(not_initialized));
}

path frozen_product::project_directory() {
    ensure_initialized();
    return project_directory_;
}

/*
 * Dia Paths.
 */
path frozen_product::output_directory() {
    ensure_initialized();
    return output_directory_;
}

path frozen_product::input_frozen_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_dia;
}

path frozen_product::input_frozen_physical_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_physical_dia;
}

path frozen_product::input_frozen_cli_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_cli_dia;
}

path frozen_product::input_frozen_dia_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_dia_dia;
}

path frozen_product::input_frozen_org_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_org_dia;
}

path frozen_product::input_frozen_tracing_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_tracing_dia;
}

path frozen_product::input_frozen_codec_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_codec_dia;
}

path frozen_product::input_frozen_codec_dia_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_codec_dia_dia;
}

path frozen_product::input_frozen_text_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_text_dia;
}

path frozen_product::input_frozen_logical_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_logical_dia;
}

path frozen_product::input_frozen_templating_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_templating_dia;
}

path frozen_product::input_frozen_orchestration_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_orchestration_dia;
}

path frozen_product::input_frozen_utility_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_utility_dia;
}

path frozen_product::input_frozen_variability_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_variability_dia;
}

path frozen_product::input_frozen_relational_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_relational_dia;
}

path frozen_product::input_frozen_identification_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_dogen_identification_dia;
}

/*
 * Org paths
 */
path frozen_product::input_frozen_org() {
    ensure_initialized();
    return org_models_directory_ / path_dogen_org;
}

path frozen_product::input_frozen_physical_org() {
    ensure_initialized();
    return org_models_directory_ / path_dogen_physical_org;
}

path frozen_product::input_frozen_cli_org() {
    ensure_initialized();
    return org_models_directory_ / path_dogen_cli_org;
}

path frozen_product::input_frozen_dia_org() {
    ensure_initialized();
    return org_models_directory_ / path_dogen_dia_org;
}

path frozen_product::input_frozen_org_org() {
    ensure_initialized();
    return org_models_directory_ / path_dogen_org_org;
}

path frozen_product::input_frozen_tracing_org() {
    ensure_initialized();
    return org_models_directory_ / path_dogen_tracing_org;
}

path frozen_product::input_frozen_codec_org() {
    ensure_initialized();
    return org_models_directory_ / path_dogen_codec_org;
}

path frozen_product::input_frozen_codec_dia_org() {
    ensure_initialized();
    return org_models_directory_ / path_dogen_codec_dia_org;
}

path frozen_product::input_frozen_text_org() {
    ensure_initialized();
    return org_models_directory_ / path_dogen_text_org;
}

path frozen_product::input_frozen_logical_org() {
    ensure_initialized();
    return org_models_directory_ / path_dogen_logical_org;
}

path frozen_product::input_frozen_templating_org() {
    ensure_initialized();
    return org_models_directory_ / path_dogen_templating_org;
}

path frozen_product::input_frozen_orchestration_org() {
    ensure_initialized();
    return org_models_directory_ / path_dogen_orchestration_org;
}

path frozen_product::input_frozen_utility_org() {
    ensure_initialized();
    return org_models_directory_ / path_dogen_utility_org;
}

path frozen_product::input_frozen_variability_org() {
    ensure_initialized();
    return org_models_directory_ / path_dogen_variability_org;
}

path frozen_product::input_frozen_relational_org() {
    ensure_initialized();
    return org_models_directory_ / path_dogen_relational_org;
}

path frozen_product::input_frozen_identification_org() {
    ensure_initialized();
    return org_models_directory_ / path_dogen_identification_org;
}

/*
 * JSON Paths.
 */
path frozen_product::input_frozen_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_json;
}

path frozen_product::input_frozen_physical_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_physical_json;
}

path frozen_product::input_frozen_cli_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_cli_json;
}

path frozen_product::input_frozen_dia_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_dia_json;
}

path frozen_product::input_frozen_tracing_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_tracing_json;
}

path frozen_product::input_frozen_codec_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_codec_json;
}

path frozen_product::input_frozen_codec_dia_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_codec_dia_json;
}

path frozen_product::input_frozen_codec_json_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_codec_json_json;
}

path frozen_product::input_frozen_text_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_text_json;
}

path frozen_product::input_frozen_logical_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_logical_json;
}

path frozen_product::input_frozen_templating_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_templating_json;
}

path frozen_product::input_frozen_orchestration_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_orchestration_json;
}

path frozen_product::input_frozen_utility_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_utility_json;
}

path frozen_product::input_frozen_variability_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_variability_json;
}

path frozen_product::input_frozen_relational_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_relational_json;
}

path frozen_product::input_frozen_identification_json() {
    ensure_initialized();
    return json_models_directory_ / path_dogen_identification_json;
}
}
