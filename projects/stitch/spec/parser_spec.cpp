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
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/test/mock_repository_factory.hpp"
#include "dogen/dynamic/test/mock_workflow_factory.hpp"
#include "dogen/stitch/io/text_template_io.hpp"
#include "dogen/stitch/types/parsing_error.hpp"
#include "dogen/stitch/types/parser.hpp"

namespace {

const std::string empty;
const std::string test_module("stitch");
const std::string test_suite("parser_spec");

const std::string only_text_content_in_single_line("some text content");
const std::string only_text_content_muti_line(R"(some text content
other text content)");

const std::string inline_scriptlet_block(R"(<#+ single line #>)");
const std::string empty_scriptlet_block(R"(<#+
#>)");

const std::string single_line_scriptlet_block(R"(<#+
single line
#>)");

const std::string text_scriptlet_text_single_line(R"(some text content
<#+
single line
#>
other text content
)");

const std::string scriptlet_text_scriptlet_single_line(R"(<#+
single line
#>
some text content
<#+
single line
#>)");

const std::string scriptlet_start_additional_characters_postfix(R"(<#+x
single line
#>)");

const std::string scriptlet_start_additional_characters_prefix(R"(x<#+
single line
#>)");

const std::string scriptlet_end_additional_characters_postfix(R"(<#+
single line
#>x)");

const std::string scriptlet_end_additional_characters_prefix(R"(<#+
single line
x#>)");

const std::string two_scriptlet_starts(R"(<#+
<#+
single line
#>)");

const std::string two_scriptlet_ends(R"(<#+
single line
#>
#>)");

const std::string text_scriptlet("some text<#+ single line #>");
const std::string scriptlet_text("<#+ single line #>some text");

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
const std::string multiple_start_expression_block("<#= <#= inline block#>");
const std::string multiple_end_expression_block("<#= inline block#> #>");
const std::string stray_end_expression_block("<#= inline block#>zzz#>");
const std::string multiline_expression_block(R"(<#=
single line
#>)");
const std::string expression_in_expression("<#= <#= single line #> #>");

const std::string licence_declaration("<#@ licence_name=gpl_v3 #>");
const std::string multiple_declarations(R"(<#@ licence_name=gpl_v3 #>
<#@ copyright_notice=Copyright(C) 2012 Kitanda <info@kitanda.co.uk> #>)");
const std::string multiple_start_declarations("<#@ <#@ licence_name=gpl_v3 #>");
const std::string multiple_end_declarations("<#@ licence_name=gpl_v3 #> #>");
const std::string namespaces_declaration("<#@ containing_namespaces=a::b::c #>");
const std::string licence_name("licence_name");
const std::string licence_value("gpl_v3");
const std::string namespaces_name("containing_namespaces");
const std::string namespaces_value("a::b::c");
const std::string copyright_notice_name("copyright_notice");
const std::string copyright_notice_value(
    "Copyright(C) 2012 Kitanda <info@kitanda.co.uk>");

const std::string only_text_content_second_line("other text content");
const std::string single_line_scriptlet_block_content("single line");

const std::string additional_characters("additional content");
const std::string starting_scriptlet_block_in_block(
    "Cannot start scriptlet block");
const std::string end_without_start("without a start block");
const std::string inline_block("inline block");
const std::string start_and_end("start and end in the same line");
const std::string middle_of_line("the middle of a line");
const std::string invalid_characters("Invalid characters used");

dogen::stitch::text_template
parse(const std::string& s) {
    using namespace dogen::dynamic::test;
    mock_repository_factory rf;
    const auto rp(rf.make());
    const auto w(mock_workflow_factory::non_validating_workflow(rp));

    const dogen::stitch::parser p(w);
    return p.parse(s);
}

}

using dogen::utility::test::contains_checker;
using dogen::stitch::parsing_error;

BOOST_AUTO_TEST_SUITE(parser)

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

    BOOST_REQUIRE(line.segments().size() == 1);
    const auto& sg(line.segments().front());
    BOOST_CHECK(sg.type() == dogen::stitch::segment_types::text);
    BOOST_CHECK(sg.content() == only_text_content_in_single_line);
}

BOOST_AUTO_TEST_CASE(string_with_only_text_content_multi_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("string_with_only_text_content_multi_line_results_in_expected_template");
    const auto tt(parse(only_text_content_muti_line));

    BOOST_REQUIRE(tt.lines().size() == 2);

    const auto& l1(tt.lines().front());
    BOOST_REQUIRE(l1.segments().size() == 1);
    const auto& sg1(l1.segments().front());
    BOOST_CHECK(sg1.type() == dogen::stitch::segment_types::text);
    BOOST_CHECK(sg1.content() == only_text_content_in_single_line);

    const auto& l2(tt.lines().back());
    BOOST_REQUIRE(l2.segments().size() == 1);
    const auto& sg2(l2.segments().front());
    BOOST_CHECK(sg2.type() == dogen::stitch::segment_types::text);
    BOOST_CHECK(sg2.content() == only_text_content_second_line);
}

BOOST_AUTO_TEST_CASE(inline_scriptlet_block_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("inline_scriptlet_block_results_in_expected_template");
    const auto tt(parse(inline_scriptlet_block));

    BOOST_REQUIRE(tt.lines().size() == 1);
    const auto& line(tt.lines().front());

    BOOST_REQUIRE(line.segments().size() == 1);
    const auto& sg(line.segments().front());
    BOOST_CHECK(sg.type() == dogen::stitch::segment_types::scriptlet);
    BOOST_CHECK(sg.content() == single_line_scriptlet_block_content);
}

BOOST_AUTO_TEST_CASE(invalid_inline_scriptlets_throw) {
    SETUP_TEST_LOG_SOURCE("invalid_inline_scriptlets_throw");

    contains_checker<parsing_error> c1(starting_scriptlet_block_in_block);
    BOOST_CHECK_EXCEPTION(
        parse(multiple_start_expression_block), parsing_error, c1);

    contains_checker<parsing_error> c2(end_without_start);
    BOOST_CHECK_EXCEPTION(
        parse(multiple_end_expression_block), parsing_error, c2);
}

BOOST_AUTO_TEST_CASE(empty_scriptlet_block_results_in_empty_template) {
    SETUP_TEST_LOG_SOURCE("empty_scriptlet_block_results_in_empty_template");
    const auto tt(parse(empty_scriptlet_block));
    BOOST_CHECK(tt.lines().empty());
}

BOOST_AUTO_TEST_CASE(single_line_scriptlet_block_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("single_line_scriptlet_block_results_in_expected_template");
    const auto tt(parse(single_line_scriptlet_block));

    BOOST_REQUIRE(tt.lines().size() == 1);
    const auto& line(tt.lines().front());

    BOOST_REQUIRE(line.segments().size() == 1);
    const auto& sg(line.segments().front());
    BOOST_CHECK(sg.type() == dogen::stitch::segment_types::scriptlet);
    BOOST_CHECK(sg.content() == single_line_scriptlet_block_content);
}

BOOST_AUTO_TEST_CASE(text_scriptlet_text_single_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("text_scriptlet_text_single_line_results_in_expected_template");
    const auto tt(parse(text_scriptlet_text_single_line));
    BOOST_REQUIRE(tt.lines().size() == 3);

    auto i(tt.lines().begin());
    const auto l1(*i);
    BOOST_REQUIRE(l1.segments().size() == 1);
    const auto& sg1(l1.segments().front());
    BOOST_CHECK(sg1.type() == dogen::stitch::segment_types::text);
    BOOST_CHECK(sg1.content() == only_text_content_in_single_line);

    ++i;
    const auto l2(*i);
    BOOST_REQUIRE(l2.segments().size() == 1);
    const auto& sg2(l2.segments().front());
    BOOST_CHECK(sg2.type() == dogen::stitch::segment_types::scriptlet);
    BOOST_CHECK(sg2.content() == single_line_scriptlet_block_content);

    ++i;
    const auto l3(*i);
    BOOST_REQUIRE(l3.segments().size() == 1);
    const auto& sg3(l3.segments().front());
    BOOST_CHECK(sg3.type() == dogen::stitch::segment_types::text);
    BOOST_CHECK(sg3.content() == only_text_content_second_line);
}

BOOST_AUTO_TEST_CASE(scriptlet_text_scriptlet_single_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("scriptlet_text_scriptlet_single_line_results_in_expected_template");
    const auto tt(parse(scriptlet_text_scriptlet_single_line));
    BOOST_REQUIRE(tt.lines().size() == 3);

    auto i(tt.lines().begin());
    const auto l1(*i);
    BOOST_REQUIRE(l1.segments().size() == 1);
    const auto& sg1(l1.segments().front());
    BOOST_CHECK(sg1.type() == dogen::stitch::segment_types::scriptlet);
    BOOST_CHECK(sg1.content() == single_line_scriptlet_block_content);

    ++i;
    const auto l2(*i);
    BOOST_REQUIRE(l2.segments().size() == 1);
    const auto& sg2(l2.segments().front());
    BOOST_CHECK(sg2.type() == dogen::stitch::segment_types::text);
    BOOST_CHECK(sg2.content() == only_text_content_in_single_line);

    ++i;
    const auto l3(*i);
    BOOST_REQUIRE(l3.segments().size() == 1);
    const auto& sg3(l3.segments().front());
    BOOST_CHECK(sg3.type() == dogen::stitch::segment_types::scriptlet);
    BOOST_CHECK(sg3.content() == single_line_scriptlet_block_content);
}

BOOST_AUTO_TEST_CASE(scriptlet_start_additional_characters_throws) {
    SETUP_TEST_LOG_SOURCE("scriptlet_start_additional_characters_throws");

    contains_checker<parsing_error> c1(middle_of_line);
    BOOST_CHECK_EXCEPTION(parse(scriptlet_start_additional_characters_prefix),
        parsing_error, c1);

    contains_checker<parsing_error> c2(additional_characters);
    BOOST_CHECK_EXCEPTION(parse(scriptlet_start_additional_characters_postfix),
        parsing_error, c2);
}

BOOST_AUTO_TEST_CASE(scriptlet_end_additional_characters_throws) {
    SETUP_TEST_LOG_SOURCE("scriptlet_end_additional_characters_throws");

    contains_checker<parsing_error> c(additional_characters);
    BOOST_CHECK_EXCEPTION(parse(scriptlet_end_additional_characters_prefix),
        parsing_error, c);
    BOOST_CHECK_EXCEPTION(parse(scriptlet_end_additional_characters_postfix),
        parsing_error, c);
}

BOOST_AUTO_TEST_CASE(two_scriptlet_starts_throws) {
    SETUP_TEST_LOG_SOURCE("two_scriptlet_starts_throws");

    contains_checker<parsing_error> c(starting_scriptlet_block_in_block);
    BOOST_CHECK_EXCEPTION(parse(two_scriptlet_starts), parsing_error, c);
}

BOOST_AUTO_TEST_CASE(two_scriptlet_ends_throws) {
    SETUP_TEST_LOG_SOURCE("two_scriptlet_ends_throws");

    contains_checker<parsing_error> c(end_without_start);
    BOOST_CHECK_EXCEPTION(parse(two_scriptlet_ends), parsing_error, c);
}

BOOST_AUTO_TEST_CASE(text_scriptlet_throws) {
    SETUP_TEST_LOG_SOURCE("text_scriptlet_throws");

    contains_checker<parsing_error> c(middle_of_line);
    BOOST_CHECK_EXCEPTION(parse(text_scriptlet), parsing_error, c);
}

BOOST_AUTO_TEST_CASE(scriptlet_text_throws) {
    SETUP_TEST_LOG_SOURCE("scriptlet_text_throws");

    contains_checker<parsing_error> c(additional_characters);
    BOOST_CHECK_EXCEPTION(parse(scriptlet_text), parsing_error, c);
}

BOOST_AUTO_TEST_CASE(licence_declaration_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("licence_declaration_results_in_expected_template");
    const auto tt(parse(licence_declaration));
    BOOST_LOG_SEV(lg, debug) << "Result: " << tt;

    BOOST_CHECK(tt.lines().empty());
    BOOST_REQUIRE(tt.extensions().fields().size() == 1);
    dogen::dynamic::field_selector fs(tt.extensions());
    BOOST_CHECK(fs.get_text_content(licence_name) == licence_value);
}

BOOST_AUTO_TEST_CASE(multiple_declarations_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("multiple_declarations_results_in_expected_template");
    const auto tt(parse(multiple_declarations));
    BOOST_LOG_SEV(lg, debug) << "Result: " << tt;

    BOOST_CHECK(tt.lines().empty());
    BOOST_REQUIRE(tt.extensions().fields().size() == 2);
    dogen::dynamic::field_selector fs(tt.extensions());
    BOOST_CHECK(fs.get_text_content(licence_name) == licence_value);
    BOOST_CHECK(
        fs.get_text_content(copyright_notice_name) == copyright_notice_value);
}

BOOST_AUTO_TEST_CASE(invalid_declaration_throws) {
    SETUP_TEST_LOG_SOURCE("invalid_declaration_throws");

    contains_checker<parsing_error> c(invalid_characters);
    BOOST_CHECK_EXCEPTION(parse(multiple_start_declarations), parsing_error, c);
    BOOST_CHECK_EXCEPTION(parse(multiple_end_declarations), parsing_error, c);
}

BOOST_AUTO_TEST_CASE(stand_alone_expression_block_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("stand_alone_expression_block_results_in_expected_template");
    const auto tt(parse(stand_alone_expression_block));
    BOOST_REQUIRE(tt.lines().size() == 1);
    const auto& line(tt.lines().front());

    BOOST_REQUIRE(line.segments().size() == 1);
    const auto& sg(line.segments().front());
    BOOST_CHECK(sg.type() == dogen::stitch::segment_types::scriptlet);
    BOOST_CHECK(sg.content() == inline_block);
}

BOOST_AUTO_TEST_CASE(text_expression_block_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("text_expression_block_results_in_expected_template");
    const auto tt(parse(text_expression_block));
    BOOST_REQUIRE(tt.lines().size() == 1);
    const auto& line(tt.lines().front());

    BOOST_REQUIRE(line.segments().size() == 2);
    const auto& sg1(line.segments().front());
    BOOST_CHECK(sg1.type() == dogen::stitch::segment_types::text);
    BOOST_CHECK(sg1.content() == only_text_content_in_single_line);

    const auto& sg2(line.segments().back());
    BOOST_CHECK(sg2.type() == dogen::stitch::segment_types::scriptlet);
    BOOST_CHECK(sg2.content() == inline_block);
}

BOOST_AUTO_TEST_CASE(text_expression_block_text_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("text_expression_block_text_results_in_expected_template");
    const auto tt(parse(text_expression_block_text));
    BOOST_REQUIRE(tt.lines().size() == 1);
    auto line(tt.lines().front());

    BOOST_REQUIRE(line.segments().size() == 3);
    auto i(line.segments().begin());
    const auto& sg1(*i);
    BOOST_CHECK(sg1.type() == dogen::stitch::segment_types::text);
    BOOST_CHECK(sg1.content() == only_text_content_in_single_line);

    ++i;
    const auto& sg2(*i);
    BOOST_CHECK(sg2.type() == dogen::stitch::segment_types::scriptlet);
    BOOST_CHECK(sg2.content() == inline_block);

    ++i;
    const auto& sg3(*i);
    BOOST_CHECK(sg3.type() == dogen::stitch::segment_types::text);
    BOOST_CHECK(sg3.content() == only_text_content_second_line);
}

BOOST_AUTO_TEST_CASE(expression_block_text_expression_block_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("expression_block_text_expression_block_results_in_expected_template");
    const auto tt(parse(expression_block_text_expression_block));
    BOOST_REQUIRE(tt.lines().size() == 1);
    auto line(tt.lines().front());

    BOOST_REQUIRE(line.segments().size() == 3);
    auto i(line.segments().begin());
    const auto& sg1(*i);
    BOOST_CHECK(sg1.type() == dogen::stitch::segment_types::scriptlet);
    BOOST_CHECK(sg1.content() == inline_block);

    ++i;
    const auto& sg2(*i);
    BOOST_CHECK(sg2.type() == dogen::stitch::segment_types::text);
    BOOST_CHECK(sg2.content() == only_text_content_in_single_line);

    ++i;
    const auto& sg3(*i);
    BOOST_CHECK(sg3.type() == dogen::stitch::segment_types::scriptlet);
    BOOST_CHECK(sg3.content() == inline_block);
}

BOOST_AUTO_TEST_CASE(text_expression_block_text_expression_block_text_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("text_expression_block_text_expression_block_text_results_in_expected_template");
    const auto tt(parse(text_expression_block_text_expression_block_text));
    BOOST_REQUIRE(tt.lines().size() == 1);
    auto line(tt.lines().front());

    BOOST_REQUIRE(line.segments().size() == 5);
    auto i(line.segments().begin());
    const auto& sg1(*i);
    BOOST_CHECK(sg1.type() == dogen::stitch::segment_types::text);
    BOOST_CHECK(sg1.content() == only_text_content_in_single_line);

    ++i;
    const auto& sg2(*i);
    BOOST_CHECK(sg2.type() == dogen::stitch::segment_types::scriptlet);
    BOOST_CHECK(sg2.content() == inline_block);

    ++i;
    const auto& sg3(*i);
    BOOST_CHECK(sg3.type() == dogen::stitch::segment_types::text);
    BOOST_CHECK(sg3.content() == only_text_content_second_line);

    ++i;
    const auto& sg4(*i);
    BOOST_CHECK(sg4.type() == dogen::stitch::segment_types::scriptlet);
    BOOST_CHECK(sg4.content() == inline_block);

    ++i;
    const auto& sg5(*i);
    BOOST_CHECK(sg5.type() == dogen::stitch::segment_types::text);
    BOOST_CHECK(sg5.content() == only_text_content_in_single_line);
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

    contains_checker<parsing_error> c(starting_scriptlet_block_in_block);
    BOOST_CHECK_EXCEPTION(parse(expression_in_expression), parsing_error, c);
}

BOOST_AUTO_TEST_CASE(namespaces_declaration_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("namespaces_declaration_results_in_expected_template");
    const auto tt(parse(namespaces_declaration));
    BOOST_LOG_SEV(lg, debug) << "Result: " << tt;

    BOOST_CHECK(tt.lines().empty());
    BOOST_REQUIRE(tt.extensions().fields().size() == 1);
    dogen::dynamic::field_selector fs(tt.extensions());
    BOOST_CHECK(fs.get_text_content(namespaces_name) == namespaces_value);
}

BOOST_AUTO_TEST_SUITE_END()
