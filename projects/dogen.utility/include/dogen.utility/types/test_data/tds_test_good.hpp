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
#ifndef DOGEN_UTILITY_TEST_DATA_TDS_TEST_GOOD_HPP
#define DOGEN_UTILITY_TEST_DATA_TDS_TEST_GOOD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>

namespace dogen::utility::test_data {

/**
 * @brief Manages the location of all files in the XML Reader test
 * data set.
 */
class tds_test_good {
public:
    tds_test_good() = delete;
    tds_test_good(const tds_test_good&) = delete;
    ~tds_test_good() = delete;
    tds_test_good(tds_test_good&&) = delete;
    tds_test_good& operator=(const tds_test_good&) = delete;

public:
    static boost::filesystem::path data_set();
    static boost::filesystem::path non_existent_file();

    static boost::filesystem::path input();
    static boost::filesystem::path input_non_empty_file_xml();
    static boost::filesystem::path input_non_empty_file_txt();
    static boost::filesystem::path input_file_1_xml();
    static boost::filesystem::path input_empty_file_txt();

    static boost::filesystem::path expected();
    static boost::filesystem::path expected_file_1_txt();
    static boost::filesystem::path expected_file_2_txt();
    static boost::filesystem::path expected_test_serializer_xmltst();
    static boost::filesystem::path expected_test_serializer_2_xmltst();
    static boost::filesystem::path expected_empty_file_txt();

    static boost::filesystem::path actual();
    static boost::filesystem::path actual_file_1_txt();
    static boost::filesystem::path actual_file_2_txt();
    static boost::filesystem::path actual_test_serializer_xmltst();
    static boost::filesystem::path actual_test_serializer_2_xmltst();
    static boost::filesystem::path actual_empty_file_txt();
};

}

#endif
