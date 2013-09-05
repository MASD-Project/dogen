/*
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
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/config/paths.hpp"
#include "dogen/utility/filesystem/file_not_found.hpp"

namespace {

const boost::filesystem::path build_data_dir(DATA_DIRECTORY_BUILD);
const boost::filesystem::path install_data_dir(DATA_DIRECTORY_INSTALL);

}

namespace dogen {
namespace utility {
namespace filesystem {

boost::filesystem::path data_directory() {
    if (boost::filesystem::exists(build_data_dir))
        return build_data_dir;

    if (boost::filesystem::exists(install_data_dir))
        return install_data_dir;

    BOOST_THROW_EXCEPTION(file_not_found(install_data_dir.string()));
}

} } }
