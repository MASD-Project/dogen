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
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/annotations/types/field_selector.hpp"
#include "dogen/annotations/types/annotation_groups_factory.hpp"
#include "dogen/annotations/test/mock_repository_factory.hpp"
#include "dogen/stitch/io/text_template_io.hpp"
#include "dogen/stitch/types/parsing_error.hpp"
#include "dogen/stitch/types/parser.hpp"

namespace {

const std::string empty;
const std::string test_module("stitch");
const std::string test_suite("parser_tests");

const std::string only_text_content_in_single_line("some text content");
const std::string only_text_content_muti_line(R"(some text content
other text content)");

const std::string inline_standard_control_block(R"(<#+ single line #>)");
const std::string empty_standard_control_block(R"(<#+
#>)");

const std::string single_line_standard_control_block(R"(<#+
single line
#>)");

const std::string text_standard_control_text_single_line(R"(some text content
<#+
single line
#>
other text content
)");

const std::string standard_control_text_standard_control_single_line(R"(<#+
single line
#>
some text content
<#+
single line
#>)");

const std::string standard_control_start_additional_characters_postfix(R"(<#+x
single line
#>)");

const std::string standard_control_start_additional_characters_prefix(R"(x<#+
single line
#>)");

const std::string standard_control_end_additional_characters_postfix(R"(<#+
single line
#>x)");

const std::string standard_control_end_additional_characters_prefix(R"(<#+
single line
x#>)");

const std::string two_standard_control_block_starts(R"(<#+
<#+
single line
#>)");

const std::string two_control_ends(R"(<#+
single line
#>
#>)");

const std::string text_standard_control("some text<#+ single line #>");
const std::string standard_control_text("<#+ single line #>some text");

const std::string stand_alone_expression_block("<#= inline block #>");
const std::string text_expression_block("some text content<#= inline block #>");
const std::string text_expression_block_text(
    "some text content<#= inline block #>other text content");
const std::string expression_block_text_expression_block(
    "<#= inline block #>some text content<#= inline block #>");
const std::string text_expression_block_text_expression_block_text(
    "some text content<#= inline block #>other text "
    "content<#= inline block #>some text content");
const std::string untermined_expression_block("<#= inline block#zzz");
const std::string multiple_start_expression_block_markers(
    "<#= <#= inline block#>");
const std::string multiple_start_standard_control_block_markers(
    "<#+ <#+ inline block#>");
const std::string multiple_end_expression_block("<#= inline block#> #>");
const std::string stray_end_expression_block("<#= inline block#>zzz#>");
const std::string multiline_expression_block(R"(<#=
single line
#>)");
const std::string expression_block_in_expression_block(
    "<#= <#= single line #> #>");

const std::string licence_directive("<#@ licence_name=gpl_v3 #>");
const std::string multiple_directives(R"(<#@ licence_name=gpl_v3 #>
<#@ copyright_notice=Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com> #>)");
const std::string multiple_start_directives("<#@ <#@ licence_name=gpl_v3 #>");
const std::string multiple_end_directives("<#@ licence_name=gpl_v3 #> #>");
const std::string namespaces_directive("<#@ containing_namespaces=a::b::c #>");
const std::string licence_name("licence_name");
const std::string licence_value("gpl_v3");
const std::string namespaces_name("containing_namespaces");
const std::string namespaces_value("a::b::c");
const std::string copyright_notice_name("copyright_notice");
const std::string copyright_notice_value(
    "Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>");

const std::string only_text_content_second_line("other text content");
const std::string single_line_standard_control_block_content("single line");

const std::string additional_characters("additional content");
const std::string starting_standard_control_block_in_block(
    "Cannot start standard control block");
const std::string starting_expression_block_in_block(
    "Cannot start expression block");
const std::string end_without_start("without a corresponding start block");
const std::string inline_block("inline block");
const std::string start_and_end("start and end in the same line");
const std::string middle_of_line("the middle of a line");
const std::string invalid_characters("Invalid characters used");

dogen::stitch::text_template
parse(const std::string& s) {
    dogen::annotations::test::mock_repository_factory rf;
    const auto rp(rf.make());
    const bool throw_on_missing_field_definition(false);
    dogen::annotations::annotation_groups_factory
        f(rp, throw_on_missing_field_definition);
    const dogen::stitch::parser p(f);
    return p.parse(s);
}

}

using dogen::utility::test::contains_checker;
using dogen::stitch::parsing_error;

BOOST_AUTO_TEST_SUITE(parser_tests)

BOOST_AUTO_TEST_CASE(empty_string_results_in_empty_template) {
    SETUP_TEST_LOG_SOURCE("empty_string_results_in_empty_template");
    const auto tt(parse(empty));
    BOOST_CHECK(tt.lines().empty());
}

BOOST_AUTO_TEST_CASE(string_with_only_text_content_in_single_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("string_with_only_text_content_in_single_line_results_in_expected_template");
    const auto tt(parse(only_text_content_in_single_line));

    BOOST_REQUIRE(tt.lines().size() == 1);
    const auto& line(tt.lines().front());

    BOOST_REQUIRE(line.blocks().size() == 1);
    const auto& b(line.blocks().front());
    BOOST_CHECK(b.type() == dogen::stitch::block_types::text_block);
    BOOST_CHECK(b.content() == only_text_content_in_single_line);
}

BOOST_AUTO_TEST_CASE(string_with_only_text_content_multi_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("string_with_only_text_content_multi_line_results_in_expected_template");
    const auto tt(parse(only_text_content_muti_line));

    BOOST_REQUIRE(tt.lines().size() == 2);

    const auto& l1(tt.lines().front());
    BOOST_REQUIRE(l1.blocks().size() == 1);
    const auto& b1(l1.blocks().front());
    BOOST_CHECK(b1.type() == dogen::stitch::block_types::text_block);
    BOOST_CHECK(b1.content() == only_text_content_in_single_line);

    const auto& l2(tt.lines().back());
    BOOST_REQUIRE(l2.blocks().size() == 1);
    const auto& b2(l2.blocks().front());
    BOOST_CHECK(b2.type() == dogen::stitch::block_types::text_block);
    BOOST_CHECK(b2.content() == only_text_content_second_line);
}

BOOST_AUTO_TEST_CASE(inline_standard_control_block_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("inline_standard_control_block_results_in_expected_template");
    const auto tt(parse(inline_standard_control_block));

    BOOST_REQUIRE(tt.lines().size() == 1);
    const auto& line(tt.lines().front());

    BOOST_REQUIRE(line.blocks().size() == 1);
    const auto& b(line.blocks().front());
    BOOST_CHECK(b.type() == dogen::stitch::block_types::standard_control_block);
    BOOST_CHECK(b.content() == single_line_standard_control_block_content);
}

BOOST_AUTO_TEST_CASE(invalid_inline_control_blocks_throw) {
    SETUP_TEST_LOG_SOURCE("invalid_inline_control_blocks_throw");

    contains_checker<parsing_error> c1(starting_expression_block_in_block);
    auto input(multiple_start_expression_block_markers);
    BOOST_CHECK_EXCEPTION(parse(input), parsing_error, c1);

    contains_checker<parsing_error> c2(end_without_start);
    input = multiple_end_expression_block;
    BOOST_CHECK_EXCEPTION(parse(input), parsing_error, c2);

    /*  FIXME
    contains_checker<parsing_error> c3(
        starting_standard_control_block_in_block);
    input = multiple_start_standard_control_block_markers;
    BOOST_CHECK_EXCEPTION(parse(input), parsing_error, c1);
    */
}

BOOST_AUTO_TEST_CASE(empty_standard_control_block_results_in_empty_template) {
    SETUP_TEST_LOG_SOURCE("empty_standard_control_block_results_in_empty_template");
    const auto tt(parse(empty_standard_control_block));
    BOOST_CHECK(tt.lines().empty());
}

BOOST_AUTO_TEST_CASE(single_line_standard_control_block_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("single_line_standard_control_block_results_in_expected_template");
    const auto tt(parse(single_line_standard_control_block));

    BOOST_REQUIRE(tt.lines().size() == 1);
    const auto& line(tt.lines().front());

    BOOST_REQUIRE(line.blocks().size() == 1);
    const auto& b(line.blocks().front());
    BOOST_CHECK(b.type() == dogen::stitch::block_types::standard_control_block);
    BOOST_CHECK(b.content() == single_line_standard_control_block_content);
}

BOOST_AUTO_TEST_CASE(text_standard_standard_control_text_single_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("text_standard_control_text_single_line_results_in_expected_template");
    const auto tt(parse(text_standard_control_text_single_line));
    BOOST_REQUIRE(tt.lines().size() == 3);

    auto i(tt.lines().begin());
    const auto l1(*i);
    BOOST_REQUIRE(l1.blocks().size() == 1);
    const auto& b1(l1.blocks().front());
    using dogen::stitch::block_types;
    BOOST_CHECK(b1.type() == block_types::text_block);
    BOOST_CHECK(b1.content() == only_text_content_in_single_line);

    ++i;
    const auto l2(*i);
    BOOST_REQUIRE(l2.blocks().size() == 1);
    const auto& b2(l2.blocks().front());
    BOOST_CHECK(b2.type() == block_types::standard_control_block);
    BOOST_CHECK(b2.content() == single_line_standard_control_block_content);

    ++i;
    const auto l3(*i);
    BOOST_REQUIRE(l3.blocks().size() == 1);
    const auto& b3(l3.blocks().front());
    BOOST_CHECK(b3.type() == block_types::text_block);
    BOOST_CHECK(b3.content() == only_text_content_second_line);
}

BOOST_AUTO_TEST_CASE(standard_control_text_standard_control_single_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("standard_control_text_standard_control_single_line_results_in_expected_template");
    const auto tt(parse(standard_control_text_standard_control_single_line));
    BOOST_REQUIRE(tt.lines().size() == 3);

    auto i(tt.lines().begin());
    const auto l1(*i);
    BOOST_REQUIRE(l1.blocks().size() == 1);
    const auto& b1(l1.blocks().front());
    using dogen::stitch::block_types;
    BOOST_CHECK(b1.type() == block_types::standard_control_block);
    BOOST_CHECK(b1.content() == single_line_standard_control_block_content);

    ++i;
    const auto l2(*i);
    BOOST_REQUIRE(l2.blocks().size() == 1);
    const auto& b2(l2.blocks().front());
    BOOST_CHECK(b2.type() == block_types::text_block);
    BOOST_CHECK(b2.content() == only_text_content_in_single_line);

    ++i;
    const auto l3(*i);
    BOOST_REQUIRE(l3.blocks().size() == 1);
    const auto& b3(l3.blocks().front());
    BOOST_CHECK(b3.type() == block_types::standard_control_block);
    BOOST_CHECK(b3.content() == single_line_standard_control_block_content);
}

BOOST_AUTO_TEST_CASE(start_standard_control_block_marker_prefixed_by_additional_characters_throws) {
    SETUP_TEST_LOG_SOURCE("start_standard_control_block_marker_prefixed_by_additional_characters_throws");

    contains_checker<parsing_error> c1(middle_of_line);
    auto input(standard_control_start_additional_characters_prefix);
    BOOST_CHECK_EXCEPTION(parse(input), parsing_error, c1);

    input = standard_control_start_additional_characters_postfix;
    contains_checker<parsing_error> c2(additional_characters);
    BOOST_CHECK_EXCEPTION(parse(input), parsing_error, c2);
}

BOOST_AUTO_TEST_CASE(end_control_block_with_additional_characters_throws) {
    SETUP_TEST_LOG_SOURCE("end_control_block_with_additional_characters_throws");

    contains_checker<parsing_error> c(additional_characters);
    auto input(standard_control_end_additional_characters_prefix);
    BOOST_CHECK_EXCEPTION(parse(input), parsing_error, c);

    input = standard_control_end_additional_characters_postfix;
    BOOST_CHECK_EXCEPTION(parse(input), parsing_error, c);
}

BOOST_AUTO_TEST_CASE(two_start_standard_control_blocks_in_a_row_throws) {
    SETUP_TEST_LOG_SOURCE("two_start_standard_control_blocks_in_a_row_throws");

    contains_checker<parsing_error> c(starting_standard_control_block_in_block);
    const auto input(two_standard_control_block_starts);
    BOOST_CHECK_EXCEPTION(parse(input), parsing_error, c);
}

BOOST_AUTO_TEST_CASE(two_end_control_block_markers_in_a_row_throws) {
    SETUP_TEST_LOG_SOURCE("two_end_control_block_markers_in_a_row_throws");

    contains_checker<parsing_error> c(end_without_start);
    BOOST_CHECK_EXCEPTION(parse(two_control_ends), parsing_error, c);
}

BOOST_AUTO_TEST_CASE(text_block_with_standard_control_block_in_the_same_line_throws) {
    SETUP_TEST_LOG_SOURCE("text_block_with_standard_control_block_in_the_same_line_throws");

    contains_checker<parsing_error> c(middle_of_line);
    BOOST_CHECK_EXCEPTION(parse(text_standard_control), parsing_error, c);
}

BOOST_AUTO_TEST_CASE(standard_control_block_with_text_block_in_the_same_line_throws) {
    SETUP_TEST_LOG_SOURCE("standard_control_block_with_text_block_in_the_same_line_throws");

    contains_checker<parsing_error> c(additional_characters);
    BOOST_CHECK_EXCEPTION(parse(standard_control_text), parsing_error, c);
}

BOOST_AUTO_TEST_CASE(licence_directive_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("licence_directive_results_in_expected_template");
    const auto tt(parse(licence_directive));
    BOOST_LOG_SEV(lg, debug) << "Result: " << tt;

    BOOST_CHECK(tt.lines().empty());
    BOOST_REQUIRE(tt.annotation().fields().size() == 1);
    dogen::annotations::field_selector fs(tt.annotation());
    BOOST_CHECK(fs.get_text_content(licence_name) == licence_value);
}

BOOST_AUTO_TEST_CASE(multiple_directives_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("multiple_directives_results_in_expected_template");
    const auto tt(parse(multiple_directives));
    BOOST_LOG_SEV(lg, debug) << "Result: " << tt;

    BOOST_CHECK(tt.lines().empty());
    BOOST_REQUIRE(tt.annotation().fields().size() == 2);
    dogen::annotations::field_selector fs(tt.annotation());
    BOOST_CHECK(fs.get_text_content(licence_name) == licence_value);
    BOOST_CHECK(
        fs.get_text_content(copyright_notice_name) == copyright_notice_value);
}

BOOST_AUTO_TEST_CASE(invalid_directive_throws) {
    SETUP_TEST_LOG_SOURCE("invalid_directive_throws");

    contains_checker<parsing_error> c(invalid_characters);
    BOOST_CHECK_EXCEPTION(parse(multiple_start_directives), parsing_error, c);
    BOOST_CHECK_EXCEPTION(parse(multiple_end_directives), parsing_error, c);
}

BOOST_AUTO_TEST_CASE(line_with_stand_alone_expression_block_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("line_with_stand_alone_expression_block_results_in_expected_template");
    const auto tt(parse(stand_alone_expression_block));
    BOOST_REQUIRE(tt.lines().size() == 1);
    const auto& line(tt.lines().front());

    BOOST_REQUIRE(line.blocks().size() == 1);
    const auto& b(line.blocks().front());
    BOOST_CHECK(b.type() == dogen::stitch::block_types::expression_block);
    BOOST_CHECK(b.content() == inline_block);
}

BOOST_AUTO_TEST_CASE(line_with_text_expression_block_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("line_with_text_expression_block_results_in_expected_template");
    const auto tt(parse(text_expression_block));
    BOOST_REQUIRE(tt.lines().size() == 1);
    const auto& line(tt.lines().front());

    BOOST_REQUIRE(line.blocks().size() == 2);
    const auto& b1(line.blocks().front());
    BOOST_CHECK(b1.type() == dogen::stitch::block_types::text_block);
    BOOST_CHECK(b1.content() == only_text_content_in_single_line);

    const auto& b2(line.blocks().back());
    BOOST_CHECK(b2.type() == dogen::stitch::block_types::expression_block);
    BOOST_CHECK(b2.content() == inline_block);
}

BOOST_AUTO_TEST_CASE(line_with_text_expression_block_text_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("line_with_text_expression_block_text_results_in_expected_template");
    const auto tt(parse(text_expression_block_text));
    BOOST_REQUIRE(tt.lines().size() == 1);
    auto line(tt.lines().front());

    BOOST_REQUIRE(line.blocks().size() == 3);
    auto i(line.blocks().begin());
    const auto& b1(*i);
    using dogen::stitch::block_types;
    BOOST_CHECK(b1.type() == block_types::text_block);
    BOOST_CHECK(b1.content() == only_text_content_in_single_line);

    ++i;
    const auto& b2(*i);
    BOOST_CHECK(b2.type() == block_types::expression_block);
    BOOST_CHECK(b2.content() == inline_block);

    ++i;
    const auto& b3(*i);
    BOOST_CHECK(b3.type() == block_types::text_block);
    BOOST_CHECK(b3.content() == only_text_content_second_line);
}

BOOST_AUTO_TEST_CASE(line_with_expression_block_text_expression_block_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("line_with_expression_block_text_expression_block_results_in_expected_template");
    const auto tt(parse(expression_block_text_expression_block));
    BOOST_REQUIRE(tt.lines().size() == 1);
    auto line(tt.lines().front());

    BOOST_REQUIRE(line.blocks().size() == 3);
    auto i(line.blocks().begin());
    const auto& b1(*i);
    using dogen::stitch::block_types;
    BOOST_CHECK(b1.type() == block_types::expression_block);
    BOOST_CHECK(b1.content() == inline_block);

    ++i;
    const auto& b2(*i);
    BOOST_CHECK(b2.type() == block_types::text_block);
    BOOST_CHECK(b2.content() == only_text_content_in_single_line);

    ++i;
    const auto& b3(*i);
    BOOST_CHECK(b3.type() == block_types::expression_block);
    BOOST_CHECK(b3.content() == inline_block);
}

BOOST_AUTO_TEST_CASE(line_with_text_expression_block_text_expression_block_text_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("line_with_text_expression_block_text_expression_block_text_results_in_expected_template");
    const auto tt(parse(text_expression_block_text_expression_block_text));
    BOOST_REQUIRE(tt.lines().size() == 1);
    auto line(tt.lines().front());

    BOOST_REQUIRE(line.blocks().size() == 5);
    auto i(line.blocks().begin());
    const auto& b1(*i);
    using dogen::stitch::block_types;
    BOOST_CHECK(b1.type() == block_types::text_block);
    BOOST_CHECK(b1.content() == only_text_content_in_single_line);

    ++i;
    const auto& b2(*i);
    BOOST_CHECK(b2.type() == block_types::expression_block);
    BOOST_CHECK(b2.content() == inline_block);

    ++i;
    const auto& b3(*i);
    BOOST_CHECK(b3.type() == block_types::text_block);
    BOOST_CHECK(b3.content() == only_text_content_second_line);

    ++i;
    const auto& b4(*i);
    BOOST_CHECK(b4.type() == block_types::expression_block);
    BOOST_CHECK(b4.content() == inline_block);

    ++i;
    const auto& b5(*i);
    BOOST_CHECK(b5.type() == block_types::text_block);
    BOOST_CHECK(b5.content() == only_text_content_in_single_line);
}

BOOST_AUTO_TEST_CASE(untermined_expression_block_throws) {
    SETUP_TEST_LOG_SOURCE("untermined_expression_block_throws");

    contains_checker<parsing_error> c(start_and_end);
    BOOST_CHECK_EXCEPTION(parse(untermined_expression_block), parsing_error, c);
}

BOOST_AUTO_TEST_CASE(multiline_expression_block_throws) {
    SETUP_TEST_LOG_SOURCE("multiline_expression_block_throws");

    contains_checker<parsing_error> c(start_and_end);
    BOOST_CHECK_EXCEPTION(parse(multiline_expression_block), parsing_error, c);
}

BOOST_AUTO_TEST_CASE(stray_end_expression_block_throws) {
    SETUP_TEST_LOG_SOURCE("stray_end_expression_block_throws");

    contains_checker<parsing_error> c(end_without_start);
    BOOST_CHECK_EXCEPTION(parse(stray_end_expression_block), parsing_error, c);
}

BOOST_AUTO_TEST_CASE(expression_in_expression_throws) {
    SETUP_TEST_LOG_SOURCE("expression_in_expression_throws");

    contains_checker<parsing_error> c(starting_expression_block_in_block);
    const auto input(expression_block_in_expression_block);
    BOOST_CHECK_EXCEPTION(parse(input), parsing_error, c);
}

BOOST_AUTO_TEST_CASE(namespaces_directive_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("namespaces_directive_results_in_expected_template");
    const auto tt(parse(namespaces_directive));
    BOOST_LOG_SEV(lg, debug) << "Result: " << tt;

    BOOST_CHECK(tt.lines().empty());
    BOOST_REQUIRE(tt.annotation().fields().size() == 1);
    dogen::annotations::field_selector fs(tt.annotation());
    BOOST_CHECK(fs.get_text_content(namespaces_name) == namespaces_value);
}

BOOST_AUTO_TEST_SUITE_END()
