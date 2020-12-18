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
#include <algorithm>
#include <boost/test/unit_test.hpp>
#include "dogen.org/types/helpers/parser.hpp"
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/filesystem/path.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.utility/types/test/exception_checkers.hpp"

namespace {

const std::string test_module("dogen.org.tests");
const std::string test_suite("parser_tests");

const std::string empty;
const std::string single_line_document(
    "A simple OrgMode file that the parser should parse properly.");
const std::string multi_line_document(R"(some text content
other text content)");

const std::string multi_line_document_with_spurious_spaces(R"(some text content





other text content)");


dogen::org::entities::document
parse(const std::string& s) {
    dogen::org::helpers::parser p;
    return p.parse(s);
}

}

BOOST_AUTO_TEST_SUITE(stitch_parser_tests)

BOOST_AUTO_TEST_CASE(empty_string_results_in_empty_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("empty_string_results_in_empty_document");
    const auto document(parse(empty));
    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.headlines().empty());
    BOOST_CHECK(document.section().blocks().empty());
}

BOOST_AUTO_TEST_CASE(single_line_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("single_line_document_results_in_expected_org_document");
    const auto document(parse(single_line_document));
    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.headlines().empty());

    const auto& blocks(document.section().blocks());
    BOOST_CHECK(!blocks.empty());

    const auto& c(blocks.front().contents());
    BOOST_CHECK(c == single_line_document);
}

BOOST_AUTO_TEST_CASE(multi_line_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("multi_line_document_results_in_expected_org_document");
    const auto document(parse(multi_line_document));
    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.headlines().empty());

    const auto& blocks(document.section().blocks());
    BOOST_CHECK(!blocks.empty());

    const auto& c(blocks.front().contents());
    BOOST_CHECK(c == multi_line_document);
}

BOOST_AUTO_TEST_CASE(multi_line_document_with_spurious_spaces_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("multi_line_document_with_spurious_spaces_in_expected_org_document");
    const auto document(parse(multi_line_document_with_spurious_spaces));
    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.headlines().empty());

    const auto& blocks(document.section().blocks());
    BOOST_CHECK(!blocks.empty());
    const auto& c(blocks.front().contents());
    BOOST_CHECK(c == multi_line_document_with_spurious_spaces);
}

BOOST_AUTO_TEST_SUITE_END()
