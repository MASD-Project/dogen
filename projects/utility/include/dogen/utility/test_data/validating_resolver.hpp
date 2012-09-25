/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_TEST_DATA_VALIDATING_RESOLVER_HPP
#define DOGEN_UTILITY_TEST_DATA_VALIDATING_RESOLVER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>

namespace dogen {
namespace utility {
namespace test_data {

class validating_resolver {
public:
    validating_resolver() = delete;
    validating_resolver(const validating_resolver&) = delete;
    ~validating_resolver() = delete;
    validating_resolver(validating_resolver&&) = delete;
    validating_resolver& operator=(const validating_resolver&) = delete;

public:
    /**
     * @brief Converts the relative path into an absolute path into
     * the test data directory and validates its existence.
     */
    static boost::filesystem::path resolve(boost::filesystem::path relative);
};

} } }

#endif
