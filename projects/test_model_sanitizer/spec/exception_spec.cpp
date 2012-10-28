/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <boost/test/unit_test.hpp>
#include <boost/throw_exception.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/exception/domain/all.hpp"
#include "dogen/exception/io/all_io.hpp"
#include "dogen/exception/serialization/all_ser.hpp"
#include "dogen/exception/test_data/all_td.hpp"
#include "dogen/exception/hash/all_hash.hpp"

namespace {

const std::string empty;
const std::string test_module("test_model_sanitizer");
const std::string test_suite("exception");

}

using namespace dogen::exception;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(exception)

BOOST_AUTO_TEST_CASE(exception_shall_be_usable_as_a_standard_exception) {
    SETUP_TEST_LOG_SOURCE("exception_shall_be_usable_as_a_standard_exception");
    const std::string message("test message");
    try {
        throw(my_error(message));
        BOOST_FAIL("Expected exception to be thrown.");
    } catch(const std::exception& e) {
        const std::string what(e.what());
        BOOST_CHECK(what == message);
        BOOST_LOG_SEV(lg, info) << "Exception thrown as expected. what: "
                                << e.what();
        BOOST_CHECK(true);
    }
}

BOOST_AUTO_TEST_CASE(exception_shall_be_usable_as_a_boost_exception) {
    SETUP_TEST_LOG_SOURCE("exception_shall_be_usable_as_a_boost_exception");
    const std::string message("test message");
    try {
        BOOST_THROW_EXCEPTION(my_error(message));
        BOOST_FAIL("Expected exception to be thrown.");
    } catch(const boost::exception& e) {
        BOOST_LOG_SEV(lg, debug) << "Exception thrown as expected. diagnostic: "
                                 << boost::diagnostic_information(e);
        BOOST_CHECK(true);
    }
}

BOOST_AUTO_TEST_SUITE_END()
