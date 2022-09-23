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
#include <sstream>
#include <forward_list>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include "dogen.utility/types/filesystem/io_error.hpp"


namespace dogen::utility::filesystem {

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
 * @brief Dump the object as a stream to the file.
 */
template<typename Ioable>
inline void write(const boost::filesystem::path& path,
    const Ioable& target) {
    try {
        boost::filesystem::ofstream stream(path);
        stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        stream << target;
    } catch (const std::exception& e) {
        std::ostringstream s;
        s << "An error occurred whilst trying to write a file. Path: '"
          << path.generic_string() << "'. Error: " << e.what();
        throw io_error(s.str());
    }
}

/**
 * @brief Returns all files available in all input directories, recursively.
 *
 * Returned paths are absolute paths. If you supply the same directory
 * multiple times, the files will be read multiple times but returned
 * on once in the set.
 */
/**@{*/
std::set<boost::filesystem::path>
find_files(const boost::filesystem::path& dir);
std::set<boost::filesystem::path>
find_files(const std::vector<boost::filesystem::path>& dirs);
std::set<boost::filesystem::path>
find_files(const std::list<boost::filesystem::path>& dirs);
/**@}*/

/**
 * @brief Finds the relative path, by searching recursively upwards
 * from the starting directory.
 */
boost::filesystem::path find_file_recursively_upwards(
    boost::filesystem::path starting_directory,
    const boost::filesystem::path& relative_file_path);

/**
 * @brief Deletes all files in the supplied list.
 */
void remove(const std::list<boost::filesystem::path>& files);

/**
 * @brief Removes all empty directories, recursively.
 */
/**@{*/
void remove_empty_directories(const boost::filesystem::path& dir);
void remove_empty_directories(const std::list<boost::filesystem::path>& dirs);
/**@}*/

/**
 * @brief If the directory exists, deletes it and recreates it. Otherwise,
 * creates it.
 *
 * @throws If the path points to a file.
 */
void recreate_directory(const boost::filesystem::path& dir);

}

#endif
