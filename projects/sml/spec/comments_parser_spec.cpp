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
#include <sstream>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/io/pair_io.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/parsing_error.hpp"
#include "dogen/sml/types/parsing_error.hpp"
#include "dogen/sml/types/comments_parser.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using dogen::utility::test::asserter;

namespace  {

const std::string empty;
const std::string test_module("sml");
const std::string test_suite("comments_parser_spec");

const std::string line_1("line 1");
const std::string line_2("line 2");
const std::string line_3("line 3");

const std::string kvp_1("#DOGEN KEY=VALUE");
const std::string key_1("KEY");
const std::string value_1("VALUE");

const std::string kvp_2(
    "#DOGEN a strange key = some really complicated value 1234");
const std::string key_2("a strange key ");
const std::string value_2(" some really complicated value 1234");

const std::string kvp_no_key("#DOGEN some really complicated value 1234");
const std::string kvp_no_value("#DOGEN KEY=");
const std::string unknown_marker("#UNKNOWN a=b");
const std::string marker_without_space("#DOGENa=b");
const std::string marker_with_leading_space(" #DOGEN a=b");
const std::string marker_in_lower_case("dogen a=b");
const std::string empty_kvp("#DOGEN ");

const std::string no_sep_msg("Expected separator");

}

using dogen::sml::parsing_error;

BOOST_AUTO_TEST_SUITE(comments_parser)

BOOST_AUTO_TEST_CASE(empty_comments_result_in_empty_documentation_and_parameters) {
    SETUP_TEST_LOG_SOURCE("empty_comments_result_in_empty_documentation_and_parameters");
    dogen::sml::comments_parser cp;
    const auto r(cp.parse(empty));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    BOOST_CHECK(r.first.empty());
    BOOST_CHECK(r.second.empty());
}

BOOST_AUTO_TEST_CASE(single_line_comment_without_end_line_results_in_expected_documentation_and_emtpy_parameters) {
    SETUP_TEST_LOG_SOURCE("single_line_comment_without_end_line_results_in_expected_documentation_and_emtpy_parameters");

    BOOST_LOG_SEV(lg, info) << "input: " << line_1;
    dogen::sml::comments_parser cp;
    const auto r(cp.parse(line_1));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    std::istringstream is(r.first);
    std::string line;

    std::getline(is, line);
    BOOST_LOG_SEV(lg, info) << "first line: " << line;
    BOOST_CHECK(line == line_1);

    BOOST_CHECK(r.second.empty());
}

BOOST_AUTO_TEST_CASE(single_line_comment_with_end_line_results_in_expected_documentation_and_emtpy_parameters) {
    SETUP_TEST_LOG_SOURCE("single_line_comment_with_end_line_results_in_expected_documentation_and_emtpy_parameters");

    std::ostringstream os;
    os << line_1 << std::endl;
    BOOST_LOG_SEV(lg, info) << "input: " << os.str();

    dogen::sml::comments_parser cp;
    const auto r(cp.parse(os.str()));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    std::istringstream is(r.first);
    std::string line;

    std::getline(is, line);
    BOOST_LOG_SEV(lg, info) << "first line: " << line;
    BOOST_CHECK(line == line_1);

    BOOST_CHECK(r.second.empty());
}

BOOST_AUTO_TEST_CASE(multi_line_comment_results_in_expected_documentation_and_emtpy_parameters) {
    SETUP_TEST_LOG_SOURCE("multi_line_comment_results_in_expected_documentation_and_emtpy_parameters");

    std::ostringstream os;
    os << line_1 << std::endl
       << line_2 << std::endl << std::endl
       << line_3 << std::endl;

    BOOST_LOG_SEV(lg, info) << "input: " << os.str();
    dogen::sml::comments_parser cp;
    const auto r(cp.parse(os.str()));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    BOOST_CHECK(!r.first.empty());

    std::istringstream is(r.first);
    std::string line;

    std::getline(is, line);
    BOOST_CHECK(line == line_1);

    std::getline(is, line);
    BOOST_CHECK(line == line_2);

    std::getline(is, line);
    BOOST_CHECK(line.empty());

    std::getline(is, line);
    BOOST_CHECK(line == line_3);

    BOOST_CHECK(!std::getline(is, line));

    BOOST_CHECK(r.second.empty());
}

BOOST_AUTO_TEST_CASE(comment_with_valid_kvp_and_no_end_line_results_in_empty_documentation_and_expected_parameter) {
    SETUP_TEST_LOG_SOURCE("comment_with_valid_kvp_and_no_end_line_results_in_empty_documentation_and_expected_parameter");

    BOOST_LOG_SEV(lg, info) << "input: " << kvp_1;
    dogen::sml::comments_parser cp;
    const auto r(cp.parse(kvp_1));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    BOOST_CHECK(r.first.empty());
    BOOST_REQUIRE(r.second.size() == 1);
    BOOST_CHECK(r.second[0].first == key_1);
    BOOST_CHECK(r.second[0].second == value_1);
}

BOOST_AUTO_TEST_CASE(comment_with_valid_kvp_and_end_line_results_in_empty_documentation_and_expected_parameter) {
    SETUP_TEST_LOG_SOURCE("comment_with_valid_kvp_and_end_line_results_in_empty_documentation_and_expected_parameter");

    std::ostringstream os;
    os << kvp_1 << std::endl;
    BOOST_LOG_SEV(lg, info) << "input: " << os.str();

    dogen::sml::comments_parser cp;
    const auto r(cp.parse(os.str()));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    BOOST_CHECK(r.first.empty());
    BOOST_REQUIRE(r.second.size() == 1);
    BOOST_CHECK(r.second[0].first == key_1);
    BOOST_CHECK(r.second[0].second == value_1);
}

BOOST_AUTO_TEST_CASE(comment_with_complex_kvp_results_in_empty_documentation_and_expected_parameter) {
    SETUP_TEST_LOG_SOURCE("comment_with_complex_kvp_results_in_empty_documentation_and_expected_parameter");

    BOOST_LOG_SEV(lg, info) << "input: " << kvp_2;
    dogen::sml::comments_parser cp;
    const auto r(cp.parse(kvp_2));

    BOOST_LOG_SEV(lg, info) << "result: " << r;
    BOOST_CHECK(r.first.empty());
    BOOST_REQUIRE(r.second.size() == 1);
    BOOST_CHECK(r.second[0].first == key_2);
    BOOST_CHECK(r.second[0].second == value_2);
}

BOOST_AUTO_TEST_CASE(comment_with_kvp_with_no_key_throws) {
    SETUP_TEST_LOG_SOURCE("comment_with_kvp_with_no_key_throws");

    BOOST_LOG_SEV(lg, info) << "input: " << kvp_no_key;
    dogen::sml::comments_parser cp;
    BOOST_CHECK_THROW(cp.parse(kvp_no_key), parsing_error);
}

BOOST_AUTO_TEST_CASE(comment_with_kvp_marker_but_no_kvp_throws) {
    SETUP_TEST_LOG_SOURCE("comment_with_kvp_marker_but_no_kvp_throws");

    BOOST_LOG_SEV(lg, info) << "input: " << empty_kvp;
    dogen::sml::comments_parser cp;
    BOOST_CHECK_THROW(cp.parse(empty_kvp), parsing_error);
}

BOOST_AUTO_TEST_CASE(comment_with_kvp_marker_glued_to_key_and_value_creates_documentation) {
    SETUP_TEST_LOG_SOURCE("comment_with_kvp_marker_glued_to_key_and_value_creates_documentation");

    BOOST_LOG_SEV(lg, info) << "input: " << marker_without_space;
    dogen::sml::comments_parser cp;
    const auto r(cp.parse(marker_without_space));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    std::string line;
    std::istringstream is(r.first);
    std::getline(is, line);

    BOOST_LOG_SEV(lg, info) << "first line: " << line;
    BOOST_CHECK(line == marker_without_space);

    BOOST_REQUIRE(r.second.empty());
}

BOOST_AUTO_TEST_CASE(comment_with_kvp_marker_preceded_by_leading_space_creates_documentation) {
    SETUP_TEST_LOG_SOURCE("comment_with_kvp_marker_preceded_by_leading_space_creates_documentation");

    BOOST_LOG_SEV(lg, info) << "input: " << marker_with_leading_space;
    dogen::sml::comments_parser cp;
    const auto r(cp.parse(marker_with_leading_space));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    std::string line;
    std::istringstream is(r.first);
    std::getline(is, line);

    BOOST_LOG_SEV(lg, info) << "first line: " << line;
    BOOST_CHECK(line == marker_with_leading_space);

    BOOST_REQUIRE(r.second.empty());
}

BOOST_AUTO_TEST_CASE(comment_with_kvp_marker_in_lower_case_creates_documentation) {
    SETUP_TEST_LOG_SOURCE("comment_with_kvp_marker_in_lower_case_creates_documentation");

    BOOST_LOG_SEV(lg, info) << "input: " << marker_in_lower_case;
    dogen::sml::comments_parser cp;
    const auto r(cp.parse(marker_in_lower_case));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    std::string line;
    std::istringstream is(r.first);
    std::getline(is, line);

    BOOST_LOG_SEV(lg, info) << "first line: " << line;
    BOOST_CHECK(line == marker_in_lower_case);

    BOOST_REQUIRE(r.second.empty());
}

BOOST_AUTO_TEST_CASE(comment_with_unknown_marker_creates_documentation) {
    SETUP_TEST_LOG_SOURCE("comment_with_unknown_marker_creates_documentation");

    BOOST_LOG_SEV(lg, info) << "input: " << unknown_marker;
    dogen::sml::comments_parser cp;
    const auto r(cp.parse(unknown_marker));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    std::string line;
    std::istringstream is(r.first);
    std::getline(is, line);

    BOOST_LOG_SEV(lg, info) << "first line: " << line;
    BOOST_CHECK(line == unknown_marker);

    BOOST_REQUIRE(r.second.empty());
}


BOOST_AUTO_TEST_CASE(multi_line_comment_with_kvp_results_in_expected_documentation_and_expected_parameter) {
    SETUP_TEST_LOG_SOURCE("multi_multi_line_comment_with_kvp_results_in_expected_documentation_and_expected_parameter");

    std::ostringstream os;
    os << line_1 << std::endl
       << kvp_1 << std::endl << std::endl
       << line_3 << std::endl;

    BOOST_LOG_SEV(lg, info) << "input: " << os.str();
    dogen::sml::comments_parser cp;
    const auto r(cp.parse(os.str()));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    BOOST_CHECK(!r.first.empty());

    std::istringstream is(r.first);
    std::string line;

    std::getline(is, line);
    BOOST_CHECK(line == line_1);

    std::getline(is, line);
    BOOST_CHECK(line.empty());

    std::getline(is, line);
    BOOST_CHECK(line == line_3);

    BOOST_CHECK(!std::getline(is, line));

    BOOST_REQUIRE(r.second.size() == 1);
    BOOST_CHECK(r.second[0].first == key_1);
    BOOST_CHECK(r.second[0].second == value_1);
}

BOOST_AUTO_TEST_CASE(comment_with_multiple_kvps_results_in_empty_documentation_and_expected_parameters) {
    SETUP_TEST_LOG_SOURCE("comment_with_multiple_kvps_results_in_empty_documentation_and_expected_parameters");

    std::ostringstream os;
    os << kvp_1 << std::endl
       << kvp_2 << std::endl
       << kvp_1 << std::endl;

    BOOST_LOG_SEV(lg, info) << "input: " << os.str();
    dogen::sml::comments_parser cp;
    const auto r(cp.parse(os.str()));
    BOOST_LOG_SEV(lg, info) << "result: " << r;

    BOOST_CHECK(r.first.empty());
    BOOST_REQUIRE(r.second.size() == 3);

    BOOST_CHECK(r.second[0].first == key_1);
    BOOST_CHECK(r.second[0].second == value_1);

    BOOST_CHECK(r.second[1].first == key_2);
    BOOST_CHECK(r.second[1].second == value_2);

    BOOST_CHECK(r.second[2].first == key_1);
    BOOST_CHECK(r.second[2].second == value_1);
}

BOOST_AUTO_TEST_SUITE_END()
