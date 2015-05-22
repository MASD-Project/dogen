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
#include <ostream>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/needle/core/io/jsonify.hpp"
#include "dogen/needle/std/io/array_io.hpp"
#include "dogen/utility/test/logging.hpp"

namespace {

const std::string test_module("needle");
const std::string test_suite("io_spec");

struct test_object {
    test_object(const std::string& sp, const unsigned int ip)
        : s(sp), i(ip) {}

    std::string s;
    unsigned int i;
};

inline std::ostream& operator<<(std::ostream& s, const test_object& to) {
    using namespace dogen::needle::core::io;
    s << constants::open_object()
      << "\"s\": " << jsonify(to.s) << constants::separator()
      << "\"i\": " << jsonify(to.i)
      << constants::close_object();
    return(s);
}

}

using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(io)

BOOST_AUTO_TEST_CASE(jsonification_of_integers_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_integers_produces_expected_result");

    std::ostringstream ss;
    const unsigned int ui(10);
    ss << dogen::needle::core::io::jsonify(ui);
    std::string expected("10");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const int i(-11);
    ss << dogen::needle::core::io::jsonify(i);
    expected = "-11";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const unsigned short us(12);
    ss << dogen::needle::core::io::jsonify(us);
    expected = "12";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const short s(-13);
    ss << dogen::needle::core::io::jsonify(s);
    expected = "-13";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const unsigned long ul(14);
    ss << dogen::needle::core::io::jsonify(ul);
    expected = "14";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const short l(-15);
    ss << dogen::needle::core::io::jsonify(l);
    expected = "-15";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");
}

BOOST_AUTO_TEST_CASE(jsonification_of_floating_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_floating_produces_expected_result");

    std::ostringstream ss;
    std::string expected = "0.000001";
    const double d(0.000001);
    ss << dogen::needle::core::io::jsonify(d);
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const float f(0.000002);
    ss << dogen::needle::core::io::jsonify(f);
    expected = "0.000002";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");
}

BOOST_AUTO_TEST_CASE(jsonification_of_bool_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_bool_produces_expected_result");

    std::ostringstream ss;
    bool b(true);
    ss << dogen::needle::core::io::jsonify(b);
    std::string expected("true");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    b = false;
    ss << dogen::needle::core::io::jsonify(b);
    expected = "false";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");
}

BOOST_AUTO_TEST_CASE(jsonification_of_string_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_string_produces_expected_result");

    std::ostringstream ss;
    std::string s("my_string");
    ss << dogen::needle::core::io::jsonify(s);
    std::string expected("\"my_string\"");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    s = "my_string with quote \" and new line \n";
    ss << dogen::needle::core::io::jsonify(s);
    expected = "\"my_string with quote <quote> and new line <new_line>\"";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");
}

BOOST_AUTO_TEST_CASE(jsonification_of_complex_type_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_complex_type_expected_result");

    std::ostringstream ss;
    const test_object to("some string", 123);
    ss << dogen::needle::core::io::jsonify(to);
    std::string expected("{ \"s\": \"some string\", \"i\": 123 }");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");
}

BOOST_AUTO_TEST_CASE(jsonification_of_array_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_array_produces_expected_result");

    const std::array<unsigned int, 3> aui = {{ 1, 2, 3 }};
    std::ostringstream ss;
    ss << aui;
    std::string expected("[ 1, 2, 3 ]");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const std::array<bool, 2> aub = {{ true, false }};
    ss << aub;
    expected = "[ true, false ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const test_object to("some string", 123);
    const std::array<test_object, 2> ato = {{ to, to }};
    ss << ato;
    expected = "[ { \"s\": \"some string\", \"i\": 123 }, "
        "{ \"s\": \"some string\", \"i\": 123 } ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");
}

BOOST_AUTO_TEST_SUITE_END()
