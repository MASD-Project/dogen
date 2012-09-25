/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_TEST_DATA_EMPTY_TDS_HPP
#define DOGEN_UTILITY_TEST_DATA_EMPTY_TDS_HPP

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
class empty_tds {
public:
    empty_tds() = delete;
    empty_tds(const empty_tds&) = delete;
    ~empty_tds() = delete;
    empty_tds(empty_tds&&) = delete;
    empty_tds& operator=(const empty_tds&) = delete;

public:
    static boost::filesystem::path data_set();
    static boost::filesystem::path target();
    static boost::filesystem::path expected();

    static boost::filesystem::path actual();
    static boost::filesystem::path actual_src();
    static boost::filesystem::path actual_include();
};

} } }

#endif
