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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/formatters/io/file_io.hpp"
#include "dogen/stitch/test/mock_text_template_factory.hpp"
#include "dogen/stitch/io/text_template_io.hpp"
#include "dogen/stitch/types/formatting_error.hpp"
#include "dogen/stitch/types/formatter.hpp"

namespace {

const std::string empty;

const std::string test_module("stitch");
const std::string test_suite("formatter_tests");

const std::string single_text_line_content(
    R"(stream_ << "This is line numnber: 0" << std::endl;
)");

const std::string multiple_text_lines_content(
    R"(stream_ << "This is line numnber: 0" << std::endl;
stream_ << "This is line numnber: 1" << std::endl;
)");

const std::string single_expression_block_line(R"(stream_ << some_function() << std::endl;
)");

const std::string multiple_expression_block_lines(R"(stream_ << some_function() + i0 << std::endl;
stream_ << some_function() + i1 << std::endl;
)");

const std::string single_standard_control_block_line(R"(unsigned int i0;
)");

const std::string multiple_standard_control_block_lines(R"(unsigned int i0;
unsigned int i1;
)");

const std::string text_expression_text_single_line(R"(stream_ << "This is line numnber: 0" << std::endl;
stream_ << some_function() << std::endl;
stream_ << "This is line numnber: 0" << std::endl;
)");

const std::string expression_text_expression_single_line(R"(stream_ << some_function() << std::endl;
stream_ << "This is line numnber: 0" << std::endl;
stream_ << some_function() << std::endl;
)");

const std::string text_expression_text_multi_line(R"(stream_ << "This is line numnber: 0" << std::endl;
stream_ << "This is line numnber: 1" << std::endl;
stream_ << some_function() + i0 << std::endl;
stream_ << some_function() + i1 << std::endl;
stream_ << "This is line numnber: 0" << std::endl;
stream_ << "This is line numnber: 1" << std::endl;
)");

const std::string expression_text_expression_multi_line(R"(stream_ << some_function() + i0 << std::endl;
stream_ << some_function() + i1 << std::endl;
stream_ << "This is line numnber: 0" << std::endl;
stream_ << "This is line numnber: 1" << std::endl;
stream_ << some_function() + i0 << std::endl;
stream_ << some_function() + i1 << std::endl;
)");

const std::string text_standard_control_text_single_line(R"(stream_ << "This is line numnber: 0" << std::endl;
unsigned int i0;
stream_ << "This is line numnber: 0" << std::endl;
)");

const std::string standard_control_text_standard_control_single_line(R"(unsigned int i0;
stream_ << "This is line numnber: 0" << std::endl;
unsigned int i0;
)");

const std::string text_standard_control_text_multi_line(R"(stream_ << "This is line numnber: 0" << std::endl;
stream_ << "This is line numnber: 1" << std::endl;
unsigned int i0;
unsigned int i1;
stream_ << "This is line numnber: 0" << std::endl;
stream_ << "This is line numnber: 1" << std::endl;
)");

const std::string standard_control_text_standard_control_multi_line(R"(unsigned int i0;
unsigned int i1;
stream_ << "This is line numnber: 0" << std::endl;
stream_ << "This is line numnber: 1" << std::endl;
unsigned int i0;
unsigned int i1;
)");

const std::string mixed_content_single_line(
    R"(stream_ << "Start mixed line." << my_variable.print() << "End mixed line." << std::endl;
)");

const std::string mixed_content_multi_line(
    R"(stream_ << "Start mixed line." << my_variable.print() << "End mixed line." << std::endl;
stream_ << "Start mixed line." << my_variable.print() << "End mixed line." << std::endl;
)");

const std::string complex_structure(R"(stream_ << "This is line numnber: 0" << std::endl;
stream_ << "This is line numnber: 1" << std::endl;
stream_ << "This is line numnber: 2" << std::endl;
unsigned int i0;
unsigned int i1;
unsigned int i2;
unsigned int i3;
stream_ << "Start mixed line." << my_variable.print() << "End mixed line." << std::endl;
stream_ << "Start mixed line." << my_variable.print() << "End mixed line." << std::endl;
unsigned int i0;
stream_ << "This is line numnber: 0" << std::endl;
)");

const std::string with_decoration_configuration(R"(/* -*- a_field: a_value -*-
 *
 * this is a marker
 *
 * a_holder
 *
 * licence text
 *
 */
stream_ << "This is line numnber: 0" << std::endl;
)");

const std::string with_containing_namespaces(R"(namespace first {
namespace second {
stream_ << "This is line numnber: 0" << std::endl;
} }
)");

const std::string empty_lines(R"(stream_ << std::endl;
stream_ << std::endl;
)");

const std::string text_line_with_quotes_content(
    R"(stream_ << "\"double quote\" \\\"double quote quote\\\" 'single'" << std::endl;
)");

dogen::formatters::file format(const dogen::stitch::text_template& tt) {
    dogen::stitch::formatter f;
    return f.format(tt);
}

using dogen::utility::test::asserter;
dogen::stitch::test::mock_text_template_factory factory;

}

using dogen::utility::test::contains_checker;
using dogen::stitch::formatting_error;

BOOST_AUTO_TEST_SUITE(formatter_tests)

BOOST_AUTO_TEST_CASE(empty_text_template_results_in_empty_file) {
    SETUP_TEST_LOG_SOURCE("empty_text_template_results_in_empty_file");

    const auto tt(factory.make_empty_template());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "result: " << r;
    BOOST_CHECK(r.content().empty());
}

BOOST_AUTO_TEST_CASE(single_text_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("single_text_line_results_in_expected_template");

    const auto tt(factory.make_single_text_block_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto actual(r.content());
    const auto expected(single_text_line_content);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(multiple_text_lines_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("multiple_text_lines_results_in_expected_template");

    const auto tt(factory.make_multiple_text_block_lines());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format((tt)));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto actual(r.content());
    const auto expected(multiple_text_lines_content);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(single_expression_block_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("single_expression_block_line_results_in_expected_template");

    const auto tt(factory.make_single_expression_block_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto actual(r.content());
    const auto expected(single_expression_block_line);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(multiple_expression_block_lines_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("multiple_expression_block_lines_results_in_expected_template");

    const auto tt(factory.make_multiple_expression_block_lines());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto actual(r.content());
    const auto expected(multiple_expression_block_lines);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(single_standard_control_block_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("single_standard_control_block_line_results_in_expected_template");

    const auto tt(factory.make_single_standard_control_block_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto actual(r.content());
    const auto expected(single_standard_control_block_line);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(multiple_standard_control_block_lines_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("multiple_standard_control_block_lines_results_in_expected_template");

    const auto tt(factory.make_multiple_standard_control_block_lines());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto& actual(r.content());
    const auto expected(multiple_standard_control_block_lines);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(text_expression_text_single_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("text_expression_text_single_line_results_in_expected_template");

    const auto tt(factory.make_text_expression_text_single_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto actual(r.content());
    const auto expected(text_expression_text_single_line);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(expression_text_expression_single_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("expression_text_expression_single_line_results_in_expected_template");

    const auto tt(factory.make_expression_text_expression_single_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto& actual(r.content());
    const auto expected(expression_text_expression_single_line);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(text_expression_text_multi_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("text_expression_text_multi_line_results_in_expected_template");

    const auto tt(factory.make_text_expression_text_multi_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto actual(r.content());
    const auto expected(text_expression_text_multi_line);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(expression_text_expression_multi_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("expression_text_expression_multi_line_results_in_expected_template");

    const auto tt(factory.make_expression_text_expression_multi_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto actual(r.content());
    const auto expected(expression_text_expression_multi_line);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(text_standard_control_text_single_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("text_standard_control_text_single_line_results_in_expected_template");

    const auto tt(factory.make_text_standard_control_text_single_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;
    const auto actual(r.content());
    const auto expected(text_standard_control_text_single_line);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(standard_control_text_standard_control_single_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("standard_control_text_standard_control_single_line_results_in_expected_template");

    const auto tt(
        factory.make_standard_control_text_standard_control_single_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto actual(r.content());
    const auto expected(standard_control_text_standard_control_single_line);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(text_standard_control_text_multi_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("text_standard_control_text_multi_line_results_in_expected_template");

    const auto tt(factory.make_text_standard_control_text_multi_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto actual(r.content());
    const auto expected(text_standard_control_text_multi_line);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(standard_control_text_standard_control_multi_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("standard_control_text_standard_control_multi_line_results_in_expected_template");

    const auto tt(
        factory.make_standard_control_text_standard_control_multi_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto actual(r.content());
    const auto expected(standard_control_text_standard_control_multi_line);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(mixed_content_single_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("mixed_content_single_line_results_in_expected_template");

    const auto tt(factory.make_mixed_content_single_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto actual(r.content());
    const auto expected(mixed_content_single_line);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(mixed_content_multi_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("mixed_content_multi_line_results_in_expected_template");

    const auto tt(factory.make_mixed_content_multi_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto actual(r.content());
    const auto expected(mixed_content_multi_line);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(complex_structure_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("complex_structure_results_in_expected_template");

    const auto tt(factory.make_complex_structure());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto actual(r.content());
    const auto expected(complex_structure);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(decoration_configuration_result_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("decoration_configuration_result_in_expected_template");

    const auto tt(factory.make_with_decoration_configuration());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto actual(r.content());
    const auto expected(with_decoration_configuration);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(containing_namespaces_result_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("containing_namespaces_result_in_expected_template");

    const auto tt(factory.make_with_containing_namespace());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto actual(r.content());
    const auto expected(with_containing_namespaces);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(empty_lines_result_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("empty_lines_result_in_expected_template");

    const auto tt(factory.make_empty_text_lines());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto actual(r.content());
    const auto expected(empty_lines);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_CASE(line_with_quotes_result_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("line_with_quotes_result_in_expected_template");

    const auto tt(factory.make_text_line_with_quotes());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;

    const auto actual(r.content());
    const auto expected(text_line_with_quotes_content);
    BOOST_CHECK(asserter::assert_equals(expected, actual));
}

BOOST_AUTO_TEST_SUITE_END()
