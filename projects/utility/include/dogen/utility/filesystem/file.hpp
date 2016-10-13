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
#ifndef DOGEN_UTILITY_FILESYSTEM_FILE_HPP
#define DOGEN_UTILITY_FILESYSTEM_FILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <set>
#include <list>
#include <string>
#include <forward_list>
#include <boost/filesystem/path.hpp>

namespace dogen {
namespace utility {
namespace filesystem {

/**
 * @brief Returns the contents of the file.
 */
std::string read_file_content(std::istream& s);

/**
 * @brief Returns the contents of the file.
 */
std::string read_file_content(const boost::filesystem::path& path);

/**
 * @brief Writes the string to a file located at path.
 */
void write_file_content(const boost::filesystem::path& path,
    const std::string& content);

/**
 * @brief Returns all files available in directory, recursively.
 *
 * Returned paths are absolute paths.
 */
std::set<boost::filesystem::path> find_files(const boost::filesystem::path& d);

/**
 * @brief Returns all files available in all input directories, recursively.
 *
 * Returned paths are absolute paths. If you supply the same directory
 * multiple times, the files will be read multiple times but returned
 * on once in the set.
 */
std::set<boost::filesystem::path>
find_files(const std::vector<boost::filesystem::path>& dirs);

} } }

#endif
