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
#include "masd.dogen.utility/types/test/logging.hpp"
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.utility/types/test/exception_checkers.hpp"
#include "masd.dogen.utility/types/string/splitter.hpp"

namespace {

const std::string empty;
const std::string test_module("masd.dogen.utility.tests");
const std::string test_suite("splitter_tests");

const std::string mixed_scopes("String has more than one");

}

using masd::dogen::utility::test::contains_checker;

BOOST_AUTO_TEST_SUITE(splitter_tests)

BOOST_AUTO_TEST_CASE(parsing_scoped_string_with_no_scope_operators_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("parsing_scoped_string_with_no_scope_operators_produces_expected_result");

    const std::string i("value");
    BOOST_LOG_SEV(lg, info) << "input: " << i;

    using masd::dogen::utility::string::splitter;
    const auto a(splitter::split_scoped(i));
    BOOST_REQUIRE(a.size() == 1);
    BOOST_CHECK(a.front() == i);
}

BOOST_AUTO_TEST_CASE(parsing_scoped_string_with_many_scope_operators_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("parsing_scoped_string_with_many_scope_operators_produces_expected_result");

    const std::string i("a::b::c::d");
    BOOST_LOG_SEV(lg, info) << "input: " << i;

    using masd::dogen::utility::string::splitter;
    auto a(splitter::split_scoped(i));
    BOOST_LOG_SEV(lg, info) << "actual: " << a;

    BOOST_REQUIRE(a.size() == 4);
    BOOST_CHECK(a.front() == "a");
    a.pop_front();

    BOOST_CHECK(a.front() == "b");
    a.pop_front();

    BOOST_CHECK(a.front() == "c");
    a.pop_front();

    BOOST_CHECK(a.front() == "d");
}

BOOST_AUTO_TEST_CASE(parsing_empty_scoped_string_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("parsing_empty_scoped_string_produces_expected_result");

    BOOST_LOG_SEV(lg, info) << "input: " << empty;

    using masd::dogen::utility::string::splitter;
    const auto a(splitter::split_scoped(empty));
    BOOST_LOG_SEV(lg, info) << "actual: " << a;
    BOOST_REQUIRE(a.empty());
}

BOOST_AUTO_TEST_CASE(parsing_scoped_string_with_only_scope_operators_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("parsing_scoped_string_with_only_scope_operators_produces_expected_result");

    const std::string i("::::");
    BOOST_LOG_SEV(lg, info) << "input: " << i;

    using masd::dogen::utility::string::splitter;
    auto a(splitter::split_scoped(i));
    BOOST_LOG_SEV(lg, info) << "actual: " << a;
    BOOST_REQUIRE(a.empty());
}

BOOST_AUTO_TEST_CASE(parsing_scoped_string_with_dots_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("parsing_scoped_string_with_dots_produces_expected_result");

    const std::string i("a.b");
    BOOST_LOG_SEV(lg, info) << "input: " << i;

    using masd::dogen::utility::string::splitter;
    const auto a(splitter::split_scoped(i));
    BOOST_LOG_SEV(lg, info) << "actual: " << a;

    BOOST_CHECK(a.front() == "a");
    BOOST_CHECK(a.back() == "b");
}

BOOST_AUTO_TEST_CASE(parsing_string_with_mixed_scope_operators_throws) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_mixed_scope_operators_throws");

    const std::string i("a.b:c");
    BOOST_LOG_SEV(lg, info) << "input: " << i;

    using masd::dogen::utility::string::splitting_error;
    contains_checker<splitting_error> c(mixed_scopes);

    using masd::dogen::utility::string::splitter;
    BOOST_CHECK_EXCEPTION(splitter::split_scoped(i), splitting_error, c);
}

BOOST_AUTO_TEST_CASE(parsing_csv_string_with_no_commas_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("parsing_csv_string_with_no_commas_produces_expected_result");

    const std::string i("value");
    using masd::dogen::utility::string::splitter;
    const auto a(splitter::split_csv(i));

    BOOST_LOG_SEV(lg, info) << "actual: " << a;
    BOOST_REQUIRE(a.size() == 1);
    BOOST_CHECK(a.front() == i);
}

BOOST_AUTO_TEST_CASE(parsing_csv_string_with_many_commas_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("parsing_csv_string_with_many_commas_produces_expected_result");

    const std::string i("a,b,c,d");
    BOOST_LOG_SEV(lg, info) << "input: " << i;

    using masd::dogen::utility::string::splitter;
    auto a(splitter::split_csv(i));
    BOOST_LOG_SEV(lg, info) << "actual: " << a;

    BOOST_REQUIRE(a.size() == 4);
    BOOST_CHECK(a.front() == "a");
    a.pop_front();

    BOOST_CHECK(a.front() == "b");
    a.pop_front();

    BOOST_CHECK(a.front() == "c");
    a.pop_front();

    BOOST_CHECK(a.front() == "d");
}

BOOST_AUTO_TEST_CASE(parsing_empty_csv_string_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("parsing_empty_csv_string_produces_expected_result");

    BOOST_LOG_SEV(lg, info) << "input: " << empty;

    using masd::dogen::utility::string::splitter;
    const auto a(splitter::split_csv(empty));
    BOOST_LOG_SEV(lg, info) << "actual: " << a;
    BOOST_REQUIRE(a.empty());
}

BOOST_AUTO_TEST_CASE(parsing_csv_string_with_only_commas_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("parsing_csv_string_with_only_commas_produces_expected_result");

    const std::string i(",,");
    BOOST_LOG_SEV(lg, info) << "input: " << i;

    using masd::dogen::utility::string::splitter;
    auto a(splitter::split_csv(i));
    BOOST_LOG_SEV(lg, info) << "actual: " << a;
    BOOST_REQUIRE(a.empty());
}

BOOST_AUTO_TEST_CASE(parsing_csv_string_with_spaces_produces_expected_result) {
    SETUP_TEST_LOG_SOURCE("parsing_csv_string_with_spaces_produces_expected_result");

    const std::string i(" a, b, c ,d,   e,f   ");
    BOOST_LOG_SEV(lg, info) << "input: " << i;

    using masd::dogen::utility::string::splitter;
    auto a(splitter::split_csv(i));
    BOOST_LOG_SEV(lg, info) << "actual: " << a;

    BOOST_REQUIRE(a.size() == 6);
    BOOST_CHECK(a.front() == "a");
    a.pop_front();

    BOOST_CHECK(a.front() == "b");
    a.pop_front();

    BOOST_CHECK(a.front() == "c");
    a.pop_front();

    BOOST_CHECK(a.front() == "d");
    a.pop_front();

    BOOST_CHECK(a.front() == "e");
    a.pop_front();

    BOOST_CHECK(a.front() == "f");
    a.pop_front();
}

BOOST_AUTO_TEST_SUITE_END()
