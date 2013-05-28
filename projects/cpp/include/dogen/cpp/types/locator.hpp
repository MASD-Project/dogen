/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_CPP_TYPES_LOCATOR_HPP
#define DOGEN_CPP_TYPES_LOCATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen/config/types/cpp_settings.hpp"
#include "dogen/cpp/types/content_descriptor.hpp"
#include "dogen/config/types/cpp_facet_types.hpp"
#include "dogen/cpp/types/file_types.hpp"
#include "dogen/cpp/types/aspect_types.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Manages the file names for all generated files and all the
 * pre-processor includes.
 */
class locator {
public:
    locator() = delete;
    locator(const locator&) = default;
    ~locator() = default;
    locator& operator=(const locator&) = delete;

public:
    locator(locator&& rhs);
    locator(const std::string& model_name,
        const config::cpp_settings& settings);

public:
    typedef boost::filesystem::path path;

private:
    /**
     * @brief Returns the directory that houses the given facet.
     */
    std::string facet_directory(const config::cpp_facet_types ft) const;

    /**
     * @brief Returns a postfix to append to filenames in a given
     * facet.
     */
    std::string facet_postfix(const config::cpp_facet_types ft) const;

    /**
     * @brief Returns a postfix to append to filenames that implement
     * a certain aspect.
     */
    std::string aspect_postfix(const aspect_types at) const;

    /**
     * @brief Returns the directory for the given file type.
     */
    path file_type_directory(const file_types flt) const;

    /**
     * @brief Returns the extension for the given file type.
     */
    std::string extension(const file_types flt) const;

public:
    /**
     * @brief Returns the path to place a file with content described
     * by the supplied content descriptor.
     *
     * @b Includes the external package path. Logical relative paths
     * are used for include files; they need to take into account
     * existing namespaces the user may have already defined.
     */
    path relative_logical_path(const content_descriptor& cd) const;

    /**
     * @brief Returns the path to place a file with content described
     * by the supplied content descriptor.
     *
     * @b Excludes the external package path. When combined with the
     * source or include directories, the physical path matches the
     * location on the hard drive for the artefact in question.
     */
    path relative_physical_path(const content_descriptor& cd) const;

    /**
     * @brief Returns the absolute path for the descriptor, taking
     * into account source and include directories, etc.
     */
    path absolute_path(const content_descriptor& cd) const;

    /**
     * @brief Returns an absolute path into the source directory for
     * the current model.
     *
     * @param name name of the item we're getting the path for.
     */
    path absolute_path_to_src(const std::string& name) const;

    /**
     * @brief Returns an absolute path into the include directory for
     * the current model.
     *
     * @param name name of the item we're getting the path for.
     */
    path absolute_path_to_include(const std::string& name) const;

    /**
     * @brief Returns an absolute path into the top level directory,
     * if split projects is not on.
     *
     * @param name name of the item we're getting the path for.
     */
    path absolute_path(const std::string& name) const;

    /**
     * @brief Returns the list of directories this location manager is
     * managing.
     */
    std::vector<boost::filesystem::path> managed_directories() const;

private:
    const std::string model_name_;
    const config::cpp_settings settings_;
    boost::filesystem::path source_directory_;
    boost::filesystem::path include_directory_;
};

} }

#endif
