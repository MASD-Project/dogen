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
#include <sstream>
#include <boost/test/unit_test.hpp>
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/test/asserter.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.identification/types/helpers/logical_name_factory.hpp"
#include "dogen.identification/types/helpers/parsing_error.hpp"
#include "dogen.identification/io/entities/logical_name_tree_io.hpp"
#include "dogen.identification/io/entities/logical_name_io.hpp"
#include "dogen.identification/types/helpers/legacy_logical_name_tree_parser.hpp"
#include "dogen.utility/types/test/exception_checkers.hpp"

using dogen::utility::test::asserter;
using dogen::identification::entities::logical_name_tree;
using dogen::identification::helpers::legacy_logical_name_tree_parser;
using dogen::identification::helpers::logical_name_factory;

namespace  {

const std::string empty;
const std::string test_module("dogen.logical.tests");
const std::string test_suite("legacy_logical_name_tree_parser_tests");

const auto cpp(dogen::identification::entities::technical_space::cpp);

logical_name_tree make(const dogen::identification::entities::logical_name& n) {
    logical_name_tree r;
    r.current(n);
    return r;
}

bool test_builtin(const std::string& s) {
    legacy_logical_name_tree_parser ntp(cpp);
    const auto a(ntp.parse(s));

    logical_name_factory nf;
    const auto e(make(nf.build_element_name(s)));
    return asserter::assert_equals(e, a);
}

}

using dogen::identification::helpers::parsing_error;

BOOST_AUTO_TEST_SUITE(legacy_logical_name_tree_parser_tests)

BOOST_AUTO_TEST_CASE(parsing_string_with_many_nested_scopes_produces_expected_name) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_many_nested_scopes_produces_expected_name");
    const std::string s("a::b::c::z");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    legacy_logical_name_tree_parser ntp(cpp);
    const auto a(ntp.parse(s));

    logical_name_factory nf;
    const auto e(make(nf.build_element_name("z", { "a", "b", "c"})));

    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_string_without_scope_operator_produces_expected_name) {
    SETUP_TEST_LOG_SOURCE("parsing_string_without_scope_operator_produces_expected_name");
    const std::string s("zeta");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    legacy_logical_name_tree_parser ntp(cpp);
    const auto a(ntp.parse(s));

    logical_name_factory nf;
    const auto e(make(nf.build_element_name(s)));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_string_with_one_scope_operator_produces_expected_name) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_one_scope_operator_produces_expected_name");
    const std::string s("a::z");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    legacy_logical_name_tree_parser ntp(cpp);
    const auto a(ntp.parse(s));

    logical_name_factory nf;
    const auto e(make(nf.build_element_name("z",
                std::list<std::string>({ "a" }))));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_string_with_single_colon_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_single_colon_fails_to_parse");
    const std::string s("a:z");
    BOOST_LOG_SEV(lg, info) << "input: " << s;
    legacy_logical_name_tree_parser ntp(cpp);
    BOOST_CHECK_THROW(ntp.parse(s), parsing_error);
}

BOOST_AUTO_TEST_CASE(string_starting_with_digit_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("string_starting_with_digit_fails_to_parse");
    const std::string s("0a");
    BOOST_LOG_SEV(lg, info) << "input: " << s;
    legacy_logical_name_tree_parser ntp(cpp);
    BOOST_CHECK_THROW(ntp.parse(s), parsing_error);
}

BOOST_AUTO_TEST_CASE(string_ending_with_scope_operator_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("string_ending_with_scope_operator_fails_to_parse");
    const std::string s("a::");
    BOOST_LOG_SEV(lg, info) << "input: " << s;
    legacy_logical_name_tree_parser ntp(cpp);
    BOOST_CHECK_THROW(ntp.parse(s), parsing_error);
}

BOOST_AUTO_TEST_CASE(scope_operator_followed_by_scope_operator_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("scope_operator_followed_by_scope_operator_fails_to_parse");
    const std::string s("A::::");
    BOOST_LOG_SEV(lg, info) << "input: " << s;
    legacy_logical_name_tree_parser ntp(cpp);
    BOOST_CHECK_THROW(ntp.parse(s), parsing_error);
}

BOOST_AUTO_TEST_CASE(all_builtin_types_are_valid) {
    SETUP_TEST_LOG("all_builtin_types_are_valid");

    BOOST_CHECK(test_builtin("char"));
    BOOST_CHECK(test_builtin("unsigned char"));
    BOOST_CHECK(test_builtin("wchar_t"));
    BOOST_CHECK(test_builtin("unsigned wchar_t"));
    BOOST_CHECK(test_builtin("bool"));
    BOOST_CHECK(test_builtin("short"));
    BOOST_CHECK(test_builtin("unsigned short"));
    BOOST_CHECK(test_builtin("int"));
    BOOST_CHECK(test_builtin("unsigned int"));
    BOOST_CHECK(test_builtin("long"));
    BOOST_CHECK(test_builtin("unsigned long"));
    BOOST_CHECK(test_builtin("long long"));
    BOOST_CHECK(test_builtin("unsigned long long"));
    BOOST_CHECK(test_builtin("void"));
    BOOST_CHECK(test_builtin("float"));
    BOOST_CHECK(test_builtin("double"));
}

BOOST_AUTO_TEST_CASE(unsignable_types_cannot_be_unsigned) {
    SETUP_TEST_LOG("unsignable_types_cannot_be_unsigned");
    legacy_logical_name_tree_parser ntp(cpp);
    BOOST_CHECK_THROW(ntp.parse("unsigned bool"), parsing_error);
    BOOST_CHECK_THROW(ntp.parse("unsigned x"), parsing_error);
    BOOST_CHECK_THROW(ntp.parse("unsigned float"), parsing_error);
    BOOST_CHECK_THROW(ntp.parse("unsigned double"), parsing_error);
}

BOOST_AUTO_TEST_CASE(parsing_string_with_single_template_argument_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_single_template_argument_produces_expected_name_trees");

    logical_name_tree e;
    logical_name_factory nf;
    e.current(nf.build_element_name("type"));

    logical_name_tree c;
    c.current(nf.build_element_name("abc"));

    e.children(std::list<logical_name_tree> { c });

    const std::string s("type<abc>");
    legacy_logical_name_tree_parser ntp(cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_string_with_two_template_argument_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_two_template_argument_produces_expected_name_trees");

    logical_name_tree e;
    logical_name_factory nf;
    e.current(nf.build_element_name("type"));

    logical_name_tree c;
    c.current(nf.build_element_name("abc"));

    logical_name_tree d;
    d.current(nf.build_element_name("cde"));

    e.children(std::list<logical_name_tree> { c, d });

    const std::string s("type<abc,cde>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    legacy_logical_name_tree_parser ntp(cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_vector_of_string_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_vector_of_string_produces_expected_name_trees");
    logical_name_tree e;
    logical_name_factory nf;
    e.current(nf.build_element_name("vector",
            std::list<std::string>({ "std" })));

    logical_name_tree c;
    c.current(nf.build_element_name("string",
            std::list<std::string>({ "std" })));
    e.children(std::list<logical_name_tree> { c });

    const std::string s("std::vector<std::string>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    legacy_logical_name_tree_parser ntp(cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_vector_of_builtin_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_vector_of_builtin_produces_expected_name_trees");

    logical_name_tree e;
    logical_name_factory nf;
    e.current(nf.build_element_name("vector",
            std::list<std::string>({ "std" })));

    logical_name_tree c;
    c.current(nf.build_element_name("unsigned int"));

    e.children(std::list<logical_name_tree> { c });

    const std::string s("std::vector<unsigned int>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    legacy_logical_name_tree_parser ntp(cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_unordered_map_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_unordered_map_produces_expected_name_trees");

    logical_name_tree e;
    logical_name_factory nf;
    e.current(nf.build_element_name("unordered_map",
            std::list<std::string>({ "std" })));

    logical_name_tree c;
    c.current(nf.build_element_name("string",
            std::list<std::string>({ "std" })));

    logical_name_tree d;
    d.current(nf.build_element_name("type",
            std::list<std::string>({ "my" })));

    e.children(std::list<logical_name_tree> { c, d });

    const std::string s1("std::unordered_map<std::string,my::type>");
    BOOST_LOG_SEV(lg, info) << "input: " << s1;

    legacy_logical_name_tree_parser ntp(cpp);
    const auto a1(ntp.parse(s1));
    BOOST_CHECK(asserter::assert_equals(e, a1));

    const std::string s2("std::unordered_map<std::string,    my::type>");
    BOOST_LOG_SEV(lg, info) << "input: " << s2;

    const auto a2(ntp.parse(s2));
    BOOST_CHECK(asserter::assert_equals(e, a2));
}

BOOST_AUTO_TEST_CASE(parsing_vector_of_shared_ptr_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_vector_of_shared_ptr_produces_expected_name_trees");

    logical_name_tree e;
    logical_name_factory nf;
    e.current(nf.build_element_name("vector",
            std::list<std::string>({ "std" })));

    logical_name_tree c;
    c.current(nf.build_element_name("shared_ptr",
            std::list<std::string>({ "std" })));

    logical_name_tree d;
    d.current(nf.build_element_name("string",
            std::list<std::string>({ "std" })));

    c.children(std::list<logical_name_tree> { d });
    e.children(std::list<logical_name_tree> { c });

    const std::string s("std::vector<std::shared_ptr<std::string>>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    legacy_logical_name_tree_parser ntp(cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(names_that_partially_match_builtins_produce_expected_name_tree) {
    SETUP_TEST_LOG("names_that_partially_match_builtins_produce_expected_name_tree");

    BOOST_CHECK(test_builtin("character"));
    BOOST_CHECK(test_builtin("cha"));
    BOOST_CHECK(test_builtin("wchar_test"));
    BOOST_CHECK(test_builtin("wcha"));
    BOOST_CHECK(test_builtin("boolean"));
    BOOST_CHECK(test_builtin("boo"));
    BOOST_CHECK(test_builtin("shorter"));
    BOOST_CHECK(test_builtin("shor"));
    BOOST_CHECK(test_builtin("integer"));
    BOOST_CHECK(test_builtin("in"));
    BOOST_CHECK(test_builtin("voidest"));
    BOOST_CHECK(test_builtin("voi"));
    BOOST_CHECK(test_builtin("floating"));
    BOOST_CHECK(test_builtin("floa"));
    BOOST_CHECK(test_builtin("doubler"));
    BOOST_CHECK(test_builtin("doubl"));
    BOOST_CHECK(test_builtin("unsigneder"));
    BOOST_CHECK(test_builtin("longer"));
}

BOOST_AUTO_TEST_SUITE_END()
