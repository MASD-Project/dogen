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
#include "dogen.utility/types/test/asserter.hpp"
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.generation/types/formatters/indent_filter.hpp"
#include "dogen.generation/types/formatters/namespace_formatter.hpp"

namespace {

const std::string test_module("dogen.generation.tests");
const std::string test_suite("namespace_formatter_tests");
const std::string empty;

const std::string single_end("}");
const std::string single_end_new_line(R"(}
)");

const std::string multiple_end("} } }");
const std::string multiple_end_new_line(R"(} } }
)");

const std::string single_namespace("aaa");
const std::list<std::string> multiple_namespaces_cpp({"aaa", "bbb", "ccc"});

const std::string
single_namespace_cpp_default_configuration_begin(R"(namespace aaa {
)");

const std::string
multiple_namespaces_cpp_default_configuration_begin(R"(namespace aaa {
namespace bbb {
namespace ccc {
)");

const std::string
single_namespace_csharp_default_configuration_begin(R"(namespace aaa
{
)");

const std::string
multiple_namespaces_csharp_default_configuration_begin(R"(namespace aaa.bbb.ccc
{
)");

const std::string
multiple_namespaces_cpp_nested_configuration_begin(R"(namespace aaa::bbb::ccc {
)");

const std::string empty_namespace_default_configuration_begin(R"(namespace {
)");

const auto cpp_ts(dogen::logical::meta_model::technical_space::cpp);
const auto csharp_ts(dogen::logical::meta_model::technical_space::csharp);
const std::list<std::string> empty_namespaces;
}

using namespace dogen::utility::test;
using dogen::utility::test::asserter;
using dogen::generation::formatters::namespace_formatter;

BOOST_AUTO_TEST_SUITE(namespace_formatter_tests)

BOOST_AUTO_TEST_CASE(single_namespace_with_default_configuration_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("single_namespace_with_default_configuration_generates_expected_cpp_namespaces");

    std::ostringstream s;
    namespace_formatter f(s, cpp_ts, single_namespace);
    f.format_begin();
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_string(
            single_namespace_cpp_default_configuration_begin, beg));
    s.str("");

    f.format_end();
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_string(single_end, end));
}

BOOST_AUTO_TEST_CASE(multiple_namespaces_with_default_configuration_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("multiple_namespaces_with_default_configuration_generates_expected_cpp_namespaces");

    std::ostringstream s;
    namespace_formatter f(s, cpp_ts, multiple_namespaces_cpp);
    f.format_begin();
    const auto beg(s.str());

    BOOST_CHECK(asserter::assert_equals_string(
            multiple_namespaces_cpp_default_configuration_begin, beg));
    s.str("");

    f.format_end();
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_string(multiple_end, end));
}

BOOST_AUTO_TEST_CASE(empy_namespace_with_default_configuration_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("empty_namespace_with_default_configuration_generates_expected_cpp_namespaces");

    std::ostringstream s;
    namespace_formatter f(s, cpp_ts, empty);
    f.format_begin();
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_string(
            empty_namespace_default_configuration_begin, beg));
    s.str("");

    f.format_end();
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_string(single_end, end));
}

BOOST_AUTO_TEST_CASE(empy_namespaces_with_default_configuration_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("empty_namespaces_with_default_configuration_generates_expected_cpp_namespaces");

    std::ostringstream s;
    namespace_formatter f(s, cpp_ts, empty_namespaces);

    f.format_begin();
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_string(
            empty_namespace_default_configuration_begin, beg));
    s.str("");

    f.format_end();
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_string(single_end, end));
}

BOOST_AUTO_TEST_CASE(empy_namespace_with_new_line_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("empty_namespace_with_new_line_generates_expected_cpp_namespaces");

    std::ostringstream s;
    namespace_formatter f(s, cpp_ts, empty, true/*add_new_line*/);
    f.format_begin();
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_string(
            empty_namespace_default_configuration_begin, beg));
    s.str("");

    f.format_end();
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_string(single_end_new_line, end));
}

BOOST_AUTO_TEST_CASE(empy_namespaces_with_new_line_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("empty_namespaces_with_new_line_generates_expected_cpp_namespaces");

    std::ostringstream s;
    namespace_formatter f(s, cpp_ts, empty_namespaces, true/*add_new_line*/);

    f.format_begin();
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_string(
            empty_namespace_default_configuration_begin, beg));
    s.str("");

    f.format_end();
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_string(single_end_new_line, end));
}

BOOST_AUTO_TEST_CASE(single_namespace_with_new_line_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("single_namespace_with_new_line_generates_expected_cpp_namespaces");

    std::ostringstream s;
    namespace_formatter f(s, cpp_ts, single_namespace, true/*add_new_line*/);
    f.format_begin();
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_string(
            single_namespace_cpp_default_configuration_begin, beg));
    s.str("");

    f.format_end();
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_string(single_end_new_line, end));
}

BOOST_AUTO_TEST_CASE(multiple_namespaces_with_new_line_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("multiple_namespaces_with_new_line_generates_expected_cpp_namespaces");

    std::ostringstream s;
    namespace_formatter f(s, cpp_ts, multiple_namespaces_cpp,
        true/*add_new_line*/);
    f.format_begin();
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_string(
            multiple_namespaces_cpp_default_configuration_begin, beg));
    s.str("");

    f.format_end();
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_string(multiple_end_new_line, end));
}

BOOST_AUTO_TEST_CASE(single_namespace_with_new_line_generates_expected_csharp_namespaces) {
    SETUP_TEST_LOG_SOURCE("single_namespace_with_new_line_generates_expected_csharp_namespaces");

    std::ostringstream s;
    namespace_formatter f(s, csharp_ts, single_namespace, true/*add_new_line*/);
    f.format_begin();
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_string(
            single_namespace_csharp_default_configuration_begin, beg));
    s.str("");

    f.format_end();
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_string(single_end_new_line, end));
}

BOOST_AUTO_TEST_CASE(multiple_namespaces_with_new_line_generates_expected_csharp_namespaces) {
    SETUP_TEST_LOG_SOURCE("multiple_namespaces_with_new_line_generates_expected_csharp_namespaces");

    std::ostringstream s;
    namespace_formatter f(s, csharp_ts, multiple_namespaces_cpp,
        true/*add_new_line*/);
    f.format_begin();
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_string(
            multiple_namespaces_csharp_default_configuration_begin, beg));
    s.str("");

    f.format_end();
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_string(single_end_new_line, end));
}

BOOST_AUTO_TEST_CASE(single_namespace_with_nested_namespaces_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("single_namespace_with_nested_namespaces_generates_expected_cpp_namespaces");

    std::ostringstream s;
    namespace_formatter f(s, cpp_ts, single_namespace, false/*add_new_line*/,
        true/*use_nesting*/);
    f.format_begin();
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_string(
            single_namespace_cpp_default_configuration_begin, beg));
    s.str("");

    f.format_end();
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_string(single_end, end));
}

BOOST_AUTO_TEST_CASE(multiple_namespaces_with_nested_namespaces_generates_expected_cpp_namespaces) {
    SETUP_TEST_LOG_SOURCE("multiple_namespaces_with_nested_namespaces_generates_expected_cpp_namespaces");

    std::ostringstream s;
    namespace_formatter f(s, cpp_ts, multiple_namespaces_cpp, false/*add_new_line*/,
        true/*use_nesting*/);
    f.format_begin();
    const auto beg(s.str());
    BOOST_CHECK(asserter::assert_equals_string(
            multiple_namespaces_cpp_nested_configuration_begin, beg));
    s.str("");

    f.format_end();
    const auto end(s.str());
    BOOST_CHECK(asserter::assert_equals_string(single_end, end));
}

BOOST_AUTO_TEST_SUITE_END()
