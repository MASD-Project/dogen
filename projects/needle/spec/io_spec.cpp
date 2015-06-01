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
#include <functional>
#include <boost/make_shared.hpp>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/needle/core/io/jsonify.hpp"
#include "dogen/needle/std/io/array_io.hpp"
#include "dogen/needle/std/io/forward_list_io.hpp"
#include "dogen/needle/std/io/list_io.hpp"
#include "dogen/needle/std/io/pair_io.hpp"
#include "dogen/needle/std/io/string_io.hpp"
#include "dogen/needle/std/io/map_io.hpp"
#include "dogen/needle/std/io/unordered_map_io.hpp"
#include "dogen/needle/std/io/set_io.hpp"
#include "dogen/needle/std/io/unordered_set_io.hpp"
#include "dogen/needle/std/io/vector_io.hpp"
#include "dogen/needle/std/io/deque_io.hpp"
#include "dogen/needle/std/io/memory_io.hpp"
#include "dogen/needle/boost/io/optional_io.hpp"
#include "dogen/needle/boost/io/shared_ptr_io.hpp"
#include "dogen/needle/boost/io/variant_io.hpp"
#include "dogen/needle/boost/io/gregorian_date_io.hpp"
#include "dogen/needle/boost/io/posix_time_io.hpp"
#include "dogen/needle/boost/io/path_io.hpp"
#include "dogen/needle/boost/io/ptree_io.hpp"
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
    using dogen::needle::core::io::constants;
    s << constants::open_object()
      << "\"s\": " << jsonify(to.s) << constants::separator()
      << "\"i\": " << jsonify(to.i)
      << constants::close_object();
    return(s);
}

inline dogen::needle::core::io::detail::no_op_formatting<const test_object>
jsonify(const test_object& v) {
    return dogen::needle::core::io::detail::
        no_op_formatting<const test_object>(v);
}

bool operator<(const test_object& lhs, const test_object& rhs) {
    return lhs.i < rhs.i;
}

bool operator==(const test_object& lhs, const test_object& rhs) {
    return lhs.i == rhs.i;
}

}

namespace std {

template<>
struct hash<test_object> {
public:
    size_t operator()(const test_object& v) const {
        return v.i;
    }
};

}

using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(io)

BOOST_AUTO_TEST_CASE(jsonification_of_integers_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_integers_produces_expected_result");

    std::ostringstream ss;
    const unsigned int i0(10);
    ss << jsonify(i0);
    std::string expected("10");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const int i1(-11);
    ss << jsonify(i1);
    expected = "-11";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const unsigned short i2(12);
    ss << jsonify(i2);
    expected = "12";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const short i3(-13);
    ss << jsonify(i3);
    expected = "-13";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const unsigned long i4(14);
    ss << jsonify(i4);
    expected = "14";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const short i5(-15);
    ss << jsonify(i5);
    expected = "-15";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
}

BOOST_AUTO_TEST_CASE(jsonification_of_floating_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_floating_produces_expected_result");

    std::ostringstream ss;
    const double i0(0.000001);
    ss << jsonify(i0);
    std::string expected("0.000001");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const float i1(0.000002);
    ss << jsonify(i1);
    expected = "0.000002";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
}

BOOST_AUTO_TEST_CASE(jsonification_of_char_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_char_produces_expected_result");

    std::ostringstream ss;
    const char i0(32);
    ss << jsonify(i0);
    std::string expected("\"0x20\"");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const char i1(0);
    ss << jsonify(i1);
    expected = "\"0x00\"";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
}

BOOST_AUTO_TEST_CASE(jsonification_of_bool_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_bool_produces_expected_result");

    std::ostringstream ss;
    const bool i0(true);
    ss << jsonify(i0);
    std::string expected("true");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const bool i1(false);
    ss << jsonify(i1);
    expected = "false";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
}

BOOST_AUTO_TEST_CASE(jsonification_of_string_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_string_produces_expected_result");

    std::ostringstream ss;
    const std::string i0("my_string");
    ss << jsonify(i0);
    std::string expected("\"my_string\"");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const std::string i1("my_string with quote \" and new line \n");
    ss << jsonify(i1);
    expected = "\"my_string with quote <quote> and new line <new_line>\"";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
}

BOOST_AUTO_TEST_CASE(jsonification_of_complex_type_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_complex_type_expected_result");

    std::ostringstream ss;
    const test_object i0("some string", 123);
    ss << jsonify(i0);
    std::string expected("{ \"s\": \"some string\", \"i\": 123 }");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
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

    const test_object to("some \" string", 123);
    const std::array<test_object, 2> i2 = {{ to, to }};
    ss << i2;
    expected = "[ { \"s\": \"some <quote> string\", \"i\": 123 }, "
        "{ \"s\": \"some <quote> string\", \"i\": 123 } ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
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

    const test_object to("some \" string", 123);
    const std::forward_list<test_object> i2 = {{ to, to }};
    ss << i2;
    expected = "[ { \"s\": \"some <quote> string\", \"i\": 123 }, "
        "{ \"s\": \"some <quote> string\", \"i\": 123 } ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
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

    const test_object to("some \" string", 123);
    const std::list<test_object> i2 = {{ to, to }};
    ss << i2;
    expected = "[ { \"s\": \"some <quote> string\", \"i\": 123 }, "
        "{ \"s\": \"some <quote> string\", \"i\": 123 } ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
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

    const test_object to("some \" string", 123);
    const std::pair<unsigned int, test_object> i2 = { 1, to };
    ss << i2;
    expected = "{ \"key\": 1, \"value\": { \"s\": "
        "\"some <quote> string\", \"i\": 123 } }";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
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

    const test_object to("some \" string", 123);
    const std::map<unsigned int, test_object> i2 = { {1, to} };
    ss << i2;
    expected = "[ { \"key\": 1, \"value\": { \"s\": "
        "\"some <quote> string\", \"i\": 123 } } ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
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

    const test_object to("some \" string", 123);
    const std::unordered_map<unsigned int, test_object> i2 = { {1, to} };
    ss << i2;
    expected = "[ { \"key\": 1, \"value\": { \"s\": "
        "\"some <quote> string\", \"i\": 123 } } ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
}

BOOST_AUTO_TEST_CASE(jsonification_of_set_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_set_produces_expected_result");

    std::ostringstream ss;
    const std::set<unsigned int> i0 = { 1, 2 };
    ss << i0;
    std::string expected("[ 1, 2 ]");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const std::set<bool> i1 = { false, true };
    ss << i1;
    expected = "[ false, true ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const std::string s("some \" string");
    const std::set<std::string> i2 = { s };
    ss << i2;
    expected = "[ \"some <quote> string\" ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const test_object to("some string", 123);
    const std::set<test_object> i3 = { to };
    ss << i3;
    expected = "[ { \"s\": \"some string\", \"i\": 123 } ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
}

BOOST_AUTO_TEST_CASE(jsonification_of_unordered_set_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_unordered_set_produces_expected_result");

    std::ostringstream ss;
    const std::unordered_set<unsigned int> i0 = { 1 };
    ss << i0;
    std::string expected("[ 1 ]");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const std::unordered_set<bool> i1 = { false };
    ss << i1;
    expected = "[ false ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const std::string s("some \" string");
    const std::unordered_set<std::string> i2 = { s };
    ss << i2;
    expected = "[ \"some <quote> string\" ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const test_object to("some string", 123);
    const std::unordered_set<test_object> i3 = { to };
    ss << i3;
    expected = "[ { \"s\": \"some string\", \"i\": 123 } ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
}

BOOST_AUTO_TEST_CASE(jsonification_of_vector_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_vector_produces_expected_result");

    std::ostringstream ss;
    const std::vector<unsigned int> i0 = { 1 };
    ss << i0;
    std::string expected("[ 1 ]");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const std::vector<bool> i1 = { false };
    ss << i1;
    expected = "[ false ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const std::string s("some \" string");
    const std::vector<std::string> i2 = { s };
    ss << i2;
    expected = "[ \"some <quote> string\" ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const test_object to("some string", 123);
    const std::vector<test_object> i3 = { to };
    ss << i3;
    expected = "[ { \"s\": \"some string\", \"i\": 123 } ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
}

BOOST_AUTO_TEST_CASE(jsonification_of_deque_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_deque_produces_expected_result");

    std::ostringstream ss;
    const std::deque<unsigned int> i0 = { 1 };
    ss << i0;
    std::string expected("[ 1 ]");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const std::deque<bool> i1 = { false };
    ss << i1;
    expected = "[ false ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const std::string s("some \" string");
    const std::deque<std::string> i2 = { s };
    ss << i2;
    expected = "[ \"some <quote> string\" ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const test_object to("some string", 123);
    const std::deque<test_object> i3 = { to };
    ss << i3;
    expected = "[ { \"s\": \"some string\", \"i\": 123 } ]";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
}
/*
BOOST_AUTO_TEST_CASE_IGNORE(jsonification_of_std_shared_pointer_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_std_shared_pointer_produces_expected_result");

    std::ostringstream ss;
    const auto i0(std::make_shared<int>(1234));
    ss << i0;
    std::string expected("1234");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const auto i1(std::make_shared<test_object>("abc", 123));
    ss << i1;
    expected = "{ \"s\": \"abc\", \"i\": 123 }";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const std::shared_ptr<int> i2;
    ss << i2;
    expected = "\"shared_ptr\": \"empty shared pointer\"";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
}

BOOST_AUTO_TEST_CASE_IGNORE(jsonification_of_boost_optional_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_boost_optional_produces_expected_result");

    std::ostringstream ss;
    const boost::optional<unsigned int> i0(1234);
    ss << i0;
    std::string expected("1234");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const boost::optional<unsigned int> i1;
    ss << i1;
    expected = "\"optional\" : \"empty\"";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
}

BOOST_AUTO_TEST_CASE_IGNORE(jsonification_of_boost_shared_pointer_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_boost_shared_pointer_produces_expected_result");

    std::ostringstream ss;
    const auto i0(boost::make_shared<int>(1234));
    ss << i0;
    std::string expected("1234");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const auto i1(boost::make_shared<test_object>("abc", 123));
    ss << i1;
    expected = "{ \"s\": \"abc\", \"i\": 123 }";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const boost::shared_ptr<int> i2;
    ss << i2;
    expected = "\"shared_ptr\": \"empty shared pointer\"";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
}

BOOST_AUTO_TEST_CASE_IGNORE(jsonification_of_boost_variant_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_boost_variant_produces_expected_result");

    std::ostringstream ss;
    const boost::variant<unsigned int, std::string> i0 = "10";
    ss << jsonify(i0);
    std::string expected("{ \"__type__\": \"boost::variant\", "
        "\"data\": \"10\" }");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    const boost::variant<unsigned int, std::string> i1 = 15;
    ss << jsonify(i1);
    expected = "{ \"__type__\": \"boost::variant\", \"data\": 15 }";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
}

BOOST_AUTO_TEST_CASE_IGNORE(jsonification_of_boost_gregorian_date_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_boost_gregorian_date_produces_expected_result");

    std::ostringstream ss;
    const boost::gregorian::date i0(2002, 2, 15);
    ss << jsonify(i0);
    std::string expected("\"2002-Feb-15\"");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");
}

BOOST_AUTO_TEST_CASE_IGNORE(jsonification_of_boost_posix_time_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_posix_time_date_produces_expected_result");

    std::ostringstream ss;
    const boost::posix_time::time_duration i0(1,2,3);
    ss << jsonify(i0);
    std::string expected("\"01:02:03\"");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    boost::gregorian::date d(2002, 2, 15);
    boost::posix_time::ptime i1(d, i0);
    ss << jsonify(i1);
    expected = "\"2002-Feb-15 01:02:03\"";
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
}

BOOST_AUTO_TEST_CASE_IGNORE(jsonification_of_boost_filesystem_path_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_filesystem_path_produces_expected_result");

    std::ostringstream ss;
    const boost::filesystem::path i0("/a/b/c");
    ss << jsonify(i0);
    std::string expected("\"/a/b/c\"");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");

    // FIXME: backslashes are not being converted for some reason.
    // const boost::filesystem::path i1("\\a\\b\\c");
    // ss << jsonify(i1);
    // BOOST_CHECK(asserter::assert_object(expected, ss.str()));
}

BOOST_AUTO_TEST_CASE_IGNORE(jsonification_of_boost_ptree_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("jsonification_of_ptree_produces_expected_result");

    std::ostringstream ss;
    using boost::property_tree::ptree;
    ptree c;
    c.put("key_2", 0);
    ptree i0;
    i0.push_back(ptree::value_type("key_1", c));

    ss << jsonify(i0);
    std::string expected("{    \"key_1\":    {        \"key_2\": \"0\"    }}");
    BOOST_CHECK(asserter::assert_object(expected, ss.str()));
    ss.str("");
}
*/
BOOST_AUTO_TEST_SUITE_END()
