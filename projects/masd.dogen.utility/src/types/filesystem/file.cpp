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
#include <boost/filesystem/operations.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/filesystem/file_not_found.hpp"
#include "masd.dogen.utility/types/filesystem/file.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("utility.filesystem.file"));

const std::string invalid_directory("Not a directory: ");
const std::string file_not_found("File not found: ");
const std::string directory_not_found("Could not find directory: ");

const std::string dot(".");

}

namespace masd::dogen::utility::filesystem {

std::string read_file_content(std::istream& s) {
    s.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::string r(
        (std::istreambuf_iterator<char>(s)),
        std::istreambuf_iterator<char>());
    return r;
}

std::string read_file_content(const boost::filesystem::path& path) {
    if (!boost::filesystem::exists(path)) {
        const auto gs(path.generic_string());
        BOOST_LOG_SEV(lg, error) << ::file_not_found << gs;
        BOOST_THROW_EXCEPTION(file_not_found(gs));
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

    if (!boost::filesystem::exists(d)) {
        const auto gs(d.generic_string());
        BOOST_LOG_SEV(lg, error) << directory_not_found << gs;
        BOOST_THROW_EXCEPTION(file_not_found(directory_not_found + gs));
    }

    if (!boost::filesystem::is_directory(d)) {
        const auto gs(d.generic_string());
        BOOST_LOG_SEV(lg, error) << invalid_directory << gs;
        BOOST_THROW_EXCEPTION(file_not_found(invalid_directory + gs));
    }

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

std::set<boost::filesystem::path>
find_files(const std::list<boost::filesystem::path>& dirs) {
    std::set<boost::filesystem::path> r;

    for (const auto& d : dirs) {
        const auto files(find_files(d));
        r.insert(files.begin(), files.end());
    }

    return r;
}

boost::filesystem::path find_file_recursively_upwards(
    boost::filesystem::path starting_directory,
    const boost::filesystem::path& relative_file_path) {

    BOOST_LOG_SEV(lg, debug) << "Starting directory: " << starting_directory
                             << " relative file path: " << relative_file_path;

    if (relative_file_path.is_absolute()) {
        /*
         * User is lying, the path is already absolute.
         */
        const auto gs(relative_file_path.generic_string());
        BOOST_LOG_SEV(lg, debug) << "Path is absolute: " << gs;
        return relative_file_path;
    }

    if (starting_directory.empty())
        starting_directory = boost::filesystem::current_path();

    if (!boost::filesystem::is_directory(starting_directory)) {
        const auto gs(starting_directory.generic_string());
        BOOST_LOG_SEV(lg, error) << invalid_directory << gs;
        BOOST_THROW_EXCEPTION(file_not_found(invalid_directory + gs));
    }

    using namespace boost::filesystem;
    auto directory_path(starting_directory);

    do {
        path abs = absolute(directory_path / relative_file_path);
        BOOST_LOG_SEV(lg, debug) << "Trying: " << abs.generic_string();

        if (exists(abs)) {
            BOOST_LOG_SEV(lg, debug) << "Found file.";
            return abs;
        }

        directory_path = directory_path.parent_path();
    } while (directory_path.has_parent_path());

    const auto gs(relative_file_path.generic_string());
    BOOST_LOG_SEV(lg, debug) << "Could not find file: " << gs;
    return path();
}

void remove(const std::list<boost::filesystem::path>& files) {
    for (const auto f : files) {
        BOOST_LOG_SEV(lg, debug) << "Removing file: " << f.generic_string();
        boost::filesystem::remove(f);
    }
}

}
