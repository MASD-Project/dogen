/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include "masd.dogen.extraction/types/indent_filter.hpp"
#include "masd.dogen.utility/test/asserter.hpp"
#include "masd.dogen.utility/test/logging.hpp"
#include "masd.dogen.utility/io/list_io.hpp"
#include "masd.dogen.utility/io/unordered_map_io.hpp"
#include "masd.dogen.extraction/types/cpp/namespace_formatter.hpp"

namespace {

const std::string test_module("masd.dogen.extraction.tests");
const std::string test_suite("namespace_formatter_tests");
const std::string empty;

const std::string single_end("}");
const std::string single_end_new_line(R"(}
)");

const std::string multiple_end("} } }");
const std::string multiple_end_new_line(R"(} } }
)");

const std::string single_namespace("aaa");
const std::list<std::string> multiple_namespaces({"aaa", "bbb", "ccc"});

const std::string
single_namespace_default_configuration_begin(R"(namespace aaa {
)");

const std::string
multiple_namespaces_default_configuration_begin(R"(namespace aaa {
namespace bbb {
namespace ccc {
)");

const std::string
multiple_namespaces_nested_configuration_begin(R"(namespace aaa::bbb::ccc {
)");

const std::string empty_namespace_default_configuration_begin(R"(namespace {
)");

}

using namespace masd::dogen::utility::test;
using masd::dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(namespace_formatter_tests)

BOOST_AUTO_TEST_CASE(single_namespace_with_default_configuration_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("single_namespace_with_default_configuration_generates_expected_cpp_namespaces");

    BOOST_LOG_SEV(lg, debug) << "Input: " << single_namespace;

    std::ostringstream s;
    masd::dogen::extraction::cpp::namespace_formatter nsf;
    nsf.format_begin(s, single_namespace);
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(
            single_namespace_default_configuration_begin, beg));
    s.str("");

    nsf.format_end(s, single_namespace);
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(single_end, end));
}

BOOST_AUTO_TEST_CASE(multiple_namespaces_with_default_configuration_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("multiple_namespaces_with_default_configuration_generates_expected_cpp_namespaces");

    BOOST_LOG_SEV(lg, debug) << "Input: " << multiple_namespaces;

    std::ostringstream s;
    masd::dogen::extraction::cpp::namespace_formatter nsf;
    nsf.format_begin(s, multiple_namespaces);
    const auto beg(s.str());

    BOOST_CHECK(asserter::assert_equals_marker(
            multiple_namespaces_default_configuration_begin, beg));
    s.str("");

    nsf.format_end(s, multiple_namespaces);
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(multiple_end, end));
}

BOOST_AUTO_TEST_CASE(empy_namespace_with_default_configuration_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("empty_namespace_with_default_configuration_generates_expected_cpp_namespaces");

    std::ostringstream s;
    using masd::dogen::extraction::cpp::namespace_formatter;
    namespace_formatter nsf(true/*anonymous_namespace*/);
    nsf.format_begin(s, empty);
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(
            empty_namespace_default_configuration_begin, beg));
    s.str("");

    nsf.format_end(s, empty);
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(single_end, end));
}

BOOST_AUTO_TEST_CASE(empy_namespaces_with_default_configuration_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("empty_namespaces_with_default_configuration_generates_expected_cpp_namespaces");

    std::ostringstream s;
    using masd::dogen::extraction::cpp::namespace_formatter;
    namespace_formatter nsf(true/*anonymous_namespace*/);

    const std::list<std::string> empty_list;
    nsf.format_begin(s, empty_list);
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(
            empty_namespace_default_configuration_begin, beg));
    s.str("");

    nsf.format_end(s, empty);
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(single_end, end));
}

BOOST_AUTO_TEST_CASE(empy_namespace_with_anonymous_namespaces_off_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("empty_namespace_with_anonymous_namespaces_off_generates_expected_cpp_namespaces");

    std::ostringstream s;
    using masd::dogen::extraction::cpp::namespace_formatter;
    namespace_formatter nsf(false/*anonymous_namespace*/);
    nsf.format_begin(s, empty);
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(empty, beg));
    s.str("");

    nsf.format_end(s, empty);
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(empty, end));
}

BOOST_AUTO_TEST_CASE(empy_namespaces_with_anonymous_namespaces_off_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("empty_namespaces_with_anonymous_namespaces_off_generates_expected_cpp_namespaces");

    std::ostringstream s;
    using masd::dogen::extraction::cpp::namespace_formatter;
    namespace_formatter nsf(false/*anonymous_namespace*/);

    const std::list<std::string> empty_list;
    nsf.format_begin(s, empty_list);
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(empty, beg));
    s.str("");

    nsf.format_end(s, empty);
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(empty, end));
}

BOOST_AUTO_TEST_CASE(empy_namespace_with_new_line_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("empty_namespace_with_new_line_generates_expected_cpp_namespaces");

    std::ostringstream s;
    using masd::dogen::extraction::cpp::namespace_formatter;
    namespace_formatter nsf(true/*anonymous_namespace*/, true/*add_new_line*/);
    nsf.format_begin(s, empty);
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(
            empty_namespace_default_configuration_begin, beg));
    s.str("");

    nsf.format_end(s, empty);
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(single_end_new_line, end));
}

BOOST_AUTO_TEST_CASE(empy_namespaces_with_new_line_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("empty_namespaces_with_new_line_generates_expected_cpp_namespaces");

    std::ostringstream s;
    using masd::dogen::extraction::cpp::namespace_formatter;
    namespace_formatter nsf(true/*anonymous_namespace*/, true/*add_new_line*/);

    const std::list<std::string> empty_list;
    nsf.format_begin(s, empty_list);
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(
            empty_namespace_default_configuration_begin, beg));
    s.str("");

    nsf.format_end(s, empty);
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(single_end_new_line, end));
}

BOOST_AUTO_TEST_CASE(single_namespace_with_new_line_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("single_namespace_with_new_line_generates_expected_cpp_namespaces");

    BOOST_LOG_SEV(lg, debug) << "Input: " << single_namespace;

    std::ostringstream s;
    using masd::dogen::extraction::cpp::namespace_formatter;
    namespace_formatter nsf(true/*anonymous_namespace*/, true/*add_new_line*/);
    nsf.format_begin(s, single_namespace);
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(
            single_namespace_default_configuration_begin, beg));
    s.str("");

    nsf.format_end(s, single_namespace);
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(single_end_new_line, end));
}

BOOST_AUTO_TEST_CASE(multiple_namespaces_with_new_line_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("multiple_namespaces_with_new_line_generates_expected_cpp_namespaces");

    BOOST_LOG_SEV(lg, debug) << "Input: " << multiple_namespaces;

    std::ostringstream s;
    using masd::dogen::extraction::cpp::namespace_formatter;

    namespace_formatter nsf(true/*anonymous_namespace*/, true/*add_new_line*/);
    nsf.format_begin(s, multiple_namespaces);
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(
            multiple_namespaces_default_configuration_begin, beg));
    s.str("");

    nsf.format_end(s, multiple_namespaces);
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(multiple_end_new_line, end));
}

BOOST_AUTO_TEST_CASE(single_namespace_with_nested_namespaces_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("single_namespace_with_nested_namespaces_generates_expected_cpp_namespaces");

    BOOST_LOG_SEV(lg, debug) << "Input: " << single_namespace;

    std::ostringstream s;
    using masd::dogen::extraction::cpp::namespace_formatter;
    namespace_formatter nsf(true/*anonymous_namespace*/, false/*add_new_line*/,
        true/*nested_namespaces*/);
    nsf.format_begin(s, single_namespace);
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(
            single_namespace_default_configuration_begin, beg));
    s.str("");

    nsf.format_end(s, single_namespace);
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(single_end, end));
}

BOOST_AUTO_TEST_CASE(multiple_namespaces_with_nested_namespaces_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("multiple_namespaces_with_nested_namespaces_generates_expected_cpp_namespaces");

    BOOST_LOG_SEV(lg, debug) << "Input: " << multiple_namespaces;

    std::ostringstream s;
    using masd::dogen::extraction::cpp::namespace_formatter;
    namespace_formatter nsf(true/*anonymous_namespace*/, false/*add_new_line*/,
        true/*nested_namespaces*/);
    nsf.format_begin(s, multiple_namespaces);
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(
            multiple_namespaces_nested_configuration_begin, beg));
    s.str("");

    nsf.format_end(s, multiple_namespaces);
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_marker(single_end, end));
}

BOOST_AUTO_TEST_SUITE_END()
