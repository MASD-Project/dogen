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
#include <boost/throw_exception.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>
#include "dogen/utility/filesystem/file_not_found.hpp"
#include "dogen/utility/filesystem/file.hpp"

namespace {

const std::string invalid_directory("Not a directory: ");
const std::string directory_not_found("Could not find directory: ");

}


namespace dogen {
namespace utility {
namespace filesystem {

std::string read_file_content(std::istream& s) {
    s.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::string r(
        (std::istreambuf_iterator<char>(s)),
        std::istreambuf_iterator<char>());
    return r;
}

std::string read_file_content(const boost::filesystem::path& path) {
    if (!boost::filesystem::exists(path)) {
        BOOST_THROW_EXCEPTION(file_not_found(path.string()));
    }

    boost::filesystem::ifstream s(path);
    return read_file_content(s);
}

void write_file_content(const boost::filesystem::path& path,
    const std::string& content) {
    boost::filesystem::ofstream stream(path);
    stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    stream << content;
}

std::set<boost::filesystem::path> find_files(const boost::filesystem::path& d) {
    std::set<boost::filesystem::path> r;

    if (!boost::filesystem::exists(d))
        BOOST_THROW_EXCEPTION(file_not_found(directory_not_found + d.string()));

    if (!boost::filesystem::is_directory(d))
        BOOST_THROW_EXCEPTION(file_not_found(invalid_directory + d.string()));

    using boost::filesystem::recursive_directory_iterator;
    for (recursive_directory_iterator end, i(d); i != end; ++i) {
        const auto& p(boost::filesystem::absolute(*i));
        if (boost::filesystem::is_regular_file(p))
            r.insert(p);
    }
    return r;
}

std::set<boost::filesystem::path>
find_files(const std::vector<boost::filesystem::path>& dirs) {
    std::set<boost::filesystem::path> r;

    for (const auto& d : dirs) {
        const auto files(find_files(d));
        r.insert(files.begin(), files.end());
    }

    return r;
}

boost::filesystem::path find_file_recursively_upwards(
    const boost::filesystem::path& starting_directory,
    const boost::filesystem::path& relative_file_path) {

    if (relative_file_path.is_absolute()) {
        /*
         * User is lying, the path is already absolute.
         */
        return relative_file_path;
    }

    if (!boost::filesystem::is_directory(starting_directory)) {
        const auto gs(starting_directory.generic_string());
        BOOST_THROW_EXCEPTION(file_not_found(invalid_directory + gs));
    }

    using namespace boost::filesystem;
    auto directory_path(starting_directory);

    do {
        path abs = absolute(directory_path / relative_file_path);
        if (exists(abs))
            return abs;

        directory_path = directory_path.parent_path();
    } while (directory_path.has_parent_path());

    return path();
}

} } }
