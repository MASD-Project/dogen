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
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/om/types/all.hpp"
#include "dogen/om/io/all_io.hpp"
#include "dogen/om/test_data/all_td.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

namespace {

const std::string empty;
const std::string test_module("om");
const std::string test_suite("comment_formatter_spec");

const std::string c_style_empty(R"(/*
 *
 */
)");

const std::string doxygen_c_style_empty(R"(/**
 *
 */
)");

const std::string licence_c_style(R"(/* -*- mode: xyz; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 *
 */
)");

const std::string licence_shell_style(R"(# -*- mode: xyz; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
#
# Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
#
# This program is free software; you can redistribute it and/or modify
#
)");

const std::string modeline_shell_style(R"(# -*- mode: xyz; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
)");

const std::string function_doxygen(R"(/**
 * @brief Ends the comment block.
 */
)");
const std::string doxygen_brief("@brief Ends the comment block.");

const std::string modeline(
    "-*- mode: xyz; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-");
const std::string licence(R"(Copyright (C) 2012 Kitanda <info@kitanda.co.uk>

This program is free software; you can redistribute it and/or modify)");

const std::string doxgen_multi_line(R"(@brief OM is the Output Model.

@section om_0 Objective

OM was designed to model the contents of the files to output with only the
required level of flexibility needed by Dogen. Thus it does not aim to model
)");

const std::string multi_line_doxygen_c_style(R"(/**
 * @brief OM is the Output Model.
 *
 * @section om_0 Objective
 *
 * OM was designed to model the contents of the files to output with only the
 * required level of flexibility needed by Dogen. Thus it does not aim to model
 *
 */
)");

const std::string multi_line_text(R"(use extensions similar to the dogen ones
--ixx-suffix .ipp
--hxx-suffix .hpp
)");

const std::string multi_line_text_shell_style(R"(# use extensions similar to the dogen ones
# --ixx-suffix .ipp
# --hxx-suffix .hpp
)");

const std::string enumeration("Represents an uninitialised enum");
const std::string enumeration_doxygen(R"(///< Represents an uninitialised enum
)");

const bool start_on_first_line(true);
const bool use_documentation_tool_markup(true);
const bool last_line_is_blank(true);
const bool line_between_blocks(true);
const bool documenting_previous_identifier(true);

}

using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(comment_formatter)

BOOST_AUTO_TEST_CASE(formatting_empty_string_as_c_style_comment_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("formatting_empty_string_as_c_style_comment_produces_expected_output");

    dogen::om::comment_formatter f;
    const auto r(f.format(empty));
    BOOST_LOG_SEV(lg, debug) << "actual: " << std::endl << r;
    BOOST_LOG_SEV(lg, debug) << "expected: " << std::endl << c_style_empty;
    BOOST_CHECK(r == c_style_empty);
}

BOOST_AUTO_TEST_CASE(formatting_empty_string_as_doxygen_c_style_comment_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("formatting_empty_string_as_doxygen_c_style_comment_produces_expected_output");

    dogen::om::comment_formatter f(
        !start_on_first_line,
        use_documentation_tool_markup,
        !documenting_previous_identifier,
        dogen::om::comment_styles::c_style,
        !last_line_is_blank);

    const auto r(f.format(empty));
    BOOST_LOG_SEV(lg, debug) << "actual: " << std::endl << r;
    BOOST_LOG_SEV(lg, debug) << "expected: " << std::endl
                             << doxygen_c_style_empty;
    BOOST_CHECK(r == doxygen_c_style_empty);
}

BOOST_AUTO_TEST_CASE(formatting_licence_as_c_style_comment_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("formatting_licence_as_c_style_comment_produces_expected_output");

    dogen::om::comment_formatter f(
        start_on_first_line,
        !use_documentation_tool_markup,
        !documenting_previous_identifier,
        dogen::om::comment_styles::c_style,
        last_line_is_blank);

    std::list<std::string> content { modeline, licence };
    const auto r(f.format(content, line_between_blocks));
    BOOST_LOG_SEV(lg, debug) << "actual: " << std::endl << r;
    BOOST_LOG_SEV(lg, debug) << "expected: " << std::endl << licence_c_style;
    BOOST_CHECK(r == licence_c_style);
}

BOOST_AUTO_TEST_CASE(formatting_licence_as_shell_style_comment_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("formatting_licence_as_shell_style_comment_produces_expected_output");

    dogen::om::comment_formatter f(
        start_on_first_line,
        !use_documentation_tool_markup,
        !documenting_previous_identifier,
        dogen::om::comment_styles::shell_style,
        last_line_is_blank);

    std::list<std::string> content { modeline, licence };
    const auto r(f.format(content, line_between_blocks));
    BOOST_LOG_SEV(lg, debug) << "actual: " << std::endl << r;
    BOOST_LOG_SEV(lg, debug) << "expected: " << std::endl << licence_shell_style;
    BOOST_CHECK(r == licence_shell_style);
}

BOOST_AUTO_TEST_CASE(formatting_modeline_as_shell_style_comment_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("formatting_modeline_as_shell_style_comment_produces_expected_output");

    dogen::om::comment_formatter f(
        start_on_first_line,
        !use_documentation_tool_markup,
        !documenting_previous_identifier,
        dogen::om::comment_styles::shell_style,
        !last_line_is_blank);

    const auto r(f.format(modeline));
    BOOST_LOG_SEV(lg, debug) << "actual: " << std::endl << r;
    BOOST_LOG_SEV(lg, debug) << "expected: " << std::endl
                             << modeline_shell_style;
    BOOST_CHECK(r == modeline_shell_style);
}

BOOST_AUTO_TEST_CASE(formatting_one_line_as_doxygen_c_style_comment_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("formatting_one_line_as_doxygen_c_style_comment_produces_expected_output");

    dogen::om::comment_formatter f(
        !start_on_first_line,
        use_documentation_tool_markup,
        !documenting_previous_identifier,
        dogen::om::comment_styles::c_style,
        !last_line_is_blank);

    const auto r(f.format(doxygen_brief));
    BOOST_LOG_SEV(lg, debug) << "actual: " << std::endl << r;
    BOOST_LOG_SEV(lg, debug) << "expected: " << std::endl
                             << function_doxygen;
    BOOST_CHECK(r == function_doxygen);
}

BOOST_AUTO_TEST_CASE(formatting_multi_line_as_doxygen_c_style_comment_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("formatting_multi_line_as_doxygen_c_style_comment_produces_expected_output");

    dogen::om::comment_formatter f(
        !start_on_first_line,
        use_documentation_tool_markup,
        !documenting_previous_identifier,
        dogen::om::comment_styles::c_style,
        last_line_is_blank);

    const auto r(f.format(doxgen_multi_line));
    BOOST_LOG_SEV(lg, debug) << "actual: " << std::endl << r;
    BOOST_LOG_SEV(lg, debug) << "expected: " << std::endl
                             << multi_line_doxygen_c_style;
    BOOST_CHECK(r == multi_line_doxygen_c_style);
}

BOOST_AUTO_TEST_CASE(formatting_one_line_as_doxygen_cpp_style_comment_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("formatting_one_line_as_doxygen_cpp_style_comment_produces_expected_output");

    dogen::om::comment_formatter f(
        start_on_first_line,
        use_documentation_tool_markup,
        documenting_previous_identifier,
        dogen::om::comment_styles::cpp_style,
        !last_line_is_blank);

    const auto r(f.format(enumeration));
    BOOST_LOG_SEV(lg, debug) << "actual: " << std::endl << r;
    BOOST_LOG_SEV(lg, debug) << "expected: " << std::endl
                             << enumeration_doxygen;
    BOOST_CHECK(r == enumeration_doxygen);
}

BOOST_AUTO_TEST_CASE(formatting_multi_line_text_as_shell_style_comment_produces_expected_output) {
    SETUP_TEST_LOG_SOURCE("formatting_multi_line_text_as_shell_style_comment_produces_expected_output");

    dogen::om::comment_formatter f(
        start_on_first_line,
        !use_documentation_tool_markup,
        !documenting_previous_identifier,
        dogen::om::comment_styles::shell_style,
        !last_line_is_blank);

    const auto r(f.format(multi_line_text));
    BOOST_LOG_SEV(lg, debug) << "actual: " << std::endl << r;
    BOOST_LOG_SEV(lg, debug) << "expected: " << std::endl
                             << multi_line_text_shell_style;
    BOOST_CHECK(r == multi_line_text_shell_style);
}

BOOST_AUTO_TEST_SUITE_END()
