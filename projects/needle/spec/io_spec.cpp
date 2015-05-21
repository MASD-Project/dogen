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
#include <sstream>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/needle/core/io/jsonify_io.hpp"
#include "dogen/utility/test/logging.hpp"

namespace {

const std::string empty;
const std::string test_module("needle");
const std::string test_suite("io_spec");

}

using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(io)

BOOST_AUTO_TEST_CASE(jsonification_of_integers_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_integers_produces_expected_result");

    std::ostringstream ss;
    const unsigned int ui(10);
    std::string expected("10");
    ss << dogen::needle::core::io::jsonify(ui);
    BOOST_CHECK(asserter::assert_object(ss.str(), expected));
    ss.str("");

    const int i(-11);
    expected = "-11";
    ss << dogen::needle::core::io::jsonify(i);
    BOOST_CHECK(asserter::assert_object(ss.str(), expected));
    ss.str("");

    const unsigned short us(12);
    expected = "12";
    ss << dogen::needle::core::io::jsonify(us);
    BOOST_CHECK(asserter::assert_object(ss.str(), expected));
    ss.str("");

    const short s(-13);
    expected = "-13";
    ss << dogen::needle::core::io::jsonify(s);
    BOOST_CHECK(asserter::assert_object(ss.str(), expected));
    ss.str("");

    const unsigned long ul(14);
    expected = "14";
    ss << dogen::needle::core::io::jsonify(ul);
    BOOST_CHECK(asserter::assert_object(ss.str(), expected));
    ss.str("");

    const short l(-15);
    expected = "-15";
    ss << dogen::needle::core::io::jsonify(l);
    BOOST_CHECK(asserter::assert_object(ss.str(), expected));
    ss.str("");
}

BOOST_AUTO_TEST_CASE(jsonification_of_floating_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_floating_produces_expected_result");

    std::ostringstream ss;
    const double d(0.000001);
    std::string expected = "0.000001";
    ss << dogen::needle::core::io::jsonify(d);
    BOOST_CHECK(asserter::assert_object(ss.str(), expected));
    ss.str("");

    const float f(0.000002);
    expected = "0.000002";
    ss << dogen::needle::core::io::jsonify(f);
    BOOST_CHECK(asserter::assert_object(ss.str(), expected));
    ss.str("");
}

BOOST_AUTO_TEST_SUITE_END()
