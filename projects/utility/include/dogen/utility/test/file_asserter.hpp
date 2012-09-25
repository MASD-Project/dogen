/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_TEST_FILE_ASSERTER_HPP
#define DOGEN_UTILITY_TEST_FILE_ASSERTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <memory>
#include <boost/filesystem/path.hpp>

namespace dogen {
namespace utility {
namespace test {

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

} } }

#endif
