/*
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
#include <sstream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/throw_exception.hpp>
#if defined __unix__ || defined __CYGWIN__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#elif defined _WIN32
#include <windows.h>
#endif
#include "dogen/version.hpp"
#include "dogen.utility/types/filesystem/path.hpp"
#include "dogen.utility/types/filesystem/file_not_found.hpp"

#ifdef __APPLE__
extern "C" int _NSGetExecutablePath(char* buf, unsigned int * bufsize);
#endif

namespace {

const std::string unsupported_operative_system(
    "Operative system not supported");
const std::string readlink_not_found("All readlinks to proc failed.");
const std::string executable_path_failure(
    "Error while obtaining path to executable");

const std::string linux_proc("/proc/self/exe");
const std::string freebsd_proc("/proc/curproc/file");
const std::string solaris_proc("/proc/self/path/a.out");

const boost::filesystem::path in_current_dir("./data");
const boost::filesystem::path in_dir_above("../data");
const boost::filesystem::path in_share_data_dir("../share/data");
const boost::filesystem::path in_share_dogen_versioned_dir(
    "../share/dogen-" DOGEN_VERSION);
const boost::filesystem::path in_share_dogen_dir("../share/dogen/data");

}

namespace dogen::utility::filesystem {

boost::filesystem::path executable_directory() {
#if defined __APPLE__
    char buffer[1024];
    unsigned int size = sizeof(buffer);
    if (_NSGetExecutablePath(buffer, &size) != 0)
        BOOST_THROW_EXCEPTION(file_not_found(executable_path_failure));

    return boost::filesystem::path(buffer).parent_path();

#elif defined __unix__
    char buffer[1024];

    // try via proc first
    ssize_t result = ::readlink(linux_proc.c_str(), buffer, sizeof(buffer) - 1);
    if (result < 0)
        result = ::readlink(freebsd_proc.c_str(), buffer, sizeof(buffer) - 1);

    if (result < 0)
        result = ::readlink(solaris_proc.c_str(), buffer, sizeof(buffer) - 1);

    if (result <= 0)
        BOOST_THROW_EXCEPTION(file_not_found(readlink_not_found));

    buffer[result] = '\0';
    return boost::filesystem::path(buffer).parent_path();

#elif defined _WIN32
    char buffer[MAX_PATH];
    ::GetModuleFileName(NULL, buffer, MAX_PATH);
    return boost::filesystem::path(buffer).parent_path();
#else
    BOOST_THROW_EXCEPTION(file_not_found(unsupported_operative_system));
#endif
}

boost::filesystem::path data_files_directory() {
    const auto ed(executable_directory());

    // shouldn't really happen, but just in case.
    auto r = boost::filesystem::absolute(ed / in_current_dir);
    if (boost::filesystem::exists(r))
        return r;

    // build directory
    r = boost::filesystem::absolute(ed / in_dir_above);
    if (boost::filesystem::exists(r))
        return r;

    // Windows, OSX, linux opt install
    r = boost::filesystem::absolute(ed / in_share_data_dir);
    if (boost::filesystem::exists(r))
        return r;

    // linux distributor, versioned install
    r = boost::filesystem::absolute(ed / in_share_dogen_versioned_dir);
    if (boost::filesystem::exists(r))
        return r;

    // linux distributor, non-versioned install
    r = boost::filesystem::absolute(ed / in_share_dogen_dir);
    if (boost::filesystem::exists(r))
        return r;

    std::ostringstream s;
    s << "Could not find data directory. Base directory: " << ed.string()
      << ". Locations searched: "
      << in_current_dir.string() << " "
      << in_dir_above.string() << " "
      << in_share_data_dir.string() << " "
      << in_share_dogen_versioned_dir.string() << " "
      << in_share_dogen_dir.string() << " ";

    BOOST_THROW_EXCEPTION(file_not_found(s.str()));
}

}
