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
#include "dogen/needle/std/io/forward_list_io.hpp"
#include "dogen/needle/std/io/list_io.hpp"
#include "dogen/needle/std/io/pair_io.hpp"
#include "dogen/needle/std/io/map_io.hpp"
#include "dogen/needle/std/io/unordered_map_io.hpp"
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
    const unsigned int i0(10);
    ss << dogen::needle::core::io::jsonify(i0);
    std::string expected("10");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const int i1(-11);
    ss << dogen::needle::core::io::jsonify(i1);
    expected = "-11";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const unsigned short i2(12);
    ss << dogen::needle::core::io::jsonify(i2);
    expected = "12";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const short i3(-13);
    ss << dogen::needle::core::io::jsonify(i3);
    expected = "-13";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const unsigned long i4(14);
    ss << dogen::needle::core::io::jsonify(i4);
    expected = "14";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const short i5(-15);
    ss << dogen::needle::core::io::jsonify(i5);
    expected = "-15";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");
}

BOOST_AUTO_TEST_CASE(jsonification_of_floating_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_floating_produces_expected_result");

    std::ostringstream ss;
    const double i0(0.000001);
    ss << dogen::needle::core::io::jsonify(i0);
    std::string expected = "0.000001";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const float i1(0.000002);
    ss << dogen::needle::core::io::jsonify(i1);
    expected = "0.000002";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");
}

BOOST_AUTO_TEST_CASE(jsonification_of_bool_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_bool_produces_expected_result");

    std::ostringstream ss;
    const bool i0(true);
    ss << dogen::needle::core::io::jsonify(i0);
    std::string expected("true");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const bool i1(false);
    ss << dogen::needle::core::io::jsonify(i1);
    expected = "false";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");
}

BOOST_AUTO_TEST_CASE(jsonification_of_string_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_string_produces_expected_result");

    std::ostringstream ss;
    const std::string i0("my_string");
    ss << dogen::needle::core::io::jsonify(i0);
    std::string expected("\"my_string\"");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const std::string i1("my_string with quote \" and new line \n");
    ss << dogen::needle::core::io::jsonify(i1);
    expected = "\"my_string with quote <quote> and new line <new_line>\"";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");
}

BOOST_AUTO_TEST_CASE(jsonification_of_complex_type_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_complex_type_expected_result");

    std::ostringstream ss;
    const test_object i0("some string", 123);
    ss << dogen::needle::core::io::jsonify(i0);
    std::string expected("{ \"s\": \"some string\", \"i\": 123 }");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");
}

BOOST_AUTO_TEST_CASE(jsonification_of_array_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_array_produces_expected_result");

    std::ostringstream ss;
    const std::array<unsigned int, 3> i0 = {{ 1, 2, 3 }};
    ss << i0;
    std::string expected("[ 1, 2, 3 ]");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const std::array<bool, 2> i1 = {{ true, false }};
    ss << i1;
    expected = "[ true, false ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const test_object to("some string", 123);
    const std::array<test_object, 2> i2 = {{ to, to }};
    ss << i2;
    expected = "[ { \"s\": \"some string\", \"i\": 123 }, "
        "{ \"s\": \"some string\", \"i\": 123 } ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");
}

BOOST_AUTO_TEST_CASE(jsonification_of_forward_list_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_forward_list_produces_expected_result");

    std::ostringstream ss;
    const std::forward_list<unsigned int> i0 = { 1, 2, 3 };
    ss << i0;
    std::string expected("[ 1, 2, 3 ]");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const std::forward_list<bool> i1 = { true, false };
    ss << i1;
    expected = "[ true, false ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const test_object to("some string", 123);
    const std::forward_list<test_object> i2 = {{ to, to }};
    ss << i2;
    expected = "[ { \"s\": \"some string\", \"i\": 123 }, "
        "{ \"s\": \"some string\", \"i\": 123 } ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");
}

BOOST_AUTO_TEST_CASE(jsonification_of_list_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_list_produces_expected_result");

    const std::list<unsigned int> i0 = { 1, 2, 3 };
    std::ostringstream ss;
    ss << i0;
    std::string expected("[ 1, 2, 3 ]");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const std::list<bool> i1 = { true, false };
    ss << i1;
    expected = "[ true, false ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const test_object to("some string", 123);
    const std::list<test_object> i2 = {{ to, to }};
    ss << i2;
    expected = "[ { \"s\": \"some string\", \"i\": 123 }, "
        "{ \"s\": \"some string\", \"i\": 123 } ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");
}

BOOST_AUTO_TEST_CASE(jsonification_of_pair_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_pair_produces_expected_result");

    std::ostringstream ss;
    const std::pair<unsigned int, unsigned int> i0 = { 1, 2 };
    ss << i0;
    std::string expected("{ \"key\": 1, \"value\": 2 }");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const std::pair<unsigned int, bool> i1 = { 1, false };
    ss << i1;
    expected = "{ \"key\": 1, \"value\": false }";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const test_object to("some string", 123);
    const std::pair<unsigned int, test_object> i2 = { 1, to };
    ss << i2;
    expected = "{ \"key\": 1, \"value\": { \"s\": "
        "\"some string\", \"i\": 123 } }";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");
}

BOOST_AUTO_TEST_CASE(jsonification_of_map_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_map_produces_expected_result");

    std::ostringstream ss;
    const std::map<unsigned int, unsigned int> i0 = { {1, 2} };
    ss << i0;
    std::string expected("[ { \"key\": 1, \"value\": 2 } ]");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const std::map<unsigned int, bool> i1 = { {1, false} };
    ss << i1;
    expected = "[ { \"key\": 1, \"value\": false } ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const test_object to("some string", 123);
    const std::map<unsigned int, test_object> i2 = { {1, to} };
    ss << i2;
    expected = "[ { \"key\": 1, \"value\": { \"s\": "
        "\"some string\", \"i\": 123 } } ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");
}

BOOST_AUTO_TEST_CASE(jsonification_of_unordered_map_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_unordered_map_produces_expected_result");

    std::ostringstream ss;
    const std::unordered_map<unsigned int, unsigned int> i0 = { {1, 2} };
    ss << i0;
    std::string expected("[ { \"key\": 1, \"value\": 2 } ]");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const std::unordered_map<unsigned int, bool> i1 = { {1, false} };
    ss << i1;
    expected = "[ { \"key\": 1, \"value\": false } ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const test_object to("some string", 123);
    const std::unordered_map<unsigned int, test_object> i2 = { {1, to} };
    ss << i2;
    expected = "[ { \"key\": 1, \"value\": { \"s\": "
        "\"some string\", \"i\": 123 } } ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");
}

BOOST_AUTO_TEST_SUITE_END()
