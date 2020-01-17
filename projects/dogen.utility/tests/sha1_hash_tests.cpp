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
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/test/asserter.hpp"
#include "dogen.utility/types/hash/sha1_hash.hpp"

namespace {

const std::string test_module("dogen.utility.tests");
const std::string test_suite("sha1_hash_tests");

const std::string empty;
const std::string trivial_non_empty_string(
    "Converts a model from one codec to another.");
const std::string expected_trivial_hash(
    "1f45006cda88569c1d44559db1aef695b30d8817");
const std::string expected_empty_hash(
    "da39a3ee5e6b4b0d3255bfef95601890afd80709");

const std::string multi_line_input(R"({
    "documentation" : "a_doc",
    "stereotypes" : [ "some stereotype", "another" ]
}
)");

const std::string expected_multi_line_hash(
    "96ae703f494cea38e849d2b87b03df13cc7efbf9");

}

using dogen::utility::test::asserter;
using dogen::utility::hash::sha1_hash;

BOOST_AUTO_TEST_SUITE(sha1_hash_tests)

BOOST_AUTO_TEST_CASE(computing_the_hash_of_a_trivial_non_empty_string_produces_the_exepcted_result) {
    SETUP_TEST_LOG_SOURCE("computing_the_hash_of_a_trivial_non_empty_string_produces_the_exepcted_result");

    // $ echo -n "Converts a model from one codec to another." | sha1sum
    //    1f45006cda88569c1d44559db1aef695b30d8817  -
    BOOST_LOG_SEV(lg, info) << "input: '" << trivial_non_empty_string << "'";
    const auto actual(sha1_hash(trivial_non_empty_string));
    BOOST_CHECK(asserter::assert_object(expected_trivial_hash, actual));
}

BOOST_AUTO_TEST_CASE(computing_the_hash_of_an_empty_string_produces_the_exepcted_result) {
    SETUP_TEST_LOG_SOURCE("computing_the_hash_of_an_empty_string_produces_the_exepcted_result");

    // $ touch crap.log && sha1sum crap.log
    //    1f45006cda88569c1d44559db1aef695b30d8817  -
    BOOST_LOG_SEV(lg, info) << "input: '" << empty << "'";
    const auto actual(sha1_hash(empty));
    BOOST_CHECK(asserter::assert_object(expected_empty_hash, actual));
}

BOOST_AUTO_TEST_CASE(computing_the_hash_of_a_multi_line_string_produces_the_exepcted_result) {
    SETUP_TEST_LOG_SOURCE("computing_the_hash_of_a_multi_line_string_produces_the_exepcted_result");

    // $ touch crap.log && sha1sum crap.log
    //    1f45006cda88569c1d44559db1aef695b30d8817  -
    BOOST_LOG_SEV(lg, info) << "input: '" << multi_line_input << "'";
    const auto actual(sha1_hash(multi_line_input));
    BOOST_CHECK(asserter::assert_object(expected_multi_line_hash, actual));
}

BOOST_AUTO_TEST_SUITE_END()
