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
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include "dogen/utility/test_data/test_data_exception.hpp"
#include "dogen/utility/test_data/resolver.hpp"

namespace {

const std::string test_data_dir_not_found("Test data directory not found");
const std::string relative_path_to_td_dir("../test_data");

}

namespace dogen {
namespace utility {
namespace test_data {

boost::filesystem::path resolver::test_data_directory() {
    const boost::filesystem::path rel(relative_path_to_td_dir);
    const boost::filesystem::path abs(boost::filesystem::absolute(rel));

    if (!boost::filesystem::exists(abs))
    {
        using dogen::utility::test_data::exception;
        throw exception(test_data_dir_not_found + abs.string());
    }
    return abs;
}

boost::filesystem::path
resolver::resolve(boost::filesystem::path relative) {
    boost::filesystem::path r(test_data_directory());
    r /= relative;
    return r;
}

} } }
