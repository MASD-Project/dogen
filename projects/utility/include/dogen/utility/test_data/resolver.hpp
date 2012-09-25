/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_TEST_DATA_RESOLVER_HPP
#define DOGEN_UTILITY_TEST_DATA_RESOLVER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>

namespace dogen {
namespace utility {
namespace test_data {

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

} } }

#endif
