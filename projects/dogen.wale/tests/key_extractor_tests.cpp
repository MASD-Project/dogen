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
#include "dogen.utility/test/logging.hpp"
#include "dogen.utility/io/unordered_set_io.hpp"
#include "dogen.wale/types/key_extractor.hpp"

namespace {

const std::string test_module("wale");
const std::string test_suite("key_extractor_tests");

const std::string no_keys_0;
const std::string no_keys_1("this is a string");
const std::string no_keys_2("this is a string { { } }");
const std::string no_keys_3("this is a string } }");
const std::string no_keys_4("this is a string { {");

const std::string one("one");
const std::string one_key_0("{{one}}");
const std::string one_key_1("this is a string {{one}}");
const std::string one_key_2("{{one}}this is a string ");

const std::string two("two");
const std::string two_keys_0("{{one}}{{two}}");
const std::string two_keys_1("{{one}}   {{two}}");
const std::string two_keys_2("this is a string {{one}}  {{two}}");
const std::string two_keys_3("{{one}}  {{two}} this is a string ");

const std::string three("three");
const std::string four("four");
const std::string five("five");
const std::string many_keys_0("{{one}}{{two}}{{three}}{{four}}{{five}}");
const std::string many_keys_1(
    "{{one}}       {{two}}  {{three}}  {{four}}  {{five}}");


const std::string many_keys_multi_line_0(R"(<#+
{{one}}
{{two}}
{{three}}
{{four}}
{{five}}
#>)");

const std::string many_keys_multi_line_1(R"(<#+
{{one}}
aaaaaa{{two}}bbbbbbb
ccc{{three}}dddd
eeeeee{{four}}eeeeee
fff{{five}}fff
#>)");


const std::string valid_key_with_numbers("k1234");
const std::string valid_key_0("{{k1234}}");

const std::string valid_key_with_underscores("kabc_def");
const std::string valid_key_1("{{kabc_def}}");

const std::string valid_key_with_dot("kabc.def");
const std::string valid_key_2("{{kabc.def}}");

const std::string at_key("k@abc");
const std::string invalid_key_0("{{k@abc}}");

const std::string number_key("k@abc");
const std::string invalid_key_1("{{123abc}}");

}

BOOST_AUTO_TEST_SUITE(key_extractor_tests)

BOOST_AUTO_TEST_CASE(string_with_no_keys_results_in_no_extracted_keys) {
    SETUP_TEST_LOG_SOURCE("string_with_no_keys_results_in_no_extracted_keys");

    dogen::wale::key_extractor ke;
    BOOST_LOG_SEV(lg, debug) << "input 0: " << no_keys_0;
    const auto a0(ke.extract(no_keys_0));
    BOOST_LOG_SEV(lg, debug) << "result 0: " << a0;
    BOOST_CHECK(a0.empty());

    BOOST_LOG_SEV(lg, debug) << "input 1: " << no_keys_1;
    const auto a1(ke.extract(no_keys_1));
    BOOST_LOG_SEV(lg, debug) << "Result 1: " << a1;
    BOOST_CHECK(a1.empty());

    BOOST_LOG_SEV(lg, debug) << "input 2: " << no_keys_2;
    const auto a2(ke.extract(no_keys_2));
    BOOST_LOG_SEV(lg, debug) << "Result 2: " << a2;
    BOOST_CHECK(a2.empty());

    BOOST_LOG_SEV(lg, debug) << "input 3: " << no_keys_3;
    const auto a3(ke.extract(no_keys_3));
    BOOST_LOG_SEV(lg, debug) << "Result 3: " << a3;
    BOOST_CHECK(a3.empty());

    BOOST_LOG_SEV(lg, debug) << "input 4: " << no_keys_4;
    const auto a4(ke.extract(no_keys_4));
    BOOST_LOG_SEV(lg, debug) << "Result 4: " << a4;
    BOOST_CHECK(a4.empty());
}

BOOST_AUTO_TEST_CASE(string_with_one_key_results_in_one_extracted_key) {
    SETUP_TEST_LOG_SOURCE("string_with_one_key_results_in_one_extracted_key");

    dogen::wale::key_extractor ke;
    BOOST_LOG_SEV(lg, debug) << "input 0: " << one_key_0;
    const auto a0(ke.extract(one_key_0));
    BOOST_LOG_SEV(lg, debug) << "result 0: " << a0;
    BOOST_CHECK(a0.size() == 1);
    BOOST_CHECK(a0.find(one) != a0.end());

    BOOST_LOG_SEV(lg, debug) << "input 1: " << one_key_1;
    const auto a1(ke.extract(one_key_1));
    BOOST_LOG_SEV(lg, debug) << "result: " << a1;
    BOOST_CHECK(a1.size() == 1);
    BOOST_CHECK(a1.find(one) != a1.end());

    BOOST_LOG_SEV(lg, debug) << "input 2: " << one_key_2;
    const auto a2(ke.extract(one_key_2));
    BOOST_LOG_SEV(lg, debug) << "result: " << a2;
    BOOST_CHECK(a2.size() == 1);
    BOOST_CHECK(a2.find(one) != a2.end());
}

BOOST_AUTO_TEST_CASE(string_with_two_keys_results_in_two_extracted_keys) {
    SETUP_TEST_LOG_SOURCE("string_with_two_keys_results_in_two_extracted_keys");

    dogen::wale::key_extractor ke;
    BOOST_LOG_SEV(lg, debug) << "input 0: " << two_keys_0;
    const auto a0(ke.extract(two_keys_0));
    BOOST_LOG_SEV(lg, debug) << "result 0: " << a0;
    BOOST_CHECK(a0.size() == 2);
    BOOST_CHECK(a0.find(one) != a0.end());
    BOOST_CHECK(a0.find(two) != a0.end());

    BOOST_LOG_SEV(lg, debug) << "input 1: " << two_keys_1;
    const auto a1(ke.extract(two_keys_1));
    BOOST_LOG_SEV(lg, debug) << "result: " << a1;
    BOOST_CHECK(a1.size() == 2);
    BOOST_CHECK(a1.find(one) != a1.end());
    BOOST_CHECK(a1.find(two) != a1.end());

    BOOST_LOG_SEV(lg, debug) << "input 2: " << two_keys_2;
    const auto a2(ke.extract(two_keys_2));
    BOOST_LOG_SEV(lg, debug) << "result: " << a2;
    BOOST_CHECK(a2.size() == 2);
    BOOST_CHECK(a2.find(one) != a2.end());
    BOOST_CHECK(a2.find(two) != a2.end());

    BOOST_LOG_SEV(lg, debug) << "input 3: " << two_keys_3;
    const auto a3(ke.extract(two_keys_3));
    BOOST_LOG_SEV(lg, debug) << "result: " << a3;
    BOOST_CHECK(a3.size() == 2);
    BOOST_CHECK(a3.find(one) != a3.end());
    BOOST_CHECK(a3.find(two) != a3.end());
}

BOOST_AUTO_TEST_CASE(string_with_many_keys_results_in_expected_extracted_keys) {
    SETUP_TEST_LOG_SOURCE("string_with_many_keys_results_in_expected_extracted_keys");

    dogen::wale::key_extractor ke;
    BOOST_LOG_SEV(lg, debug) << "input 0: " << many_keys_0;
    const auto a0(ke.extract(many_keys_0));
    BOOST_LOG_SEV(lg, debug) << "result 0: " << a0;
    BOOST_CHECK(a0.size() == 5);
    BOOST_CHECK(a0.find(one) != a0.end());
    BOOST_CHECK(a0.find(two) != a0.end());
    BOOST_CHECK(a0.find(three) != a0.end());
    BOOST_CHECK(a0.find(four) != a0.end());
    BOOST_CHECK(a0.find(five) != a0.end());

    BOOST_LOG_SEV(lg, debug) << "input 1: " << many_keys_1;
    const auto a1(ke.extract(many_keys_1));
    BOOST_LOG_SEV(lg, debug) << "result: " << a1;
    BOOST_CHECK(a1.size() == 5);
    BOOST_CHECK(a1.find(one) != a1.end());
    BOOST_CHECK(a1.find(two) != a1.end());
    BOOST_CHECK(a1.find(three) != a1.end());
    BOOST_CHECK(a1.find(four) != a1.end());
    BOOST_CHECK(a1.find(five) != a1.end());

    BOOST_LOG_SEV(lg, debug) << "input 2: " << many_keys_multi_line_0;
    const auto a2(ke.extract(many_keys_multi_line_0));
    BOOST_LOG_SEV(lg, debug) << "result: " << a2;
    BOOST_CHECK(a2.size() == 5);
    BOOST_CHECK(a2.find(one) != a2.end());
    BOOST_CHECK(a2.find(two) != a2.end());
    BOOST_CHECK(a2.find(three) != a2.end());
    BOOST_CHECK(a2.find(four) != a2.end());
    BOOST_CHECK(a2.find(five) != a2.end());

    BOOST_LOG_SEV(lg, debug) << "input 3: " << many_keys_multi_line_1;
    const auto a3(ke.extract(many_keys_multi_line_1));
    BOOST_LOG_SEV(lg, debug) << "result: " << a3;
    BOOST_CHECK(a3.size() == 5);
    BOOST_CHECK(a3.find(one) != a3.end());
    BOOST_CHECK(a3.find(two) != a3.end());
    BOOST_CHECK(a3.find(three) != a3.end());
    BOOST_CHECK(a3.find(four) != a3.end());
    BOOST_CHECK(a3.find(five) != a3.end());
}

BOOST_AUTO_TEST_CASE(valid_keys_result_in_expected_extracted_keys) {
    SETUP_TEST_LOG_SOURCE("valid_keys_result_in_expected_extracted_keys");

    dogen::wale::key_extractor ke;
    BOOST_LOG_SEV(lg, debug) << "input 0: " << valid_key_0;
    const auto a0(ke.extract(valid_key_0));
    BOOST_LOG_SEV(lg, debug) << "result 0: " << a0;
    BOOST_CHECK(a0.size() == 1);
    BOOST_CHECK(a0.find(valid_key_with_numbers) != a0.end());

    BOOST_LOG_SEV(lg, debug) << "input 1: " << valid_key_1;
    const auto a1(ke.extract(valid_key_1));
    BOOST_LOG_SEV(lg, debug) << "result 1: " << a1;
    BOOST_CHECK(a1.size() == 1);
    BOOST_CHECK(a1.find(valid_key_with_underscores) != a1.end());

    BOOST_LOG_SEV(lg, debug) << "input21: " << valid_key_2;
    const auto a2(ke.extract(valid_key_2));
    BOOST_LOG_SEV(lg, debug) << "result 1: " << a2;
    BOOST_CHECK(a2.size() == 1);
    BOOST_CHECK(a2.find(valid_key_with_dot) != a2.end());
}

BOOST_AUTO_TEST_SUITE_END()
