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
#ifndef MASD_DOGEN_UTILITY_TEST_FILE_ASSERTER_HPP
#define MASD_DOGEN_UTILITY_TEST_FILE_ASSERTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <boost/filesystem/path.hpp>

namespace masd::dogen::utility::test {

class file_asserter {
public:
    file_asserter(const file_asserter&) = default;
    virtual ~file_asserter() = default;
    file_asserter(file_asserter&&) = default;
    file_asserter& operator=(const file_asserter&) = default;

public:
    typedef std::shared_ptr<file_asserter> shared_ptr;

protected:
    file_asserter() = default;

public:
    virtual bool is_assertable(boost::filesystem::path path) const = 0;
    virtual bool assert_file(boost::filesystem::path expected,
        boost::filesystem::path actual) const = 0;
};

}

#endif
