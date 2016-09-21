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
#ifndef DOGEN_QUILT_CPP_TYPES_PROPERTIES_LOCATOR_HPP
#define DOGEN_QUILT_CPP_TYPES_PROPERTIES_LOCATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "dogen/options/types/cpp_options.hpp"
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/model.hpp"
#include "dogen/quilt.cpp/types/annotations/path_annotations.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

/**
 * @brief Generates paths for project items, given qualified name.
 */
class locator {
public:
    locator(const options::cpp_options& opts, const yarn::model& m,
        const std::unordered_map<std::string, annotations::path_annotations>& ps);

private:
    /**
     * @brief Retrieves the ids of all the modules in the model.
     */
    std::unordered_set<std::string> module_ids(const yarn::model& m) const;

private:
    /**
     * @brief Given a formatter name, returns its path annotations.
     *
     * @pre Formatter must have path annotations.
     */
    const annotations::path_annotations& path_annotations_for_formatter(
        const std::string& formatter_name) const;

private:
    /**
     * @brief Returns the absolute path to the project folder.
     */
    boost::filesystem::path make_project_path(
        const options::cpp_options& opts,
        const yarn::name& model_name) const;

    /**
     * @brief Generates the facet path segment of a file path.
     *
     * The facet path segment is the same for both include and source
     * folders; it starts at the facet and includes the file name.
     */
    boost::filesystem::path make_facet_path(const annotations::path_annotations& ps,
        const std::string& extension, const yarn::name& n) const;

    /**
     * @brief Builds a relative path from the top-level include
     * directory for the supplied qualified name.
     */
    boost::filesystem::path make_inclusion_path(
        const annotations::path_annotations& ps,
        const std::string& extension,
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
    const std::unordered_map<std::string, annotations::path_annotations>&
    path_annotations_;
    const std::unordered_set<std::string> module_ids_;
    const boost::filesystem::path project_path_;
};

} } } }

#endif
