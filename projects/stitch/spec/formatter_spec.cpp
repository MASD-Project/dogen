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
const std::string test_suite("formatter_spec");

const std::string single_text_line_content(
    R"(stream_ << "This is line numnber: 0" << std::endl;
)");

const std::string multiple_text_lines_content(
    R"(stream_ << "This is line numnber: 0" << std::endl;
stream_ << "This is line numnber: 1" << std::endl;
)");

const std::string single_line_scriptlet_block(R"(unsigned int i0;
)");

const std::string multi_line_scriptlet_block(R"(unsigned int i0;
unsigned int i1;
)");

const std::string text_scriptlet_text_single_line(R"(stream_ << "This is line numnber: 0" << std::endl;
unsigned int i0;
stream_ << "This is line numnber: 0" << std::endl;
)");

const std::string scriptlet_text_scriptlet_single_line(R"(unsigned int i0;
stream_ << "This is line numnber: 0" << std::endl;
unsigned int i0;
)");

const std::string text_scriptlet_text_multi_line(R"(stream_ << "This is line numnber: 0" << std::endl;
stream_ << "This is line numnber: 1" << std::endl;
unsigned int i0;
unsigned int i1;
stream_ << "This is line numnber: 0" << std::endl;
stream_ << "This is line numnber: 1" << std::endl;
)");

const std::string scriptlet_text_scriptlet_multi_line(R"(unsigned int i0;
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

dogen::formatters::file format(const dogen::stitch::text_template& tt) {
    dogen::stitch::formatter f;
    return f.format(tt);
}

using dogen::utility::test::asserter;
dogen::stitch::test::mock_text_template_factory factory;

}

using dogen::utility::test::contains_checker;
using dogen::stitch::formatting_error;

BOOST_AUTO_TEST_SUITE(formatter)

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

    const auto tt(factory.make_single_text_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;
    BOOST_CHECK(asserter::assert_equals(single_text_line_content, r.content()));
}

BOOST_AUTO_TEST_CASE(multiple_text_lines_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("multiple_text_lines_results_in_expected_template");

    const auto tt(factory.make_multiple_text_lines());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format((tt)));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;
    const auto& c(r.content());
    BOOST_CHECK(asserter::assert_equals(multiple_text_lines_content, c));
}

BOOST_AUTO_TEST_CASE(single_line_scriptlet_block_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("single_line_scriptlet_block_results_in_expected_template");

    const auto tt(factory.make_single_line_scriptlet_block());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;
    const auto& c(r.content());
    BOOST_CHECK(asserter::assert_equals(single_line_scriptlet_block, c));
}

BOOST_AUTO_TEST_CASE(multi_line_scriptlet_block_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("multi_line_scriptlet_block_results_in_expected_template");

    const auto tt(factory.make_multi_line_scriptlet_block());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;
    const auto& c(r.content());
    BOOST_CHECK(asserter::assert_equals(multi_line_scriptlet_block, c));
}

BOOST_AUTO_TEST_CASE(text_scriptlet_text_single_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("text_scriptlet_text_single_line_results_in_expected_template");

    const auto tt(factory.make_text_scriptlet_text_single_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;
    const auto& c(r.content());
    BOOST_CHECK(asserter::assert_equals(text_scriptlet_text_single_line, c));
}

BOOST_AUTO_TEST_CASE(scriptlet_text_scriptlet_single_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("scriptlet_text_scriptlet_single_line_results_in_expected_template");

    const auto tt(factory.make_scriptlet_text_scriptlet_single_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;
    const auto& c(r.content());
    BOOST_CHECK(
        asserter::assert_equals(scriptlet_text_scriptlet_single_line, c));
}

BOOST_AUTO_TEST_CASE(text_scriptlet_text_multi_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("text_scriptlet_text_multi_line_results_in_expected_template");

    const auto tt(factory.make_text_scriptlet_text_multi_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;
    const auto& c(r.content());
    BOOST_CHECK(asserter::assert_equals(text_scriptlet_text_multi_line, c));
}

BOOST_AUTO_TEST_CASE(scriptlet_text_scriptlet_multi_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("scriptlet_text_scriptlet_multi_line_results_in_expected_template");

    const auto tt(factory.make_scriptlet_text_scriptlet_multi_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;
    const auto& c(r.content());
    BOOST_CHECK(
        asserter::assert_equals(scriptlet_text_scriptlet_multi_line, c));
}

BOOST_AUTO_TEST_CASE(mixed_content_single_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("mixed_content_single_line_results_in_expected_template");

    const auto tt(factory.make_mixed_content_single_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;
    const auto& c(r.content());
    BOOST_CHECK(asserter::assert_equals(mixed_content_single_line, c));
}

BOOST_AUTO_TEST_CASE(mixed_content_multi_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("mixed_content_multi_line_results_in_expected_template");

    const auto tt(factory.make_mixed_content_multi_line());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;
    const auto& c(r.content());
    BOOST_CHECK(asserter::assert_equals(mixed_content_multi_line, c));
}

BOOST_AUTO_TEST_CASE(complex_structure_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("complex_structure_results_in_expected_template");

    const auto tt(factory.make_complex_structure());
    BOOST_LOG_SEV(lg, debug) << "input: " << tt;

    const auto r(format(tt));
    BOOST_LOG_SEV(lg, debug) << "Result: " << r;
    const auto& c(r.content());
    BOOST_CHECK(asserter::assert_equals(complex_structure, c));
}

BOOST_AUTO_TEST_SUITE_END()
