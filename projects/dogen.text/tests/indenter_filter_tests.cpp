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
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/test/asserter.hpp"
#include "dogen.text/types/formatters/indent_filter.hpp"

namespace {

const std::string test_module("dogen.text.tests");
const std::string test_suite("indent_filter_tests");

const std::string empty;
const std::string input("this is a sample");
const std::string other_input("yet another text");
const std::string without_blank_lines(R"(this is a sample
)");
const std::string with_one_leading_blank_line(R"(
this is a sample
)");

const std::string with_one_trailing_blank_line(R"(this is a sample

)");
const std::string with_two_trailing_blank_lines(R"(this is a sample


)");

const std::string blank_line_in_between_content(R"(this is a sample

yet another text
)");

const std::string blank_lines_in_between_content(R"(this is a sample



yet another text
)");

const std::string expected(const unsigned int indentation_level,
    const unsigned int indentation_size, const bool without_new_line = false) {
    const unsigned int total_spaces(indentation_level * indentation_size);
    std::ostringstream s;

    if (indentation_level > 0)
        s << std::string(total_spaces, ' ');

    s << input;

    if (!without_new_line)
        s << std::endl;

    return s.str();
}

}

using namespace dogen::utility::test;
using dogen::utility::test::asserter;
using dogen::text::formatters::indent_filter;
using dogen::text::formatters::manage_blank_lines;

BOOST_AUTO_TEST_SUITE(indenter_filter_tests)

BOOST_AUTO_TEST_CASE(default_indentation_level_does_not_indent) {
    SETUP_TEST_LOG_SOURCE("default_indentation_level_does_not_indent");

    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    indent_filter::push(fo, 4);
    fo.push(s);
    fo << input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(expected(0, 4), s.str()));
}

BOOST_AUTO_TEST_CASE(default_indentation_level_without_new_line_does_not_indent) {
    SETUP_TEST_LOG_SOURCE("default_indentation_level_without_new_line_does_not_indent");

    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    indent_filter::push(fo, 4);
    fo.push(s);
    fo << input;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(input, s.str()));
}

BOOST_AUTO_TEST_CASE(incrementing_once_increases_indentation_level_by_one) {
    SETUP_TEST_LOG_SOURCE("incrementing_once_increases_indentation_level_by_one");

    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    indent_filter::push(fo, 4);
    fo.push(s);
    ++fo;
    fo << input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(expected(1, 4), s.str()));
    s.str(empty);
}

BOOST_AUTO_TEST_CASE(incrementing_twice_times_increases_indentation_level_by_two) {
    SETUP_TEST_LOG_SOURCE("incrementing_twice_times_increases_indentation_level_by_two");

    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    indent_filter::push(fo, 4);
    fo.push(s);
    ++fo; ++fo;
    fo << input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(expected(2, 4), s.str()));
    s.str(empty);
}

BOOST_AUTO_TEST_CASE(incrementing_three_times_increases_indentation_level_by_three) {
    SETUP_TEST_LOG_SOURCE("incrementing_three_times_increases_indentation_level_by_three");

    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    indent_filter::push(fo, 4);
    fo.push(s);
    ++fo; ++fo; ++fo;
    fo << input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(expected(3, 4), s.str()));
    s.str(empty);
}

BOOST_AUTO_TEST_CASE(decrementing_once_increases_indentation_level_by_one) {
    SETUP_TEST_LOG_SOURCE("decrementing_once_increases_indentation_level_by_one");

    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    indent_filter::push(fo, 4);
    fo.push(s);
    ++fo; ++fo; ++fo;
    fo << input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(expected(3, 4), s.str()));
    s.str(empty);

    --fo;
    fo << input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(expected(2, 4), s.str()));
    s.str(empty);
}

BOOST_AUTO_TEST_CASE(decrementing_twice_increases_indentation_level_by_two) {
    SETUP_TEST_LOG_SOURCE("decrementing_twice_increases_indentation_level_by_two");

    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    indent_filter::push(fo, 4);
    fo.push(s);
    ++fo; ++fo; ++fo; ++fo;
    fo << input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(expected(4, 4), s.str()));
    s.str(empty);

    --fo; --fo;
    fo << input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(expected(2, 4), s.str()));
    s.str(empty);
}

BOOST_AUTO_TEST_CASE(decrementing_three_times_increases_indentation_level_by_three) {
    SETUP_TEST_LOG_SOURCE("decrementing_three_times_increases_indentation_level_by_three");

    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    indent_filter::push(fo, 4);
    fo.push(s);
    ++fo; ++fo; ++fo; ++fo; ++fo; ++fo;
    fo << input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(expected(6, 4), s.str()));
    s.str(empty);

    --fo; --fo; --fo;
    fo << input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(expected(3, 4), s.str()));
    s.str(empty);
}

BOOST_AUTO_TEST_CASE(unindenting_at_zero_indentation_level_does_nothing) {
    SETUP_TEST_LOG("unindenting_at_zero_indentation_level_does_nothing");

    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    indent_filter::push(fo, 4);
    fo.push(s);
    --fo;
    fo << input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(expected(0, 4), s.str()));
    s.str(empty);
}

BOOST_AUTO_TEST_CASE(positive_indenter_scope_correctly_increases_and_decreases_indentation_level) {
    SETUP_TEST_LOG("positive_indenter_scope_correctly_increases_and_decreases_indentation_level");
    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    indent_filter::push(fo, 4);
    fo.push(s);
    fo << input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(expected(0, 4), s.str()));
    s.str(empty);
    {
        dogen::text::formatters::positive_indenter_scope pis(fo);
        fo << input << std::endl;
        fo.flush();
        BOOST_CHECK(asserter::assert_equals_string(expected(1, 4), s.str()));
        s.str(empty);
        {
            dogen::text::formatters::positive_indenter_scope pis(fo);
            fo << input << std::endl;
            fo.flush();
            BOOST_CHECK(asserter::assert_equals_string(expected(2, 4),
                    s.str()));
            s.str(empty);
        }
        fo << input << std::endl;
        fo.flush();
        BOOST_CHECK(asserter::assert_equals_string(expected(1, 4), s.str()));
        s.str(empty);
    }
    fo << input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(expected(0, 4), s.str()));
    s.str(empty);
}

BOOST_AUTO_TEST_CASE(negative_indenter_scope_correctly_decreases_and_increases_indentation_level) {
    SETUP_TEST_LOG_SOURCE("negative_indenter_scope_correctly_decreases_and_increases_indentation_level");
    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    indent_filter::push(fo, 4);
    fo.push(s);
    ++fo; ++fo;
    fo << input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(expected(2, 4), s.str()));
    s.str(empty);

    {
        dogen::text::formatters::negative_indenter_scope nis(fo);
        fo << input << std::endl;
        fo.flush();
        BOOST_CHECK(asserter::assert_equals_string(expected(1, 4), s.str()));
        s.str(empty);
        {
            dogen::text::formatters::negative_indenter_scope nis(fo);
            fo << input << std::endl;
            fo.flush();
            BOOST_CHECK(asserter::assert_equals_string(expected(0, 4),
                    s.str()));
            s.str(empty);
        }
        fo << input << std::endl;
        fo.flush();
        BOOST_CHECK(asserter::assert_equals_string(expected(1, 4), s.str()));
        s.str(empty);
    }
    fo << input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(expected(2, 4), s.str()));
    s.str(empty);
}

BOOST_AUTO_TEST_CASE(negative_indenter_scope_correctly_handles_zero_indentation_level) {
    SETUP_TEST_LOG("negative_indenter_scope_correctly_handles_zero_indentation_level");
    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    indent_filter::push(fo, 4);
    fo.push(s);
    fo << input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(expected(0, 4), s.str()));
    s.str(empty);
    {
        dogen::text::formatters::negative_indenter_scope nis(fo);
        fo << input << std::endl;
        fo.flush();
        BOOST_CHECK(asserter::assert_equals_string(expected(0, 4), s.str()));
        s.str(empty);
    }
    fo << input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(expected(0, 4), s.str()));
    s.str(empty);
}

BOOST_AUTO_TEST_CASE(single_trailing_blank_line_is_suppressed_when_managing_blank_lines) {
    SETUP_TEST_LOG("single_trailing_blank_line_is_suppressed_when_managing_blank_lines");
    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    indent_filter::push(fo, 4);
    fo.push(s);
    fo << input << std::endl << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(
            with_one_trailing_blank_line, s.str()));
    s.str(empty);

    fo << input << std::endl;
    fo << manage_blank_lines << std::endl;
    BOOST_CHECK(asserter::assert_equals_string(without_blank_lines, s.str()));
    s.str(empty);
}

BOOST_AUTO_TEST_CASE(multiple_trailing_blank_lines_are_suppressed_when_managing_blank_lines) {
    SETUP_TEST_LOG("multiple_trailing_blank_lines_are_suppressed_when_managing_blank_lines");
    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    indent_filter::push(fo, 4);
    fo.push(s);
    fo << input << std::endl << std::endl << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(
            with_two_trailing_blank_lines, s.str()));
    s.str(empty);

    fo << input << std::endl;
    fo << manage_blank_lines << std::endl << std::endl;
    BOOST_CHECK(asserter::assert_equals_string(without_blank_lines, s.str()));
    s.str(empty);
}

BOOST_AUTO_TEST_CASE(one_blank_line_in_between_content_is_printed_out_when_managing_blank_lines) {
    SETUP_TEST_LOG("one_blank_line_in_between_content_is_printed_out_when_managing_blank_lines");
    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    indent_filter::push(fo, 4);
    fo.push(s);
    fo << input << std::endl << std::endl << other_input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(
            blank_line_in_between_content, s.str()));
    s.str(empty);

    fo << input << std::endl;
    fo << manage_blank_lines << std::endl;
    fo << other_input << std::endl;
    BOOST_CHECK(asserter::assert_equals_string(blank_line_in_between_content,
            s.str()));
    s.str(empty);
}

BOOST_AUTO_TEST_CASE(multiple_blank_lines_in_between_content_results_in_a_single_blank_line_out_when_managing_blank_lines) {
    SETUP_TEST_LOG("multiple_blank_lines_in_between_content_results_in_a_single_blank_line_out_when_managing_blank_lines");
    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    indent_filter::push(fo, 4);
    fo.push(s);
    fo << input << std::endl << std::endl << std::endl << std::endl
       << other_input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(
            blank_lines_in_between_content, s.str()));
    s.str(empty);

    fo << input << std::endl;
    fo << manage_blank_lines << std::endl << std::endl
       << std::endl << std::endl;
    fo << other_input << std::endl;
    BOOST_CHECK(asserter::assert_equals_string(blank_line_in_between_content,
            s.str()));
    s.str(empty);
}

BOOST_AUTO_TEST_CASE(single_leading_blank_line_is_not_suppressed_when_managing_blank_lines) {
    SETUP_TEST_LOG("single_leading_blank_line_is_not_suppressed_when_managing_blank_lines");
    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    indent_filter::push(fo, 4);
    fo.push(s);
    fo << std::endl << input << std::endl;
    fo.flush();
    BOOST_CHECK(asserter::assert_equals_string(
            with_one_leading_blank_line, s.str()));
    s.str(empty);

    fo << std::endl << input << std::endl;
    fo << manage_blank_lines << std::endl << std::endl;
    BOOST_CHECK(asserter::assert_equals_string(
            with_one_leading_blank_line, s.str()));
    s.str(empty);
}

BOOST_AUTO_TEST_SUITE_END()
