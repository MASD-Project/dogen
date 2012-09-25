/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_UTILITY_TEST_BYTEWISE_FILE_ASSERTER_HPP
#define DOGEN_UTILITY_TEST_BYTEWISE_FILE_ASSERTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include "dogen/utility/test/file_asserter.hpp"

namespace dogen {
namespace utility {
namespace test {

class bytewise_file_asserter : public file_asserter {
public:
    bytewise_file_asserter() = default;
    bytewise_file_asserter(const bytewise_file_asserter&) = default;
    bytewise_file_asserter(bytewise_file_asserter&&) = default;
    bytewise_file_asserter& operator=(const bytewise_file_asserter&) = default;

public:
    virtual ~bytewise_file_asserter() noexcept {}

public:
    virtual bool is_assertable(boost::filesystem::path path) const override;
    virtual bool assert_file(boost::filesystem::path expected,
        boost::filesystem::path actual) const override;
};

} } }

#endif
