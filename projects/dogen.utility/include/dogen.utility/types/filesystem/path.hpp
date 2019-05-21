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
#ifndef DOGEN_UTILITY_FILESYSTEM_PATH_HPP
#define DOGEN_UTILITY_FILESYSTEM_PATH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>

namespace dogen::utility::filesystem {

/**
 * @brief Returns the full path to the directory containing the
 * executable.
 */
boost::filesystem::path executable_directory();

/**
 * @brief Returns the path to the directory containing the shared
 * files.
 *
 * We could not find a sensible way of implementing this in a
 * cross-platform way. For instance, we couldn't hard code the path
 * because some installers allow the user to change the installation
 * directory (such as NSIS on Windows, etc).
 *
 * Instead we are using a basic algorithm. We try to locate a folder
 * called @e data by searching the following places, relative to the
 * location of the binary, in order of precedence:
 *
 * @li the current directory;
 * @li the parent directory;
 * @li a sub-folder called @e share in the parent directory;
 * @li a sub-folder called @e share/dogen-VERSION in the parent
 * directory, where @e VERSION is the current dogen version;
 * @li a sub-folder called @e share/dogen in the parent directory;
 *
 * If the folder is not found, the function throws an exception.
 */
boost::filesystem::path library_directory();

}

#endif
