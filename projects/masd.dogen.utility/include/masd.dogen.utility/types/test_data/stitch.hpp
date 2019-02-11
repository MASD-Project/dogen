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
#ifndef MASD_DOGEN_UTILITY_TEST_DATA_STITCH_HPP
#define MASD_DOGEN_UTILITY_TEST_DATA_STITCH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>

namespace masd::dogen::utility::test_data {

class stitch {
public:
    stitch() = delete;
    stitch(const stitch&) = delete;
    ~stitch() = delete;
    stitch(stitch&&) = delete;
    stitch& operator=(const stitch&) = delete;

public:
    static boost::filesystem::path data_set();
    static boost::filesystem::path non_existent_file();

    static boost::filesystem::path input();
    static boost::filesystem::path input_simple_template_stitch();
    static boost::filesystem::path input_empty_template_stitch();
    static boost::filesystem::path input_complex_template_stitch();
};

}

#endif
