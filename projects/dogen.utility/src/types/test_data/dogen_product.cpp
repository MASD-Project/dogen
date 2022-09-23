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
#include "dogen.utility/types/test_data/dogen_product.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("utility.dogen_product"));

const std::string dogen_project_directory_env("DOGEN_PROJECTS_DIRECTORY");

const std::string project_dir_not_found(
    "Could not find project directory: ");
const std::string not_initialized("Test data set is not initialized");
const std::string output_dir("dogen.code_generation_test_output");

const std::string path_dogen("dogen");
const std::string path_dogen_cli("dogen.cli");
const std::string path_dogen_physical("dogen.physical");
const std::string path_dogen_dia("dogen.dia");
const std::string path_dogen_org("dogen.org");
const std::string path_dogen_tracing("dogen.tracing");
const std::string path_dogen_codec("dogen.codec");
const std::string path_dogen_text("dogen.text");
const std::string path_dogen_logical("dogen.logical");
const std::string path_dogen_templating("dogen.templating");
const std::string path_dogen_orchestration("dogen.orchestration");
const std::string path_dogen_utility("dogen.utility");
const std::string path_dogen_variability("dogen.variability");
const std::string path_dogen_relational("dogen.relational");
const std::string path_dogen_identification("dogen.identification");

}

using boost::filesystem::path;

namespace dogen::utility::test_data {

path dogen_product::project_directory_;
path dogen_product::output_directory_;
std::vector<path> dogen_product::reference_directories_;

void dogen_product::initialize() {
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

    reference_directories_.
        push_back(project_directory_ / path_dogen / "modeling");
    reference_directories_.
        push_back(project_directory_ / path_dogen_cli / "modeling");
    reference_directories_.
        push_back(project_directory_ / path_dogen_physical / "modeling");
    reference_directories_.
        push_back(project_directory_ / path_dogen_dia / "modeling");
    reference_directories_.
        push_back(project_directory_ / path_dogen_org / "modeling");
    reference_directories_.
        push_back(project_directory_ / path_dogen_tracing / "modeling");
    reference_directories_.
        push_back(project_directory_ / path_dogen_codec / "modeling");
    reference_directories_.
        push_back(project_directory_ / path_dogen_text / "modeling");
    reference_directories_.
        push_back(project_directory_ / path_dogen_logical / "modeling");
    reference_directories_.
        push_back(project_directory_ / path_dogen_templating / "modeling");
    reference_directories_.
        push_back(project_directory_ / path_dogen_orchestration / "modeling");
    reference_directories_.
        push_back(project_directory_ / path_dogen_utility / "modeling");
    reference_directories_.
        push_back(project_directory_ / path_dogen_variability / "modeling");
    reference_directories_.
        push_back(project_directory_ / path_dogen_relational / "modeling");
    reference_directories_.
        push_back(project_directory_ / path_dogen_identification / "modeling");
    reference_directories_.
        push_back(project_directory_ / "dogen.modeling" / "org");

    output_directory_ = boost::filesystem::absolute(output_dir);
}

void dogen_product::ensure_initialized() {
    if (project_directory_.empty())
        BOOST_THROW_EXCEPTION(test_data_exception(not_initialized));
}

path dogen_product::project_directory() {
    ensure_initialized();
    return project_directory_;
}

path dogen_product::output_directory() {
    ensure_initialized();
    return output_directory_;
}

const std::vector<boost::filesystem::path>&
dogen_product::reference_directories() {
    return reference_directories_;
}

/*
 * Org paths
 */
path dogen_product::input_dogen_org() {
    ensure_initialized();
    const std::string fn(path_dogen + ".org");
    return project_directory_ / path_dogen / "modeling" / fn;
}

path dogen_product::input_dogen_physical_org() {
    ensure_initialized();
    const std::string fn(path_dogen_physical + ".org");
    return project_directory_ / path_dogen_physical / "modeling" / fn;
}

path dogen_product::input_dogen_cli_org() {
    ensure_initialized();
    const std::string fn(path_dogen_cli + ".org");
    return project_directory_ / path_dogen_cli / "modeling" / fn;
}

path dogen_product::input_dogen_dia_org() {
    ensure_initialized();
    const std::string fn(path_dogen_dia + ".org");
    return project_directory_ / path_dogen_dia / "modeling" / fn;
}

path dogen_product::input_dogen_org_org() {
    ensure_initialized();
    const std::string fn(path_dogen_org + ".org");
    return project_directory_ / path_dogen_org / "modeling" / fn;
}

path dogen_product::input_dogen_tracing_org() {
    ensure_initialized();
    const std::string fn(path_dogen_tracing + ".org");
    return project_directory_ / path_dogen_tracing / "modeling" / fn;
}

path dogen_product::input_dogen_codec_org() {
    ensure_initialized();
    const std::string fn(path_dogen_codec + ".org");
    return project_directory_ / path_dogen_codec / "modeling" / fn;
}

path dogen_product::input_dogen_text_org() {
    ensure_initialized();
    const std::string fn(path_dogen_text + ".org");
    return project_directory_ / path_dogen_text / "modeling" / fn;
}

path dogen_product::input_dogen_logical_org() {
    ensure_initialized();
    const std::string fn(path_dogen_logical + ".org");
    return project_directory_ / path_dogen_logical / "modeling" / fn;
}

path dogen_product::input_dogen_templating_org() {
    ensure_initialized();
    const std::string fn(path_dogen_templating + ".org");
    return project_directory_ / path_dogen_templating / "modeling" / fn;
}

path dogen_product::input_dogen_orchestration_org() {
    ensure_initialized();
    const std::string fn(path_dogen_orchestration + ".org");
    return project_directory_ / path_dogen_orchestration / "modeling" / fn;
}

path dogen_product::input_dogen_utility_org() {
    ensure_initialized();
    const std::string fn(path_dogen_utility + ".org");
    return project_directory_ / path_dogen_utility / "modeling" / fn;
}

path dogen_product::input_dogen_variability_org() {
    ensure_initialized();
    const std::string fn(path_dogen_variability + ".org");
    return project_directory_ / path_dogen_variability / "modeling" / fn;
}

path dogen_product::input_dogen_relational_org() {
    ensure_initialized();
    const std::string fn(path_dogen_relational + ".org");
    return project_directory_ / path_dogen_relational / "modeling" / fn;
}

path dogen_product::input_dogen_identification_org() {
    ensure_initialized();
    const std::string fn(path_dogen_identification + ".org");
    return project_directory_ / path_dogen_identification / "modeling" / fn;
}

}
