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
#include "dogen/dynamic/schema/types/field_selector.hpp"
#include "dogen/dynamic/schema/test/mock_repository_factory.hpp"
#include "dogen/dynamic/schema/test/mock_workflow_factory.hpp"
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
const std::string licence_declaration("<#@ licence_name=gpl_v3 #>");
const std::string licence_name("licence_name");
const std::string licence_value("gpl_v3");

const std::string only_text_content_second_line("other text content");
const std::string single_line_scriptlet_block_content("single line");

const std::string additional_characters("additional content");
const std::string starting_scriptlet_block_in_block(
    "Cannot start scriptlet block");
const std::string end_without_start("without a start block");

dogen::stitch::text_template parse(const std::string& s) {
    using namespace dogen::dynamic::schema::test;
    mock_repository_factory rf;
    const auto rp(rf.make());
    const auto w(mock_workflow_factory::non_validating_workflow(rp));

    dogen::stitch::parser p(w);
    return p.parse(s);
}

}

using dogen::utility::test::contains_checker;
using dogen::stitch::parsing_error;

BOOST_AUTO_TEST_SUITE(parser)

BOOST_AUTO_TEST_CASE(empty_string_results_in_empty_template) {
    SETUP_TEST_LOG_SOURCE("empty_string_results_in_empty_template");
    const auto tt(parse(empty));
    BOOST_LOG_SEV(lg, debug) << "Result: " << tt;
    BOOST_CHECK(tt.content().empty());
}

BOOST_AUTO_TEST_CASE(string_with_only_text_content_in_single_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("string_with_only_text_content_in_single_line_results_in_expected_template");
    const auto tt(parse(only_text_content_in_single_line));
    BOOST_LOG_SEV(lg, debug) << "Result: " << tt;

    BOOST_REQUIRE(tt.content().size() == 1);
    const auto& block(tt.content().front());
    const auto& mcb(boost::get<dogen::stitch::mixed_content_block>(block));

    BOOST_REQUIRE(mcb.content().size() == 1);
    const auto& line(mcb.content().front());
    const auto s(boost::get<std::string>(line));
    BOOST_CHECK(s == only_text_content_in_single_line);
}

BOOST_AUTO_TEST_CASE(string_with_only_text_content_multi_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("string_with_only_text_content_multi_line_results_in_expected_template");
    const auto tt(parse(only_text_content_muti_line));
    BOOST_LOG_SEV(lg, debug) << "Result: " << tt;

    BOOST_REQUIRE(tt.content().size() == 1);
    const auto& block(tt.content().front());
    const auto& mcb(boost::get<dogen::stitch::mixed_content_block>(block));

    BOOST_REQUIRE(mcb.content().size() == 2);
    const auto& front(mcb.content().front());
    const auto s1(boost::get<std::string>(front));
    BOOST_CHECK(s1 == only_text_content_in_single_line);

    const auto& back(mcb.content().back());
    const auto s2(boost::get<std::string>(back));
    BOOST_CHECK(s2 == only_text_content_second_line);
}

BOOST_AUTO_TEST_CASE(empty_scriptlet_block_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("empty_scriptlet_block_results_in_expected_template");
    const auto tt(parse(empty_scriptlet_block));
    BOOST_LOG_SEV(lg, debug) << "Result: " << tt;

    BOOST_REQUIRE(tt.content().size() == 1);
    const auto& block(tt.content().front());
    const auto& sb(boost::get<dogen::stitch::scriptlet_block>(block));
    BOOST_CHECK(sb.content().empty());
}

BOOST_AUTO_TEST_CASE(single_line_scriptlet_block_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("single_line_scriptlet_block_results_in_expected_template");
    const auto tt(parse(single_line_scriptlet_block));
    BOOST_LOG_SEV(lg, debug) << "Result: " << tt;

    BOOST_REQUIRE(tt.content().size() == 1);
    const auto& block(tt.content().front());
    const auto& sb(boost::get<dogen::stitch::scriptlet_block>(block));
    BOOST_CHECK(sb.content().size() == 1);

    const auto& front(sb.content().front());
    BOOST_CHECK(front == single_line_scriptlet_block_content);
}

BOOST_AUTO_TEST_CASE(text_scriptlet_text_single_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("text_scriptlet_text_single_line_results_in_expected_template");
    const auto tt(parse(text_scriptlet_text_single_line));
    BOOST_LOG_SEV(lg, debug) << "Result: " << tt;

    BOOST_REQUIRE(tt.content().size() == 3);
    auto i(tt.content().begin());
    const auto& tb1(boost::get<dogen::stitch::mixed_content_block>(*i));
    BOOST_CHECK(tb1.content().size() == 1);
    const auto& tb1_front(tb1.content().front());
    const auto s1(boost::get<std::string>(tb1_front));
    BOOST_CHECK(s1 == only_text_content_in_single_line);

    ++i;
    const auto& sb(boost::get<dogen::stitch::scriptlet_block>(*i));
    BOOST_CHECK(sb.content().size() == 1);
    const auto& sb_front(sb.content().front());
    BOOST_CHECK(sb_front == single_line_scriptlet_block_content);

    ++i;
    const auto& tb2(boost::get<dogen::stitch::mixed_content_block>(*i));
    BOOST_CHECK(tb2.content().size() == 1);
    const auto& tb2_front(tb2.content().front());
    const auto s2(boost::get<std::string>(tb2_front));
    BOOST_CHECK(s2 == only_text_content_second_line);
}

BOOST_AUTO_TEST_CASE(scriptlet_text_scriptlet_single_line_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("scriptlet_text_scriptlet_single_line_results_in_expected_template");
    const auto tt(parse(scriptlet_text_scriptlet_single_line));
    BOOST_LOG_SEV(lg, debug) << "Result: " << tt;

    BOOST_REQUIRE(tt.content().size() == 3);
    auto i(tt.content().begin());
    const auto& sb1(boost::get<dogen::stitch::scriptlet_block>(*i));
    BOOST_CHECK(sb1.content().size() == 1);
    const auto& sb1_front(sb1.content().front());
    BOOST_CHECK(sb1_front == single_line_scriptlet_block_content);

    ++i;
    const auto& tb1(boost::get<dogen::stitch::mixed_content_block>(*i));
    BOOST_CHECK(tb1.content().size() == 1);
    const auto& tb1_front(tb1.content().front());
    const auto s1(boost::get<std::string>(tb1_front));
    BOOST_CHECK(s1 == only_text_content_in_single_line);

    ++i;
    const auto& sb2(boost::get<dogen::stitch::scriptlet_block>(*i));
    BOOST_CHECK(sb2.content().size() == 1);
    const auto& sb2_front(sb1.content().front());
    BOOST_CHECK(sb2_front == single_line_scriptlet_block_content);
}

BOOST_AUTO_TEST_CASE(scriptlet_start_additional_characters_throws) {
    SETUP_TEST_LOG_SOURCE("scriptlet_start_additional_characters_throws");

    contains_checker<parsing_error> c(additional_characters);
    BOOST_CHECK_EXCEPTION(parse(scriptlet_start_additional_characters_prefix),
        parsing_error, c);
    BOOST_CHECK_EXCEPTION(parse(scriptlet_start_additional_characters_postfix),
        parsing_error, c);
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

BOOST_AUTO_TEST_CASE(licence_declaration_results_in_expected_template) {
    SETUP_TEST_LOG_SOURCE("licence_declaration_results_in_expected_template");
    const auto tt(parse(licence_declaration));
    BOOST_LOG_SEV(lg, debug) << "Result: " << tt;

    BOOST_CHECK(tt.content().empty());
    BOOST_REQUIRE(tt.extensions().fields().size() == 1);
    dogen::dynamic::schema::field_selector fs(tt.extensions());
    BOOST_CHECK(fs.get_text_content(licence_name) == licence_value);
}

BOOST_AUTO_TEST_SUITE_END()
