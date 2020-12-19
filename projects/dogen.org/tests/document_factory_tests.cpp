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
#include <boost/test/tools/old/interface.hpp>
#include <boost/test/unit_test.hpp>
#include "dogen.org/types/helpers/document_factory.hpp"
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/filesystem/path.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.utility/types/test/exception_checkers.hpp"

namespace {

const std::string test_module("dogen.org.tests");
const std::string test_suite("document_factory_tests");

const std::string empty;
const std::string single_line_document(
    "A simple OrgMode file that the document_factory should parse properly.");
const std::string multi_line_document(R"(some text content
other text content)");

const std::string multi_line_document_with_spurious_spaces(R"(some text content





other text content)");
const std::string single_word_title("title");
const std::string multi_word_title("title with more than one word");

const std::string simple_headline("* title");
const std::string multi_word_headline("* title with more than one word");
const std::string headline_with_priority_cookie_no_title("* [#A]");
const std::string headline_with_priority_cookie_and_single_word_title(
    "* [#Z] title");
const std::string headline_with_priority_cookie_and_multi_word_title(
    "* [#Z] title with more than one word");
const std::string title_less_headline("***");
const std::string title_less_headline_with_space("*** ");
const std::string headline_with_real_todo_no_title("* TODO");
const std::string headline_with_fake_todo_no_title("* FAKE");

const std::string headline_with_todo_keyword_and_single_word_title(
    "* TODO title");
const std::string headline_with_todo_keyword_and_multi_word_title(
    "* TODO title with more than one word");
const std::string
headline_with_priority_todo_and_single_word_title(
    "* DONE [#I] title");
const std::string
headline_with_priority_todo_and_multi_word_title(
    "* DONE [#I] title with more than one word");
const std::string headline_with_no_title_and_single_tag("* :tag:");
const std::string headline_with_no_title_and_multiple_tags("* :tag:b:c:d:");
const std::string headline_with_single_word_title_and_single_tag(
    "* title :tag:");
const std::string headline_with_multi_word_title_and_single_tag(
    "* title with more than one word :tag:");
const std::string complete_headline(
    "* DONE [#A] title with more than one word :tag:b:c:d:");
const std::string one_headline_with_content(R"(some text content
other text content

* first headline

headline content
more headline content)");

const std::string top_level_content_two_headlines_without_content(
    R"(some text content
other text content

* first headline
** second headline)");

dogen::org::entities::document
make(const std::string& s) {
    dogen::org::helpers::document_factory f;
    return f.make(s);
}

}

BOOST_AUTO_TEST_SUITE(document_factory_tests)

BOOST_AUTO_TEST_CASE(empty_string_results_in_empty_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("empty_string_results_in_empty_document");
    const auto document(make(empty));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.headlines().empty());
    BOOST_CHECK(document.section().blocks().empty());
}

BOOST_AUTO_TEST_CASE(single_line_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("single_line_document_results_in_expected_org_document");
    const auto document(make(single_line_document));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.headlines().empty());

    const auto& blocks(document.section().blocks());
    BOOST_REQUIRE(!blocks.empty());

    const auto& c(blocks.front().contents());
    BOOST_CHECK(c == single_line_document);
}

BOOST_AUTO_TEST_CASE(multi_line_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("multi_line_document_results_in_expected_org_document");
    const auto document(make(multi_line_document));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.headlines().empty());

    const auto& blocks(document.section().blocks());
    BOOST_REQUIRE(!blocks.empty());

    const auto& c(blocks.front().contents());
    BOOST_CHECK(c == multi_line_document);
}

BOOST_AUTO_TEST_CASE(multi_line_document_with_spurious_spaces_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("multi_line_document_with_spurious_spaces_in_expected_org_document");
    const auto document(make(multi_line_document_with_spurious_spaces));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.headlines().empty());

    const auto& blocks(document.section().blocks());
    BOOST_REQUIRE(!blocks.empty());
    const auto& c(blocks.front().contents());
    BOOST_CHECK(c == multi_line_document_with_spurious_spaces);
}

BOOST_AUTO_TEST_CASE(simple_headline_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("simple_headline_document_in_expected_org_document");
    const auto document(make(simple_headline));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.section().blocks().empty());

    const auto& hls(document.headlines());
    BOOST_REQUIRE(hls.size() == 1);

    const auto& hl(hls.front());
    BOOST_CHECK(hl.headlines().empty());
    BOOST_CHECK(hl.title() == single_word_title);
    BOOST_CHECK(hl.affiliated_keywords().empty());
    BOOST_CHECK(hl.drawers().empty());
    BOOST_CHECK(hl.section().blocks().empty());
    BOOST_CHECK(hl.tags().empty());
}

BOOST_AUTO_TEST_CASE(multi_word_headline_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("multi_word_headline_document_in_expected_org_document");
    const auto document(make(multi_word_headline));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.section().blocks().empty());

    const auto& hls(document.headlines());
    BOOST_REQUIRE(hls.size() == 1);

    const auto& hl(hls.front());
    BOOST_CHECK(hl.headlines().empty());
    BOOST_CHECK(hl.title() == multi_word_title);
    BOOST_CHECK(hl.affiliated_keywords().empty());
    BOOST_CHECK(hl.drawers().empty());
    BOOST_CHECK(hl.section().blocks().empty());
    BOOST_CHECK(hl.tags().empty());
}

BOOST_AUTO_TEST_CASE(title_less_headline_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("title_less_headline_document_results_in_expected_org_document");
    const auto document(make(title_less_headline));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.headlines().empty());

    const auto& blocks(document.section().blocks());
    BOOST_REQUIRE(!blocks.empty());

    const auto& c(blocks.front().contents());
    BOOST_CHECK(c == title_less_headline);
}

BOOST_AUTO_TEST_CASE(title_less_headline_with_space_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("title_less_headline_with_space_document_results_in_expected_org_document");
    const auto document(make(title_less_headline_with_space));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.headlines().empty());

    const auto& blocks(document.section().blocks());
    BOOST_REQUIRE(!blocks.empty());

    const auto& c(blocks.front().contents());
    BOOST_CHECK(c == title_less_headline_with_space);
}

BOOST_AUTO_TEST_CASE(headline_with_priority_cookie_no_title_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("headline_with_priority_cookie_no_title_document_in_expected_org_document");
    const auto document(make(headline_with_priority_cookie_no_title));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.section().blocks().empty());

    const auto& hls(document.headlines());
    BOOST_REQUIRE(hls.size() == 1);

    const auto& hl(hls.front());
    BOOST_CHECK(hl.headlines().empty());
    BOOST_CHECK(hl.title().empty());
    BOOST_CHECK(hl.priority().value() == "[#A]");
    BOOST_CHECK(hl.affiliated_keywords().empty());
    BOOST_CHECK(hl.drawers().empty());
    BOOST_CHECK(hl.section().blocks().empty());
    BOOST_CHECK(hl.todo_keyword().value().empty());
    BOOST_CHECK(hl.tags().empty());
}

BOOST_AUTO_TEST_CASE(headline_with_priority_cookie_and_single_word_title_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("headline_with_priority_cookie_and_single_word_title_document_in_expected_org_document");
    const auto document(make(headline_with_priority_cookie_and_single_word_title));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.section().blocks().empty());

    const auto& hls(document.headlines());
    BOOST_REQUIRE(hls.size() == 1);

    const auto& hl(hls.front());
    BOOST_CHECK(hl.headlines().empty());
    BOOST_CHECK(hl.title() == single_word_title);
    BOOST_CHECK(hl.priority().value() == "[#Z]");
    BOOST_CHECK(hl.affiliated_keywords().empty());
    BOOST_CHECK(hl.drawers().empty());
    BOOST_CHECK(hl.section().blocks().empty());
    BOOST_CHECK(hl.todo_keyword().value().empty());
    BOOST_CHECK(hl.tags().empty());
}

BOOST_AUTO_TEST_CASE(headline_with_priority_cookie_and_multi_word_title_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("headline_with_priority_cookie_and_multi_word_title_document_in_expected_org_document");
    const auto document(make(headline_with_priority_cookie_and_multi_word_title));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.section().blocks().empty());

    const auto& hls(document.headlines());
    BOOST_REQUIRE(hls.size() == 1);

    const auto& hl(hls.front());
    BOOST_CHECK(hl.headlines().empty());
    BOOST_CHECK(hl.title() == multi_word_title);
    BOOST_CHECK(hl.priority().value() == "[#Z]");
    BOOST_CHECK(hl.affiliated_keywords().empty());
    BOOST_CHECK(hl.drawers().empty());
    BOOST_CHECK(hl.section().blocks().empty());
    BOOST_CHECK(hl.todo_keyword().value().empty());
    BOOST_CHECK(hl.tags().empty());
}

BOOST_AUTO_TEST_CASE(headline_with_real_todo_no_title_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("headline_with_real_todo_no_title_document_in_expected_org_document");
    const auto document(make(headline_with_real_todo_no_title));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.section().blocks().empty());

    const auto& hls(document.headlines());
    BOOST_REQUIRE(hls.size() == 1);

    const auto& hl(hls.front());
    BOOST_CHECK(hl.headlines().empty());
    BOOST_CHECK(hl.title().empty());
    BOOST_CHECK(hl.priority().value().empty());
    BOOST_CHECK(hl.affiliated_keywords().empty());
    BOOST_CHECK(hl.drawers().empty());
    BOOST_CHECK(hl.section().blocks().empty());
    BOOST_CHECK(hl.todo_keyword().value() == "TODO");
    BOOST_CHECK(hl.tags().empty());
}

BOOST_AUTO_TEST_CASE(headline_with_fake_todo_no_title_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("headline_with_fake_todo_no_title_document_in_expected_org_document");
    const auto document(make(headline_with_fake_todo_no_title));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.section().blocks().empty());

    const auto& hls(document.headlines());
    BOOST_REQUIRE(hls.size() == 1);

    const auto& hl(hls.front());
    BOOST_CHECK(hl.headlines().empty());
    BOOST_CHECK(hl.title().empty());
    BOOST_CHECK(hl.priority().value().empty());
    BOOST_CHECK(hl.affiliated_keywords().empty());
    BOOST_CHECK(hl.drawers().empty());
    BOOST_CHECK(hl.section().blocks().empty());
    BOOST_CHECK(hl.todo_keyword().value() == "FAKE");
    BOOST_CHECK(hl.tags().empty());
}

BOOST_AUTO_TEST_CASE(headline_with_todo_keyword_and_single_word_title_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("headline_with_todo_keyword_and_single_word_title_document_in_expected_org_document");
    const auto document(make(headline_with_todo_keyword_and_single_word_title));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.section().blocks().empty());

    const auto& hls(document.headlines());
    BOOST_REQUIRE(hls.size() == 1);

    const auto& hl(hls.front());
    BOOST_CHECK(hl.headlines().empty());
    BOOST_CHECK(hl.title() == single_word_title);
    BOOST_CHECK(hl.priority().value().empty());
    BOOST_CHECK(hl.affiliated_keywords().empty());
    BOOST_CHECK(hl.drawers().empty());
    BOOST_CHECK(hl.section().blocks().empty());
    BOOST_CHECK(hl.todo_keyword().value() == "TODO");
    BOOST_CHECK(hl.tags().empty());
}

BOOST_AUTO_TEST_CASE(headline_with_todo_keyword_and_multi_word_title_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("headline_with_todo_keyword_and_multi_word_title_document_in_expected_org_document");
    const auto document(make(headline_with_todo_keyword_and_multi_word_title));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.section().blocks().empty());

    const auto& hls(document.headlines());
    BOOST_REQUIRE(hls.size() == 1);

    const auto& hl(hls.front());
    BOOST_CHECK(hl.headlines().empty());
    BOOST_CHECK(hl.title() == multi_word_title);
    BOOST_CHECK(hl.priority().value().empty());
    BOOST_CHECK(hl.affiliated_keywords().empty());
    BOOST_CHECK(hl.drawers().empty());
    BOOST_CHECK(hl.section().blocks().empty());
    BOOST_CHECK(hl.todo_keyword().value() == "TODO");
    BOOST_CHECK(hl.tags().empty());
}

BOOST_AUTO_TEST_CASE(headline_with_priority_todo_and_single_word_title_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("headline_with_priority_todo_and_single_word_title_document_in_expected_org_document");
    const auto document(make(headline_with_priority_todo_and_single_word_title));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.section().blocks().empty());

    const auto& hls(document.headlines());
    BOOST_REQUIRE(hls.size() == 1);

    const auto& hl(hls.front());
    BOOST_CHECK(hl.headlines().empty());
    BOOST_CHECK(hl.title() == single_word_title);
    BOOST_CHECK(hl.priority().value() == "[#I]");
    BOOST_CHECK(hl.affiliated_keywords().empty());
    BOOST_CHECK(hl.drawers().empty());
    BOOST_CHECK(hl.section().blocks().empty());
    BOOST_CHECK(hl.todo_keyword().value() == "DONE");
    BOOST_CHECK(hl.tags().empty());
}

BOOST_AUTO_TEST_CASE(headline_with_priority_todo_and_multi_word_title_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("headline_with_priority_todo_and_multi_word_title_document_in_expected_org_document");
    const auto document(make(headline_with_priority_todo_and_multi_word_title));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.section().blocks().empty());

    const auto& hls(document.headlines());
    BOOST_REQUIRE(hls.size() == 1);

    const auto& hl(hls.front());
    BOOST_CHECK(hl.headlines().empty());
    BOOST_CHECK(hl.title() == multi_word_title);
    BOOST_CHECK(hl.priority().value() == "[#I]");
    BOOST_CHECK(hl.affiliated_keywords().empty());
    BOOST_CHECK(hl.drawers().empty());
    BOOST_CHECK(hl.section().blocks().empty());
    BOOST_CHECK(hl.todo_keyword().value() == "DONE");
    BOOST_CHECK(hl.tags().empty());
}

BOOST_AUTO_TEST_CASE(headline_with_no_title_and_single_tag_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("headline_with_no_title_and_single_tag_document_in_expected_org_document");
    const auto document(make(headline_with_no_title_and_single_tag));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.section().blocks().empty());

    const auto& hls(document.headlines());
    BOOST_REQUIRE(hls.size() == 1);

    const auto& hl(hls.front());
    BOOST_CHECK(hl.headlines().empty());
    BOOST_CHECK(hl.title().empty());
    BOOST_CHECK(hl.priority().value().empty());
    BOOST_CHECK(hl.affiliated_keywords().empty());
    BOOST_CHECK(hl.drawers().empty());
    BOOST_CHECK(hl.section().blocks().empty());
    BOOST_CHECK(hl.todo_keyword().value().empty());

    const auto& tags(hl.tags());
    BOOST_REQUIRE(tags.size() == 1);
    BOOST_CHECK(tags.front().value() == "tag");
}

BOOST_AUTO_TEST_CASE(headline_with_no_title_and_multiple_tags_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("headline_with_no_title_and_multiple_tags_document_in_expected_org_document");
    const auto document(make(headline_with_no_title_and_multiple_tags));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.section().blocks().empty());

    const auto& hls(document.headlines());
    BOOST_REQUIRE(hls.size() == 1);

    const auto& hl(hls.front());
    BOOST_CHECK(hl.headlines().empty());
    BOOST_CHECK(hl.title().empty());
    BOOST_CHECK(hl.priority().value().empty());
    BOOST_CHECK(hl.affiliated_keywords().empty());
    BOOST_CHECK(hl.drawers().empty());
    BOOST_CHECK(hl.section().blocks().empty());
    BOOST_CHECK(hl.todo_keyword().value().empty());

    const auto& tags(hl.tags());
    BOOST_REQUIRE(tags.size() == 4);
    BOOST_CHECK(tags.front().value() == "tag");
    BOOST_CHECK(tags.back().value() == "d");
}

BOOST_AUTO_TEST_CASE(headline_with_single_word_title_and_single_tag_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("headline_with_single_word_title_and_single_tag_document_in_expected_org_document");
    const auto document(make(headline_with_single_word_title_and_single_tag));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.section().blocks().empty());

    const auto& hls(document.headlines());
    BOOST_REQUIRE(hls.size() == 1);

    const auto& hl(hls.front());
    BOOST_CHECK(hl.headlines().empty());
    BOOST_CHECK(hl.title() == single_word_title);
    BOOST_CHECK(hl.priority().value().empty());
    BOOST_CHECK(hl.affiliated_keywords().empty());
    BOOST_CHECK(hl.drawers().empty());
    BOOST_CHECK(hl.section().blocks().empty());
    BOOST_CHECK(hl.todo_keyword().value().empty());

    const auto& tags(hl.tags());
    BOOST_REQUIRE(tags.size() == 1);
    BOOST_CHECK(tags.front().value() == "tag");
}

BOOST_AUTO_TEST_CASE(headline_with_multi_word_title_and_single_tag_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("headline_with_multi_word_title_and_single_tag_document_in_expected_org_document");
    const auto document(make(headline_with_multi_word_title_and_single_tag));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.section().blocks().empty());

    const auto& hls(document.headlines());
    BOOST_REQUIRE(hls.size() == 1);

    const auto& hl(hls.front());
    BOOST_CHECK(hl.headlines().empty());
    BOOST_CHECK(hl.title() == multi_word_title);
    BOOST_CHECK(hl.priority().value().empty());
    BOOST_CHECK(hl.affiliated_keywords().empty());
    BOOST_CHECK(hl.drawers().empty());
    BOOST_CHECK(hl.section().blocks().empty());
    BOOST_CHECK(hl.todo_keyword().value().empty());

    const auto& tags(hl.tags());
    BOOST_REQUIRE(tags.size() == 1);
    BOOST_CHECK(tags.front().value() == "tag");
}

BOOST_AUTO_TEST_CASE(complete_headline_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("complete_headline_document_in_expected_org_document");
    const auto document(make(complete_headline));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.section().blocks().empty());

    const auto& hls(document.headlines());
    BOOST_REQUIRE(hls.size() == 1);

    const auto& hl(hls.front());
    BOOST_CHECK(hl.headlines().empty());
    BOOST_CHECK(hl.title() == multi_word_title);
    BOOST_CHECK(hl.priority().value() == "[#A]");
    BOOST_CHECK(hl.affiliated_keywords().empty());
    BOOST_CHECK(hl.drawers().empty());
    BOOST_CHECK(hl.section().blocks().empty());
    BOOST_CHECK(hl.todo_keyword().value() == "DONE");

    const auto& tags(hl.tags());
    BOOST_REQUIRE(tags.size() == 4);
    BOOST_CHECK(tags.front().value() == "tag");
    BOOST_CHECK(tags.back().value() == "d");
}

BOOST_AUTO_TEST_CASE(one_headline_with_content_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("one_headline_with_content_document_in_expected_org_document");
    const auto document(make(one_headline_with_content));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());

    const auto& blocks(document.section().blocks());
    BOOST_REQUIRE(!blocks.empty());

    const auto& c(blocks.front().contents());
    const std::string expected_doc(R"(some text content
other text content
)");
    BOOST_CHECK(c == expected_doc);

    const auto& hls(document.headlines());
    BOOST_REQUIRE(hls.size() == 1);

    const auto& hl(hls.front());
    BOOST_CHECK(hl.headlines().empty());
    BOOST_CHECK(hl.title() == "first headline");
    BOOST_CHECK(hl.priority().value().empty());
    BOOST_CHECK(hl.affiliated_keywords().empty());
    BOOST_CHECK(hl.drawers().empty());
    BOOST_CHECK(hl.todo_keyword().value().empty());
    BOOST_CHECK(hl.tags().empty());

    BOOST_REQUIRE(hl.section().blocks().size() == 1);
    const auto& cs(hl.section().blocks().front().contents());
    const std::string expected_sec(R"(
headline content
more headline content)");
    BOOST_CHECK(cs == expected_sec);
}

BOOST_AUTO_TEST_CASE(top_level_content_two_headlines_without_content_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("top_level_content_two_headlines_without_content_document_in_expected_org_document");
    const auto document(make(top_level_content_two_headlines_without_content));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());

    const auto& blocks(document.section().blocks());
    BOOST_REQUIRE(blocks.size() == 1);
    const auto& c(blocks.front().contents());
    const std::string expected_doc(R"(some text content
other text content
)");
    BOOST_CHECK(c == expected_doc);

    const auto& hls(document.headlines());
    BOOST_REQUIRE(hls.size() == 1);

    const auto& hl(hls.front());
    BOOST_CHECK(hl.title() == "first headline");
    BOOST_CHECK(hl.priority().value().empty());
    BOOST_CHECK(hl.affiliated_keywords().empty());
    BOOST_CHECK(hl.drawers().empty());
    BOOST_CHECK(hl.section().blocks().empty());
    BOOST_CHECK(hl.todo_keyword().value().empty());
    BOOST_CHECK(hl.tags().empty());

    BOOST_CHECK(hl.headlines().size() == 1);
    const auto& child(hl.headlines().front());
    BOOST_CHECK(child.title() == "second headline");
    BOOST_CHECK(child.priority().value().empty());
    BOOST_CHECK(child.affiliated_keywords().empty());
    BOOST_CHECK(child.drawers().empty());
    BOOST_CHECK(child.section().blocks().empty());
    BOOST_CHECK(child.todo_keyword().value().empty());
    BOOST_CHECK(child.tags().empty());
}


BOOST_AUTO_TEST_SUITE_END()
