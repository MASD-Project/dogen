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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_LOCATOR_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_LOCATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/dynamic/types/field_definition.hpp"
#include "dogen/yarn/types/name.hpp"
#include "dogen/quilt.cpp/types/formatters/container.hpp"
#include "dogen/quilt.cpp/types/formattables/locator_configuration.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

/**
 * @brief Generates paths for project items, given qualified name.
 */
class locator {
public:
    locator(
        const boost::filesystem::path& project_directory_path,
        const dynamic::repository& drp, const formatters::container& fc,
        const dynamic::object& root_object, const yarn::name& model_name,
        const std::unordered_set<std::string>& module_ids);

private:
    struct facet_field_definitions {
        dynamic::field_definition directory;
        dynamic::field_definition postfix;
    };

    struct formatter_field_definitions {
        boost::optional<dynamic::field_definition> facet_directory;
        boost::optional<dynamic::field_definition> facet_postfix;
        dynamic::field_definition formatter_postfix;
    };

    struct field_definitions {
        std::unordered_map<std::string, facet_field_definitions>
        facets_field_definitions;
        std::unordered_map<std::string, formatter_field_definitions>
        formatters_field_definitions;
        dynamic::field_definition header_file_extension;
        dynamic::field_definition implementation_file_extension;
        dynamic::field_definition include_directory_name;
        dynamic::field_definition source_directory_name;
        dynamic::field_definition disable_facet_directories;
    };

    field_definitions make_field_definitions(const dynamic::repository& drp,
        const formatters::container& fc) const;

    locator_configuration make_configuration(const field_definitions& fds,
        const dynamic::object& o) const;

    locator_configuration make_configuration(const dynamic::repository& drp,
        const formatters::container& fc, const dynamic::object& o);

private:
    /**
     * @brief Given a formatter name, returns its configuration.
     *
     * @pre Formatter must have a configuration.
     */
    const locator_formatter_configuration& configuration_for_formatter(
        const std::string& formatter_name) const;

private:
    /**
     * @brief Returns the absolute path to the project folder.
     */
    boost::filesystem::path make_project_path(
        const boost::filesystem::path& project_directory_path,
        const yarn::name& model_name) const;

    /**
     * @brief Generates the facet path segment of a file path.
     *
     * The facet path segment is the same for both include and source
     * folders; it starts at the facet and includes the file name.
     */
    boost::filesystem::path make_facet_path(const std::string& formatter_name,
        const std::string& extension, const yarn::name& n) const;

    /**
     * @brief Builds a relative path from the top-level include
     * directory for the supplied qualified name.
     */
    boost::filesystem::path make_inclusion_path(
        const std::string& formatter_name, const std::string& extension,
        const yarn::name& n) const;

public:
    /**
     * @brief Generate the inclusion path for C++ headers.
     */
    boost::filesystem::path make_inclusion_path_for_cpp_header(
        const yarn::name& n, const std::string& formatter_name) const;

    /**
     * @brief Generate the full path for C++ headers.
     */
    boost::filesystem::path make_full_path_for_cpp_header(
        const yarn::name& n, const std::string& formatter_name) const;

    /**
     * @brief Generate the full path for C++ implementation.
     */
    boost::filesystem::path make_full_path_for_cpp_implementation(
        const yarn::name& n, const std::string& formatter_name) const;

    /**
     * @brief Generate the full path for cmakelists in include.
     */
    boost::filesystem::path make_full_path_for_include_cmakelists(
        const yarn::name& n, const std::string& formatter_name) const;

    /**
     * @brief Generate the full path for cmakelists in source.
     */
    boost::filesystem::path make_full_path_for_source_cmakelists(
        const yarn::name& n, const std::string& formatter_name) const;

    /**
     * @brief Generate the full path for odb options.
     */
    boost::filesystem::path make_full_path_for_odb_options(
        const yarn::name& n, const std::string& formatter_name) const;

private:
    const yarn::name& model_name_;
    const locator_configuration configuration_;
    const std::unordered_set<std::string> module_ids_;
    const boost::filesystem::path project_path_;
};

} } } }

#endif
