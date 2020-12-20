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
#include "dogen.org/types/entities/drawer_type.hpp"
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

const std::string top_level_content_two_headlines_with_content(
    R"(some text content
other text content

* first headline

some content

** second headline

more content.

)");

const std::string complex_headline_structure(
    R"(some text content
other text content

* 1

some content

** 1.1

more content.

*** DONE [#A] 1.1.1 :tag:b:c:d:
** 1.2
* 2
** 2.1
* 3

some content
)");

const std::string simple_affiliated_keywords("#+title: some title");
const std::string multiple_affiliated_keywords(R"(#+title: some title
#+no_value:
#+with_value: 1234

some text content
other text content

)");

const std::string simple_empty_drawer(R"(:some_drawer:
:end:
)");

const std::string drawer_with_one_line(R"(:some_drawer:
some contents
:end:
)");

const std::string drawer_with_multiple_lines(R"(:some_drawer:
some contents
more contents
yet some more
:end:
)");

const std::string property_drawer_with_one_entry(R"(:PROPERTIES:
:key: a value
:END:
)");

const std::string property_drawer_with_multiple_entries(R"(:PROPERTIES:
:key0: a value
:key1: another value
:abc: v
:END:
)");

const std::string various_drawers_in_headlines(R"(#+title: some title
:PROPERTIES:
:key_0: value_0
:END:

some text content

* 1
:PROPERTIES:
:key_1: value_1
:END:

content

** 1.1
*** 1.1.1
:PROPERTIES:
:key_1_1_1: value_1_1_1
:END:

* 2
:PROPERTIES:
:key_2: value_2
:END:

contents
)");
dogen::org::entities::document
make(const std::string& s) {
    dogen::org::helpers::document_factory f;
    return f.make(s);
}

}

BOOST_AUTO_TEST_SUITE(document_factory_tests)

BOOST_AUTO_TEST_CASE(empty_string_results_in_empty_document) {
    SETUP_TEST_LOG_SOURCE("empty_string_results_in_empty_document");
    const auto document(make(empty));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.headlines().empty());
    BOOST_CHECK(document.section().blocks().empty());
}

BOOST_AUTO_TEST_CASE(single_line_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE("single_line_document_results_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("multi_line_document_results_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("multi_line_document_with_spurious_spaces_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("simple_headline_document_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("multi_word_headline_document_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("title_less_headline_document_results_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("title_less_headline_with_space_document_results_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("headline_with_priority_cookie_no_title_document_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("headline_with_priority_cookie_and_single_word_title_document_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("headline_with_priority_cookie_and_multi_word_title_document_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("headline_with_real_todo_no_title_document_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("headline_with_fake_todo_no_title_document_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("headline_with_todo_keyword_and_single_word_title_document_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("headline_with_todo_keyword_and_multi_word_title_document_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("headline_with_priority_todo_and_single_word_title_document_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("headline_with_priority_todo_and_multi_word_title_document_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("headline_with_no_title_and_single_tag_document_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("headline_with_no_title_and_multiple_tags_document_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("headline_with_single_word_title_and_single_tag_document_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("headline_with_multi_word_title_and_single_tag_document_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("complete_headline_document_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("one_headline_with_content_document_in_expected_org_document");
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
    SETUP_TEST_LOG_SOURCE("top_level_content_two_headlines_without_content_document_in_expected_org_document");
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

BOOST_AUTO_TEST_CASE(top_level_content_two_headlines_with_content_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE("top_level_content_two_headlines_with_content_document_in_expected_org_document");
    const auto document(make(top_level_content_two_headlines_with_content));

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
    BOOST_CHECK(hl.todo_keyword().value().empty());
    BOOST_CHECK(hl.tags().empty());

    BOOST_REQUIRE(hl.section().blocks().size() == 1);
    const auto& cs(hl.section().blocks().front().contents());
    const std::string expected_sec(R"(
some content
)");
    BOOST_CHECK(cs == expected_sec);

    BOOST_CHECK(hl.headlines().size() == 1);
    const auto& child(hl.headlines().front());
    BOOST_CHECK(child.title() == "second headline");
    BOOST_CHECK(child.priority().value().empty());
    BOOST_CHECK(child.affiliated_keywords().empty());
    BOOST_CHECK(child.drawers().empty());
    BOOST_CHECK(child.todo_keyword().value().empty());
    BOOST_CHECK(child.tags().empty());

    BOOST_REQUIRE(child.section().blocks().size() == 1);
    const auto& ccs(child.section().blocks().front().contents());
    const std::string expected_child_sec(R"(
more content.
)");
    BOOST_CHECK(ccs == expected_child_sec);
}

BOOST_AUTO_TEST_CASE(complex_headline_structure_document_results_in_expected_org_document) {
    SETUP_TEST_LOG_SOURCE("complex_headline_structure_document_in_expected_org_document");
    const auto document(make(complex_headline_structure));

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
    BOOST_REQUIRE(hls.size() == 3);

    const auto& front(hls.front());
    BOOST_REQUIRE(front.headlines().size() == 2);
    BOOST_REQUIRE(front.headlines().front().headlines().size() == 1);
    BOOST_CHECK(front.headlines().front().title() == "1.1");
    BOOST_REQUIRE(front.headlines().front().headlines().size() == 1);

    const auto& grand_child(front.headlines().front().headlines().front());
    BOOST_CHECK(grand_child.headlines().empty());
    BOOST_CHECK(grand_child.title() == "1.1.1");
    BOOST_CHECK(grand_child.priority().value() == "[#A]");
    BOOST_CHECK(grand_child.todo_keyword().value() == "DONE");

    const auto& tags(grand_child.tags());
    BOOST_REQUIRE(tags.size() == 4);
    BOOST_CHECK(tags.front().value() == "tag");
    BOOST_CHECK(tags.back().value() == "d");

    BOOST_CHECK(front.headlines().back().headlines().empty());
    BOOST_CHECK(front.headlines().back().title() == "1.2");
    BOOST_CHECK(front.title() == "1");
    BOOST_CHECK(front.priority().value().empty());
    BOOST_CHECK(front.affiliated_keywords().empty());
    BOOST_CHECK(front.drawers().empty());
    BOOST_CHECK(front.todo_keyword().value().empty());
    BOOST_CHECK(front.tags().empty());

    BOOST_REQUIRE(front.section().blocks().size() == 1);
    const auto& cs(front.section().blocks().front().contents());
    const std::string expected_sec(R"(
some content
)");
    BOOST_CHECK(cs == expected_sec);

    const auto& middle(*(++hls.begin()));
    BOOST_CHECK(middle.title() == "2");
    BOOST_CHECK(middle.headlines().front().headlines().empty());
    BOOST_CHECK(middle.priority().value().empty());
    BOOST_CHECK(middle.affiliated_keywords().empty());
    BOOST_CHECK(middle.drawers().empty());
    BOOST_CHECK(middle.todo_keyword().value().empty());
    BOOST_CHECK(middle.tags().empty());
    BOOST_CHECK(middle.section().blocks().empty());

    const auto& back(hls.back());
    BOOST_CHECK(back.title() == "3");
    BOOST_CHECK(back.headlines().empty());
    BOOST_CHECK(back.priority().value().empty());
    BOOST_CHECK(back.affiliated_keywords().empty());
    BOOST_CHECK(back.drawers().empty());
    BOOST_CHECK(back.todo_keyword().value().empty());
    BOOST_CHECK(back.tags().empty());

    BOOST_REQUIRE(back.section().blocks().size() == 1);
    const auto& bc(back.section().blocks().back().contents());
    const std::string expected_back_sec(R"(
some content)");
    BOOST_CHECK(bc == expected_back_sec);
}

BOOST_AUTO_TEST_CASE(simple_affiliated_keywords_document_results_in_expected_document) {
    SETUP_TEST_LOG_SOURCE("simple_affiliated_keywords_document_results_in_expected_document");
    const auto document(make(simple_affiliated_keywords));

    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.headlines().empty());
    BOOST_CHECK(document.section().blocks().empty());

    BOOST_REQUIRE(document.affiliated_keywords().size() == 1);
    const auto& ak(document.affiliated_keywords().front());
    BOOST_CHECK(ak.key() == "title");
    BOOST_CHECK(ak.value() == "some title");
}

BOOST_AUTO_TEST_CASE(multiple_affiliated_keywords_document_results_in_expected_document) {
    SETUP_TEST_LOG_SOURCE("multiple_affiliated_keywords_document_results_in_expected_document");
    const auto document(make(multiple_affiliated_keywords));

    BOOST_CHECK(document.drawers().empty());
    BOOST_CHECK(document.headlines().empty());

    BOOST_REQUIRE(document.affiliated_keywords().size() == 2);
    const auto& front(document.affiliated_keywords().front());
    BOOST_CHECK(front.key() == "title");
    BOOST_CHECK(front.value() == "some title");

    const auto& back(document.affiliated_keywords().back());
    BOOST_CHECK(back.key() == "with_value");
    BOOST_CHECK(back.value() == "1234");

    BOOST_REQUIRE(document.section().blocks().size() == 2);

    /*
     * Key without a value is not recognised as an affiliated keyword.
     */
    const auto& front_block(document.section().blocks().front().contents());
    BOOST_CHECK(front_block == "#+no_value:");

    const auto& back_block(document.section().blocks().back().contents());
    const std::string expected_sec(R"(
some text content
other text content
)");
    BOOST_CHECK(expected_sec == back_block);
}

BOOST_AUTO_TEST_CASE(simple_empty_drawer_results_in_expected_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("simple_empty_drawer_results_in_expected_document");
    const auto document(make(simple_empty_drawer));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.headlines().empty());
    BOOST_CHECK(document.section().blocks().empty());

    BOOST_REQUIRE(document.drawers().size() == 1);
    const auto& drawer(document.drawers().back());
    BOOST_CHECK(drawer.name() == "some_drawer");
    BOOST_CHECK(drawer.contents().empty());

    using dogen::org::entities::drawer_type;
    BOOST_CHECK(drawer.type() == drawer_type::regular);
}

BOOST_AUTO_TEST_CASE(drawer_with_one_line_results_in_expected_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("drawer_with_one_line_results_in_expected_document");
    const auto document(make(drawer_with_one_line));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.headlines().empty());
    BOOST_CHECK(document.section().blocks().empty());

    BOOST_REQUIRE(document.drawers().size() == 1);
    const auto& drawer(document.drawers().back());
    BOOST_CHECK(drawer.name() == "some_drawer");
    BOOST_REQUIRE(drawer.contents().size() == 1);

    const auto& contents(drawer.contents().front());
    BOOST_CHECK(contents.key().empty());
    BOOST_CHECK(contents.value() == "some contents");

    using dogen::org::entities::drawer_type;
    BOOST_CHECK(drawer.type() == drawer_type::regular);
}

BOOST_AUTO_TEST_CASE(drawer_with_multiple_lines_results_in_expected_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("drawer_with_multiple_lines_results_in_expected_document");
    const auto document(make(drawer_with_multiple_lines));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.headlines().empty());
    BOOST_CHECK(document.section().blocks().empty());

    BOOST_REQUIRE(document.drawers().size() == 1);
    const auto& drawer(document.drawers().back());
    BOOST_CHECK(drawer.name() == "some_drawer");

    BOOST_REQUIRE(drawer.contents().size() == 3);
    const auto& front(drawer.contents().front());
    BOOST_CHECK(front.key().empty());
    BOOST_CHECK(front.value() == "some contents");

    const auto& back(drawer.contents().back());
    BOOST_CHECK(back.key().empty());
    BOOST_CHECK(back.value() == "yet some more");

    using dogen::org::entities::drawer_type;
    BOOST_CHECK(drawer.type() == drawer_type::regular);
}

BOOST_AUTO_TEST_CASE(property_drawer_with_one_entry_results_in_expected_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("property_drawer_with_one_entry_results_in_expected_document");
    const auto document(make(property_drawer_with_one_entry));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.headlines().empty());
    BOOST_CHECK(document.section().blocks().empty());

    BOOST_REQUIRE(document.drawers().size() == 1);
    const auto& drawer(document.drawers().back());
    BOOST_CHECK(drawer.name() == "PROPERTIES");

    BOOST_REQUIRE(drawer.contents().size() == 1);
    const auto& front(drawer.contents().front());
    BOOST_CHECK(front.key() == "key");
    BOOST_CHECK(front.value() == "a value");

    using dogen::org::entities::drawer_type;
    BOOST_CHECK(drawer.type() == drawer_type::property_drawer);
}

BOOST_AUTO_TEST_CASE(property_drawer_with_multiple_entries_results_in_expected_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("property_drawer_with_multiple_entries_results_in_expected_document");
    const auto document(make(property_drawer_with_multiple_entries));

    BOOST_CHECK(document.affiliated_keywords().empty());
    BOOST_CHECK(document.headlines().empty());
    BOOST_CHECK(document.section().blocks().empty());

    BOOST_REQUIRE(document.drawers().size() == 1);
    const auto& drawer(document.drawers().back());
    BOOST_CHECK(drawer.name() == "PROPERTIES");

    BOOST_REQUIRE(drawer.contents().size() == 3);
    const auto& front(drawer.contents().front());
    BOOST_CHECK(front.key() == "key0");
    BOOST_CHECK(front.value() == "a value");

    const auto& back(drawer.contents().back());
    BOOST_CHECK(back.key() == "abc");
    BOOST_CHECK(back.value() == "v");

    using dogen::org::entities::drawer_type;
    BOOST_CHECK(drawer.type() == drawer_type::property_drawer);
}

BOOST_AUTO_TEST_CASE(various_drawers_in_headlines_results_in_expected_document) {
    SETUP_TEST_LOG_SOURCE_DEBUG("various_drawers_in_headlines_results_in_expected_document");
    const auto document(make(various_drawers_in_headlines));

    /*
     * Validate top-level.
     */
    BOOST_REQUIRE(document.affiliated_keywords().size() == 1);
    const auto& ak(document.affiliated_keywords().front());
    BOOST_CHECK(ak.key() == "title");
    BOOST_CHECK(ak.value() == "some title");

    const auto& document_blocks(document.section().blocks());
    BOOST_REQUIRE(document_blocks.size() == 1);

    const auto& document_content(document_blocks.front().contents());
    const auto expected_document_content(R"(
some text content
)");
    BOOST_CHECK(document_content == expected_document_content);

    BOOST_REQUIRE(document.drawers().size() == 1);
    const auto& document_drawer(document.drawers().back());
    BOOST_CHECK(document_drawer.name() == "PROPERTIES");

    BOOST_REQUIRE(document_drawer.contents().size() == 1);
    const auto& front(document_drawer.contents().front());
    BOOST_CHECK(front.key() == "key_0");
    BOOST_CHECK(front.value() == "value_0");

    using dogen::org::entities::drawer_type;
    BOOST_CHECK(document_drawer.type() == drawer_type::property_drawer);
    BOOST_REQUIRE(document.headlines().size() == 2);

    /*
     * Validate headline 1.
     */
    const auto h1(document.headlines().front());
    BOOST_CHECK(h1.title() == "1");

    const auto& h1_blocks(h1.section().blocks());
    BOOST_REQUIRE(h1_blocks.size() == 1);

    const auto& h1_content(h1_blocks.front().contents());
    const auto expected_h1_content(R"(
content
)");
    BOOST_CHECK(h1_content == expected_h1_content);

    /*
     * Validate headline 1.1.
     */
    BOOST_REQUIRE(h1.headlines().size() == 1);
    const auto& h1_1(h1.headlines().front());
    BOOST_CHECK(h1_1.title() == "1.1");
    BOOST_CHECK(h1_1.section().blocks().empty());
    BOOST_REQUIRE(h1_1.drawers().empty());

    /*
     * Validate headline 1.1.1.
     */
    BOOST_REQUIRE(h1_1.headlines().size() == 1);
    const auto& h1_1_1(h1_1.headlines().front());
    BOOST_CHECK(h1_1_1.title() == "1.1.1");
    BOOST_REQUIRE(h1_1_1.headlines().empty());
    BOOST_REQUIRE(h1_1_1.drawers().size() == 1);

    const auto& h1_1_1_drawer(h1_1_1.drawers().back());
    BOOST_CHECK(h1_1_1_drawer.name() == "PROPERTIES");

    BOOST_REQUIRE(h1_1_1_drawer.contents().size() == 1);
    const auto& h1_1_1_front(h1_1_1_drawer.contents().front());
    BOOST_CHECK(h1_1_1_front.key() == "key_1_1_1");
    BOOST_CHECK(h1_1_1_front.value() == "value_1_1_1");

    using dogen::org::entities::drawer_type;
    BOOST_CHECK(h1_1_1_drawer.type() == drawer_type::property_drawer);
}

BOOST_AUTO_TEST_SUITE_END()
