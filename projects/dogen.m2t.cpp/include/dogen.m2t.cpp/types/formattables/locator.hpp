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
#ifndef DOGEN_M2T_CPP_TYPES_FORMATTABLES_LOCATOR_HPP
#define DOGEN_M2T_CPP_TYPES_FORMATTABLES_LOCATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.logical/types/entities/name.hpp"
#include "dogen.m2t.cpp/types/transforms/repository.hpp"
#include "dogen.m2t.cpp/types/formattables/locator_configuration.hpp"

namespace dogen::m2t::cpp::formattables {

/**
 * @brief Generates paths for project items, given qualified name.
 */
class locator {
public:
    locator(
        const boost::filesystem::path& output_directory_path,
        const boost::filesystem::path& cpp_headers_output_directory_path,
        const variability::entities::feature_model& fm,
        const transforms::repository& frp,
        const variability::entities::configuration& rcfg,
        const logical::entities::name& model_name,
        const std::unordered_set<std::string>& module_ids,
        const bool enable_backend_directories);

private:
    struct facet_feature_group {
        variability::entities::feature directory;
        variability::entities::feature postfix;
    };

    struct formatter_feature_group {
        boost::optional<variability::entities::feature> facet_directory;
        boost::optional<variability::entities::feature> facet_postfix;
        variability::entities::feature archetype_postfix;
    };

    struct feature_group {
        std::unordered_map<std::string, facet_feature_group>
        facets_feature_group;
        std::unordered_map<std::string, formatter_feature_group>
        formatters_feature_group;
        variability::entities::feature header_file_extension;
        variability::entities::feature implementation_file_extension;
        variability::entities::feature include_directory_name;
        variability::entities::feature source_directory_name;
        variability::entities::feature tests_directory_name;
        variability::entities::feature templates_directory_name;
        variability::entities::feature disable_facet_directories;
        variability::entities::feature backend_directory_name;
        variability::entities::feature templates_file_extension;
    };

    feature_group make_feature_group(
        const variability::entities::feature_model& fm,
        const transforms::repository& frp) const;

    locator_configuration make_configuration(const feature_group& fg,
        const variability::entities::configuration& cfg) const;

    locator_configuration
    make_configuration(const variability::entities::feature_model& fm,
        const transforms::repository& frp,
        const variability::entities::configuration& cfg);

private:
    boost::filesystem::path compute_headers_path(
        const boost::filesystem::path& output_directory_path,
        const boost::filesystem::path& project_path,
        const boost::filesystem::path& cpp_headers_output_directory_path) const;

    boost::filesystem::path compute_templates_path(
        const boost::filesystem::path& project_path) const;

    /**
     * @brief Given a facet, returns its configuration.
     *
     * @pre Facet must have a configuration.
     */
    const locator_facet_configuration&
    configuration_for_facet(const std::string& facet) const;

    /**
     * @brief Given an archetype, returns its configuration.
     *
     * @pre Archetype must have a configuration.
     */
    const locator_archetype_configuration&
    configuration_for_archetype(const std::string& archetype) const;

public:
    /**
     * @brief Returns the extension used for header files.
     */
    std::string header_file_extension() const;

    /**
     * @brief Returns the extension used for implementation files.
     */
    std::string implementation_file_extension() const;

    /**
     * @brief Returns the postfix for the supplied facet.
     */
    std::string postfix_for_facet(const std::string& facet) const;

private:
    /**
     * @brief Returns the absolute path to the project folder.
     */
    boost::filesystem::path make_project_path(
        const boost::filesystem::path& output_directory_path,
        const logical::entities::name& model_name,
        const locator_configuration& lc,
        const bool enable_backend_directories) const;

    /**
     * @brief Generates the facet path segment of a file path.
     *
     * The facet path segment is the same for both include and source
     * folders; it starts at the facet and includes the file name.
     */
    boost::filesystem::path make_facet_path(const std::string& archetype,
        const std::string& extension, const logical::entities::name& n) const;
    boost::filesystem::path make_facet_path_temp(const std::string& archetype,
        const std::string& file_name, const logical::entities::name& n) const;

    /**
     * @brief Makes the first part of the inclusion path.
     */
    boost::filesystem::path
    make_inclusion_path_prefix(const logical::entities::name& n) const;

    /**
     * @brief Builds a relative path from the top-level include
     * directory for the supplied qualified name.
     */
    boost::filesystem::path make_inclusion_path(const std::string& archetype,
        const std::string& extension, const logical::entities::name& n) const;

public:
    /**
     * @brief Top-level project directory.
     */
    boost::filesystem::path project_path() const;

    /**
     * @brief Top-level headers project directory.
     */
    boost::filesystem::path headers_project_path() const;

    /**
     * @brief Top-level templates project directory.
     */
    boost::filesystem::path templates_project_path() const;

    /**
     * @brief Top-level headers model directory.
     */
    boost::filesystem::path headers_model_path() const;

public:
    /**
     * @brief Name of the include directory.
     */
    std::string include_directory_name() const;

    /**
     * @brief Name of the source directory.
     */
    std::string source_directory_name() const;

    /**
     * @brief Name of the tests directory.
     */
    std::string tests_directory_name() const;

    /**
     * @brief Name of the templates directory.
     */
    std::string templates_directory_name() const;

public:
    /**
     * @brief Generate the relative path to the include directory.
     */
    boost::filesystem::path make_relative_include_path(
        bool for_include_statement) const;

    /**
     * @brief Generate the relative path to the include directory for
     * a given facet.
     */
    boost::filesystem::path make_relative_include_path_for_facet(
        const std::string& facet, bool for_include_statement = false) const;

    /**
     * @brief Generate the inclusion path for C++ headers.
     */
    boost::filesystem::path make_inclusion_path_for_cpp_header(
        const logical::entities::name& n, const std::string& archetype) const;

    /**
     * @brief Generate the full path to the include directory
     */
    boost::filesystem::path make_full_path_to_include_directory() const;

    /**
     * @brief Generate the full path to the implementation directory
     */
    boost::filesystem::path make_full_path_to_implementation_directory() const;

    /**
     * @brief Generate the full path to the facet include directory.
     */
    boost::filesystem::path make_full_path_to_include_facet_directory(
        const std::string& facet) const;

    /**
     * @brief Generate the full path for C++ headers.
     */
    boost::filesystem::path make_full_path_for_cpp_header(
        const logical::entities::name& n, const std::string& archetype) const;

    /**
     * @brief Generate the relative implementation path for a facet.
     */
    boost::filesystem::path make_relative_implementation_path_for_facet(
        const std::string& facet) const;

    /**
     * @brief Generate the full path for templates.
     */
    boost::filesystem::path make_full_path_for_templates(
        const logical::entities::name& n, const std::string& archetype) const;

    /**
     * @brief Generate the full path for C++ implementation for tests
     */
    boost::filesystem::path make_full_path_for_tests_cpp_implementation(
        const logical::entities::name& n, const std::string& archetype) const;

    /**
     * @brief Generate the full path for entry point under tests.
     */
    boost::filesystem::path make_full_path_for_tests_cpp_main(
        const logical::entities::name& n, const std::string& archetype) const;

    /**
     * @brief Generate the full path for C++ implementation.
     */
    boost::filesystem::path make_full_path_for_cpp_implementation(
        const logical::entities::name& n, const std::string& archetype) const;

    /**
     * @brief Generate the full path for cmakelists in include.
     */
    boost::filesystem::path make_full_path_for_include_cmakelists(
        const logical::entities::name& n, const std::string& archetype) const;

    /**
     * @brief Generate the full path for cmakelists in source.
     */
    boost::filesystem::path make_full_path_for_source_cmakelists(
        const logical::entities::name& n, const std::string& archetype) const;

    /**
     * @brief Generate the full path for cmakelists in tests.
     */
    boost::filesystem::path make_full_path_for_tests_cmakelists(
        const logical::entities::name& n, const std::string& archetype) const;

    /**
     * @brief Generate the full path for cmakelists in source.
     */
    boost::filesystem::path make_full_path_for_msbuild_targets(
        const logical::entities::name& n, const std::string& archetype) const;

    /**
     * @brief Generate the relatvie path for odb options.
     */
    boost::filesystem::path make_relative_path_for_odb_options(
        const logical::entities::name& n, const std::string& archetype,
        bool include_source_directory = true) const;

    /**
     * @brief Generate the full path for odb options.
     */
    boost::filesystem::path make_full_path_for_odb_options(
        const logical::entities::name& n, const std::string& archetype) const;

    boost::filesystem::path make_full_path_for_project(
        const logical::entities::name& n, const std::string& archetype) const;

    boost::filesystem::path make_full_path_for_solution(
        const logical::entities::name& n, const std::string& archetype) const;

public:
    std::unordered_map<std::string, std::string> facet_directories() const;

private:
    const logical::entities::name& model_name_;
    const locator_configuration configuration_;
    const std::unordered_set<std::string> module_ids_;
    const boost::filesystem::path project_path_;
    const boost::filesystem::path headers_project_path_;
    const boost::filesystem::path templates_project_path_;
    const bool split_mode_;
};

}

#endif
