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
#ifndef DOGEN_UTILITY_TEST_DATA_RESOLVER_HPP
#define DOGEN_UTILITY_TEST_DATA_RESOLVER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>

namespace dogen::utility::test_data {

class resolver {
public:
    resolver() = delete;
    resolver(const resolver&) = delete;
    ~resolver() = delete;
    resolver(resolver&&) = delete;
    resolver& operator=(const resolver&) = delete;

private:
    /**
     * @brief Returns the full path to the @e output test data
     * directory.
     *
     * @pre Expects the current working directory to be one up from the
     * test data directory, e.g. it should be located at ../test_data.
     */
    static boost::filesystem::path test_data_directory();

public:
    /**
     * @brief Converts the relative path into an absolute path into
     * the test data directory.
     */
    static boost::filesystem::path resolve(boost::filesystem::path relative);
};

}

#endif
