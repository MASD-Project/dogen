/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc_LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_TEST_DATA_FILESYSTEM_TESTS_HPP
#define DOGEN_UTILITY_TEST_DATA_FILESYSTEM_TESTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>

namespace dogen {
namespace utility {
namespace test_data {

/**
 * @brief Manages the location of all files in the XML Reader test
 * data set.
 */
class filesystem_tests {
public:
    filesystem_tests() = delete;
    filesystem_tests(const filesystem_tests&) = delete;
    ~filesystem_tests() = delete;
    filesystem_tests(filesystem_tests&&) = delete;
    filesystem_tests& operator=(const filesystem_tests&) = delete;

public:
    static boost::filesystem::path data_set();
    static boost::filesystem::path non_existent_file();

    static boost::filesystem::path input();
    static boost::filesystem::path input_non_empty_file_txt();
    static boost::filesystem::path input_empty_file_txt();

    static boost::filesystem::path expected();
    static boost::filesystem::path expected_some_file_txt();
    static boost::filesystem::path expected_file_to_overwrite_txt();

    static boost::filesystem::path actual();
    static boost::filesystem::path actual_some_file_txt();
    static boost::filesystem::path actual_file_to_overwrite_txt();
};

} } }

#endif
