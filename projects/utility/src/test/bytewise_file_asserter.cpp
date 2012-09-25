/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/test/bytewise_file_asserter.hpp"

namespace dogen {
namespace utility {
namespace test {

bool bytewise_file_asserter::is_assertable(boost::filesystem::path) const {
    return true;
}

bool bytewise_file_asserter::
assert_file(boost::filesystem::path expected,
    boost::filesystem::path actual) const {
    using dogen::utility::filesystem::read_file_content;
    const std::string expected_content(read_file_content(expected));
    const std::string actual_content(read_file_content(actual));

    using namespace dogen::utility::log;
    logger lg(logger_factory("bytewise_file_asserter"));


    if (expected_content == actual_content) {
        BOOST_LOG_SEV(lg, debug)
            << "Byte-wise file asserter: contents are equal.";
        return true;
    }

    BOOST_LOG_SEV(lg, debug) << "Byte-wise file asserter: contents differ.";
    BOOST_LOG_SEV(lg, debug) << "expected content: " << expected_content;
    BOOST_LOG_SEV(lg, debug) << "actual content: " << actual_content;
    BOOST_LOG_SEV(lg, debug) << "diff -u " << expected.string() << " "
                             << actual.string();
    return false;
}

} } }
