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
#include "dogen.utility/types/test_data/cpp_ref_impl_product.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("utility.cpp_ref_impl_product"));

const std::string cpp_ref_impl_project_directory_env(
    "CPP_REF_IMPL_PROJECTS_DIRECTORY");

const std::string project_dir_not_found(
    "Could not find project directory: ");
const std::string not_initialized("Test data set is not initialized");
const std::string output_dir("cpp_ref_impl.code_generation_test_output");

const std::string models_dia_dir("cpp_ref_impl.models/dia");
const std::string models_json_dir("cpp_ref_impl.models/json");
const std::string models_org_dir("cpp_ref_impl.models/org");

/*
 * Dia
 */
const std::string path_cpp_ref_impl_boost_model_dia(
    "cpp_ref_impl.boost_model.dia");
const std::string path_cpp_ref_impl_colours_dia(
    "cpp_ref_impl.colours.dia");
const std::string path_cpp_ref_impl_compressed_dia(
    "cpp_ref_impl.compressed.dia");
const std::string path_cpp_ref_impl_cpp_98_dia(
    "cpp_ref_impl.cpp_98.dia");
const std::string path_cpp_ref_impl_cpp_model_dia(
    "cpp_ref_impl.cpp_model.dia");
const std::string path_cpp_ref_impl_directory_settings_dia(
    "cpp_ref_impl.directory_settings.dia");
const std::string path_cpp_ref_impl_disable_cmakelists_dia(
    "cpp_ref_impl.disable_cmakelists.dia");
const std::string path_cpp_ref_impl_disable_facet_folders_dia(
    "cpp_ref_impl.disable_facet_folders.dia");
const std::string path_cpp_ref_impl_enable_facet_hash_dia(
    "cpp_ref_impl.enable_facet_hash.dia");
const std::string path_cpp_ref_impl_enable_facet_io_dia(
    "cpp_ref_impl.enable_facet_io.dia");
const std::string path_cpp_ref_impl_enable_facet_serialization_dia(
    "cpp_ref_impl.enable_facet_serialization.dia");
const std::string path_cpp_ref_impl_enable_facet_types_dia(
    "cpp_ref_impl.enable_facet_types.dia");
const std::string path_cpp_ref_impl_flat_directory_mode_dia(
    "cpp_ref_impl.flat_directory_mode.dia");
const std::string path_cpp_ref_impl_lam_model_dia(
    "cpp_ref_impl.lam_model.dia");
const std::string path_cpp_ref_impl_northwind_dia(
    "cpp_ref_impl.northwind.dia");
const std::string path_cpp_ref_impl_split_project_dia(
    "cpp_ref_impl.split_project.dia");
const std::string path_cpp_ref_impl_std_model_dia(
    "cpp_ref_impl.std_model.dia");
const std::string path_cpp_ref_impl_two_layers_with_objects_dia(
    "cpp_ref_impl.two_layers.dia");
const std::string path_cpp_ref_impl_delete_extra_dia(
    "cpp_ref_impl.delete_extra.dia");
const std::string path_cpp_ref_impl_ignore_extra_dia(
    "cpp_ref_impl.ignore_extra.dia");
const std::string path_cpp_ref_impl_force_write_dia(
    "cpp_ref_impl.force_write.dia");
const std::string path_cpp_ref_impl_out_of_sync_dia(
    "cpp_ref_impl.out_of_sync.dia");
const std::string path_cpp_ref_impl_do_not_delete_empty_dirs_dia(
    "cpp_ref_impl.skip_empty_dirs.dia");

/*
 * JSON
 */
const std::string path_cpp_ref_impl_boost_model_json(
    "cpp_ref_impl.boost_model.json");
const std::string path_cpp_ref_impl_colours_json(
    "cpp_ref_impl.colours.json");
const std::string path_cpp_ref_impl_compressed_json(
    "cpp_ref_impl.compressed.json");
const std::string path_cpp_ref_impl_cpp_98_json(
    "cpp_ref_impl.cpp_98.json");
const std::string path_cpp_ref_impl_cpp_model_json(
    "cpp_ref_impl.cpp_model.json");
const std::string path_cpp_ref_impl_directory_settings_json(
    "cpp_ref_impl.directory_settings.json");
const std::string path_cpp_ref_impl_disable_cmakelists_json(
    "cpp_ref_impl.disable_cmakelists.json");
const std::string path_cpp_ref_impl_disable_facet_folders_json(
    "cpp_ref_impl.disable_facet_folders.json");
const std::string path_cpp_ref_impl_enable_facet_hash_json(
    "cpp_ref_impl.enable_facet_hash.json");
const std::string path_cpp_ref_impl_enable_facet_io_json(
    "cpp_ref_impl.enable_facet_io.json");
const std::string path_cpp_ref_impl_enable_facet_serialization_json(
    "cpp_ref_impl.enable_facet_serialization.json");
const std::string path_cpp_ref_impl_enable_facet_types_json(
    "cpp_ref_impl.enable_facet_types.json");
const std::string path_cpp_ref_impl_flat_directory_mode_json(
    "cpp_ref_impl.flat_directory_mode.json");
const std::string path_cpp_ref_impl_lam_model_json(
    "cpp_ref_impl.lam_model.json");
const std::string path_cpp_ref_impl_northwind_json(
    "cpp_ref_impl.northwind.json");
const std::string path_cpp_ref_impl_split_project_json(
    "cpp_ref_impl.split_project.json");
const std::string path_cpp_ref_impl_std_model_json(
    "cpp_ref_impl.std_model.json");
const std::string path_cpp_ref_impl_two_layers_with_objects_json(
    "cpp_ref_impl.two_layers.json");
const std::string path_cpp_ref_impl_delete_extra_json(
    "cpp_ref_impl.delete_extra.json");
const std::string path_cpp_ref_impl_ignore_extra_json(
    "cpp_ref_impl.ignore_extra.json");
const std::string path_cpp_ref_impl_force_write_json(
    "cpp_ref_impl.force_write.json");
const std::string path_cpp_ref_impl_out_of_sync_json(
    "cpp_ref_impl.out_of_sync.json");
const std::string path_cpp_ref_impl_do_not_delete_empty_dirs_json(
    "cpp_ref_impl.skip_empty_dirs.json");

/*
 * Org
 */
const std::string path_cpp_ref_impl_boost_model_org(
    "cpp_ref_impl.boost_model.org");
const std::string path_cpp_ref_impl_colours_org(
    "cpp_ref_impl.colours.org");
const std::string path_cpp_ref_impl_compressed_org(
    "cpp_ref_impl.compressed.org");
const std::string path_cpp_ref_impl_cpp_98_org(
    "cpp_ref_impl.cpp_98.org");
const std::string path_cpp_ref_impl_cpp_model_org(
    "cpp_ref_impl.cpp_model.org");
const std::string path_cpp_ref_impl_directory_settings_org(
    "cpp_ref_impl.directory_settings.org");
const std::string path_cpp_ref_impl_disable_cmakelists_org(
    "cpp_ref_impl.disable_cmakelists.org");
const std::string path_cpp_ref_impl_disable_facet_folders_org(
    "cpp_ref_impl.disable_facet_folders.org");
const std::string path_cpp_ref_impl_enable_facet_hash_org(
    "cpp_ref_impl.enable_facet_hash.org");
const std::string path_cpp_ref_impl_enable_facet_io_org(
    "cpp_ref_impl.enable_facet_io.org");
const std::string path_cpp_ref_impl_enable_facet_serialization_org(
    "cpp_ref_impl.enable_facet_serialization.org");
const std::string path_cpp_ref_impl_enable_facet_types_org(
    "cpp_ref_impl.enable_facet_types.org");
const std::string path_cpp_ref_impl_flat_directory_mode_org(
    "cpp_ref_impl.flat_directory_mode.org");
const std::string path_cpp_ref_impl_lam_model_org(
    "cpp_ref_impl.lam_model.org");
const std::string path_cpp_ref_impl_northwind_org(
    "cpp_ref_impl.northwind.org");
const std::string path_cpp_ref_impl_split_project_org(
    "cpp_ref_impl.split_project.org");
const std::string path_cpp_ref_impl_std_model_org(
    "cpp_ref_impl.std_model.org");
const std::string path_cpp_ref_impl_two_layers_with_objects_org(
    "cpp_ref_impl.two_layers.org");
const std::string path_cpp_ref_impl_delete_extra_org(
    "cpp_ref_impl.delete_extra.org");
const std::string path_cpp_ref_impl_ignore_extra_org(
    "cpp_ref_impl.ignore_extra.org");
const std::string path_cpp_ref_impl_force_write_org(
    "cpp_ref_impl.force_write.org");
const std::string path_cpp_ref_impl_out_of_sync_org(
    "cpp_ref_impl.out_of_sync.org");
const std::string path_cpp_ref_impl_do_not_delete_empty_dirs_org(
    "cpp_ref_impl.skip_empty_dirs.org");

}

using boost::filesystem::path;

namespace dogen::utility::test_data {

path cpp_ref_impl_product::project_directory_;
path cpp_ref_impl_product::dia_models_directory_;
path cpp_ref_impl_product::json_models_directory_;
path cpp_ref_impl_product::org_models_directory_;
path cpp_ref_impl_product::output_directory_;

void cpp_ref_impl_product::initialize() {
    using environment::variable_reader;
    const std::string proj_dir_env(
        variable_reader::strict_read_environment_variable(
            cpp_ref_impl_project_directory_env));

    project_directory_ = path(proj_dir_env);
    BOOST_LOG_SEV(lg, debug) << "Project directory: "
                             << project_directory_.generic_string();
    if (!boost::filesystem::exists(project_directory_)) {
        BOOST_LOG_SEV(lg, error) << project_dir_not_found
                                 << proj_dir_env;
        BOOST_THROW_EXCEPTION(
            test_data_exception(project_dir_not_found + proj_dir_env));
    }

    dia_models_directory_ = project_directory_ / models_dia_dir;
    json_models_directory_ = project_directory_ / models_json_dir;
    org_models_directory_ = project_directory_ / models_org_dir;
    BOOST_LOG_SEV(lg, debug) << "Dia models: "
                             << dia_models_directory_.generic_string()
                             << " JSON models: "
                             << json_models_directory_.generic_string();

    output_directory_ = boost::filesystem::absolute(output_dir);
}

void cpp_ref_impl_product::ensure_initialized() {
    if (project_directory_.empty())
        BOOST_THROW_EXCEPTION(test_data_exception(not_initialized));
}

path cpp_ref_impl_product::project_directory() {
    ensure_initialized();
    return project_directory_;
}

path cpp_ref_impl_product::output_directory() {
    ensure_initialized();
    return output_directory_;
}

/*
 * Dia
 */
path cpp_ref_impl_product::input_cpp_ref_impl_boost_model_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_boost_model_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_colours_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_colours_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_compressed_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_compressed_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_cpp_98_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_cpp_98_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_cpp_model_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_cpp_model_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_directory_settings_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_directory_settings_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_disable_cmakelists_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_disable_cmakelists_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_disable_facet_folders_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_disable_facet_folders_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_hash_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_enable_facet_hash_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_io_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_enable_facet_io_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_serialization_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_enable_facet_serialization_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_types_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_enable_facet_types_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_flat_directory_mode_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_flat_directory_mode_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_lam_model_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_lam_model_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_northwind_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_northwind_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_split_project_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_split_project_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_std_model_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_std_model_dia;
}

path cpp_ref_impl_product::
input_cpp_ref_impl_two_layers_with_objects_dia() {
    ensure_initialized();
    return dia_models_directory_ /
        path_cpp_ref_impl_two_layers_with_objects_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_delete_extra_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_delete_extra_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_ignore_extra_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_ignore_extra_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_force_write_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_force_write_dia;
}

path cpp_ref_impl_product::input_cpp_ref_impl_out_of_sync_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_out_of_sync_dia;
}

path cpp_ref_impl_product::
input_cpp_ref_impl_do_not_delete_empty_dirs_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_cpp_ref_impl_do_not_delete_empty_dirs_dia;
}

/*
 * JSON
 */
path cpp_ref_impl_product::input_cpp_ref_impl_boost_model_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_boost_model_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_colours_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_colours_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_compressed_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_compressed_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_cpp_98_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_cpp_98_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_cpp_model_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_cpp_model_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_directory_settings_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_directory_settings_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_disable_cmakelists_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_disable_cmakelists_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_disable_facet_folders_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_disable_facet_folders_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_hash_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_enable_facet_hash_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_io_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_enable_facet_io_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_serialization_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_enable_facet_serialization_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_types_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_enable_facet_types_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_flat_directory_mode_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_flat_directory_mode_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_lam_model_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_lam_model_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_northwind_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_northwind_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_split_project_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_split_project_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_std_model_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_std_model_json;
}

path cpp_ref_impl_product::
input_cpp_ref_impl_two_layers_with_objects_json() {
    ensure_initialized();
    return json_models_directory_ /
        path_cpp_ref_impl_two_layers_with_objects_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_delete_extra_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_delete_extra_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_ignore_extra_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_ignore_extra_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_force_write_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_force_write_json;
}

path cpp_ref_impl_product::input_cpp_ref_impl_out_of_sync_json() {
    ensure_initialized();
    return json_models_directory_ / path_cpp_ref_impl_out_of_sync_json;
}

path cpp_ref_impl_product::
input_cpp_ref_impl_do_not_delete_empty_dirs_json() {
    ensure_initialized();
    return json_models_directory_ /
        path_cpp_ref_impl_do_not_delete_empty_dirs_json;
}

/*
 * Org
 */
path cpp_ref_impl_product::input_cpp_ref_impl_boost_model_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_boost_model_org;
}

path cpp_ref_impl_product::input_cpp_ref_impl_colours_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_colours_org;
}

path cpp_ref_impl_product::input_cpp_ref_impl_cpp_98_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_cpp_98_org;
}

path cpp_ref_impl_product::input_cpp_ref_impl_cpp_model_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_cpp_model_org;
}

path cpp_ref_impl_product::input_cpp_ref_impl_directory_settings_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_directory_settings_org;
}

path cpp_ref_impl_product::input_cpp_ref_impl_disable_cmakelists_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_disable_cmakelists_org;
}

path cpp_ref_impl_product::input_cpp_ref_impl_disable_facet_folders_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_disable_facet_folders_org;
}

path cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_hash_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_enable_facet_hash_org;
}

path cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_io_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_enable_facet_io_org;
}

path cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_serialization_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_enable_facet_serialization_org;
}

path cpp_ref_impl_product::input_cpp_ref_impl_enable_facet_types_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_enable_facet_types_org;
}

path cpp_ref_impl_product::input_cpp_ref_impl_flat_directory_mode_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_flat_directory_mode_org;
}

path cpp_ref_impl_product::input_cpp_ref_impl_lam_model_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_lam_model_org;
}

path cpp_ref_impl_product::input_cpp_ref_impl_northwind_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_northwind_org;
}

path cpp_ref_impl_product::input_cpp_ref_impl_split_project_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_split_project_org;
}

path cpp_ref_impl_product::input_cpp_ref_impl_std_model_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_std_model_org;
}

path cpp_ref_impl_product::
input_cpp_ref_impl_two_layers_with_objects_org() {
    ensure_initialized();
    return org_models_directory_ /
        path_cpp_ref_impl_two_layers_with_objects_org;
}

path cpp_ref_impl_product::input_cpp_ref_impl_delete_extra_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_delete_extra_org;
}

path cpp_ref_impl_product::input_cpp_ref_impl_ignore_extra_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_ignore_extra_org;
}

path cpp_ref_impl_product::input_cpp_ref_impl_force_write_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_force_write_org;
}

path cpp_ref_impl_product::input_cpp_ref_impl_out_of_sync_org() {
    ensure_initialized();
    return org_models_directory_ / path_cpp_ref_impl_out_of_sync_org;
}

path cpp_ref_impl_product::
input_cpp_ref_impl_do_not_delete_empty_dirs_org() {
    ensure_initialized();
    return org_models_directory_ /
        path_cpp_ref_impl_do_not_delete_empty_dirs_org;
}

}
