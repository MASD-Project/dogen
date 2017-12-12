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
#ifndef DOGEN_UTILITY_TEST_DATA_SEAM_HPP
#define DOGEN_UTILITY_TEST_DATA_SEAM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>

namespace dogen {
namespace utility {
namespace test_data {

class seam {
public:
    seam() = delete;
    seam(const seam&) = delete;
    ~seam() = delete;
    seam(seam&&) = delete;
    seam& operator=(const seam&) = delete;

public:
    static boost::filesystem::path data_set();

    static boost::filesystem::path expected();
    static boost::filesystem::path expected_simple_template_stitch_cpp();
    static boost::filesystem::path expected_empty_template_stitch_cpp();
    static boost::filesystem::path expected_complex_template_stitch_cpp();

    static boost::filesystem::path actual();
    static boost::filesystem::path actual_simple_template_stitch_cpp();
    static boost::filesystem::path actual_empty_template_stitch_cpp();
    static boost::filesystem::path actual_complex_template_stitch_cpp();

};

} } }

#endif
