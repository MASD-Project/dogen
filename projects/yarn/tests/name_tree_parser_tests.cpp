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
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/yarn/types/name_builder.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/parsing_error.hpp"
#include "dogen/yarn/io/name_tree_io.hpp"
#include "dogen/yarn/io/name_io.hpp"
#include "dogen/yarn/types/merging_error.hpp"
#include "dogen/yarn/types/name_tree_parser.hpp"
#include "dogen/yarn/types/merger.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using dogen::utility::test::asserter;

namespace  {

const std::string empty;
const std::string test_module("yarn");
const std::string test_suite("name_tree_parser_tests");

const dogen::yarn::languages cpp(dogen::yarn::languages::cpp);

const auto top_level_modules = std::unordered_set<std::string>();
const auto model_location = dogen::yarn::location();

dogen::yarn::
name_tree make(const dogen::yarn::name& n) {
    dogen::yarn::name_tree r;
    r.current(n);
    return r;
}

bool test_primitive(const std::string& s) {
    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));

    dogen::yarn::name_factory nf;
    const auto e(make(nf.build_element_name(s)));
    return asserter::assert_equals(e, a);
}

}

using dogen::yarn::parsing_error;

BOOST_AUTO_TEST_SUITE(name_tree_parser_tests)

BOOST_AUTO_TEST_CASE(parsing_string_with_many_nested_scopes_produces_expected_name) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_many_nested_scopes_produces_expected_name");
    const std::string s("a::b::c::z");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));

    dogen::yarn::name_builder b;
    b.simple_name("z");
    b.model_name("a");
    b.internal_modules(std::list<std::string> { "b", "c"});
    const auto e(make(b.build()));

    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_string_without_scope_operator_produces_expected_name) {
    SETUP_TEST_LOG_SOURCE("parsing_string_without_scope_operator_produces_expected_name");
    const std::string s("zeta");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));

    dogen::yarn::name_factory nf;
    const auto e(make(nf.build_element_name(s)));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_string_with_one_scope_operator_produces_expected_name) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_one_scope_operator_produces_expected_name");
    const std::string s("a::z");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));

    dogen::yarn::name_factory nf;
    const auto e(make(nf.build_element_name("a", "z")));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_string_with_single_colon_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_single_colon_fails_to_parse");
    const std::string s("a:z");
    BOOST_LOG_SEV(lg, info) << "input: " << s;
    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    BOOST_CHECK_THROW(ntp.parse(s), parsing_error);
}

BOOST_AUTO_TEST_CASE(string_starting_with_digit_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("string_starting_with_digit_fails_to_parse");
    const std::string s("0a");
    BOOST_LOG_SEV(lg, info) << "input: " << s;
    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    BOOST_CHECK_THROW(ntp.parse(s), parsing_error);
}

BOOST_AUTO_TEST_CASE(string_ending_with_scope_operator_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("string_ending_with_scope_operator_fails_to_parse");
    const std::string s("a::");
    BOOST_LOG_SEV(lg, info) << "input: " << s;
    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    BOOST_CHECK_THROW(ntp.parse(s), parsing_error);
}

BOOST_AUTO_TEST_CASE(scope_operator_followed_by_scope_operator_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("scope_operator_followed_by_scope_operator_fails_to_parse");
    const std::string s("A::::");
    BOOST_LOG_SEV(lg, info) << "input: " << s;
    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    BOOST_CHECK_THROW(ntp.parse(s), parsing_error);
}

BOOST_AUTO_TEST_CASE(all_primitive_types_are_valid) {
    SETUP_TEST_LOG("all_primitive_types_are_valid");

    BOOST_CHECK(test_primitive("char"));
    BOOST_CHECK(test_primitive("unsigned char"));
    BOOST_CHECK(test_primitive("wchar_t"));
    BOOST_CHECK(test_primitive("unsigned wchar_t"));
    BOOST_CHECK(test_primitive("bool"));
    BOOST_CHECK(test_primitive("short"));
    BOOST_CHECK(test_primitive("unsigned short"));
    BOOST_CHECK(test_primitive("int"));
    BOOST_CHECK(test_primitive("unsigned int"));
    BOOST_CHECK(test_primitive("long"));
    BOOST_CHECK(test_primitive("unsigned long"));
    BOOST_CHECK(test_primitive("long long"));
    BOOST_CHECK(test_primitive("unsigned long long"));
    BOOST_CHECK(test_primitive("void"));
    BOOST_CHECK(test_primitive("float"));
    BOOST_CHECK(test_primitive("double"));
}

BOOST_AUTO_TEST_CASE(unsignable_types_cannot_be_unsigned) {
    SETUP_TEST_LOG("unsignable_types_cannot_be_unsigned");
    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    BOOST_CHECK_THROW(ntp.parse("unsigned bool"), parsing_error);
    BOOST_CHECK_THROW(ntp.parse("unsigned x"), parsing_error);
    BOOST_CHECK_THROW(ntp.parse("unsigned float"), parsing_error);
    BOOST_CHECK_THROW(ntp.parse("unsigned double"), parsing_error);
}

BOOST_AUTO_TEST_CASE(parsing_string_with_single_template_argument_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_single_template_argument_produces_expected_name_trees");

    dogen::yarn::name_tree e;
    dogen::yarn::name_factory nf;
    e.current(nf.build_element_name("type"));

    dogen::yarn::name_tree c;
    c.current(nf.build_element_name("abc"));

    e.children(std::list<dogen::yarn::name_tree> { c });

    const std::string s("type<abc>");
    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_string_with_two_template_argument_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_two_template_argument_produces_expected_name_trees");

    dogen::yarn::name_tree e;
    dogen::yarn::name_factory nf;
    e.current(nf.build_element_name("type"));

    dogen::yarn::name_tree c;
    c.current(nf.build_element_name("abc"));

    dogen::yarn::name_tree d;
    d.current(nf.build_element_name("cde"));

    e.children(std::list<dogen::yarn::name_tree> { c, d });

    const std::string s("type<abc,cde>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_vector_of_string_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_vector_of_string_produces_expected_name_trees");
    dogen::yarn::name_tree e;
    dogen::yarn::name_factory nf;
    e.current(nf.build_element_name("std", "vector"));

    dogen::yarn::name_tree c;
    c.current(nf.build_element_name("std", "string"));

    e.children(std::list<dogen::yarn::name_tree> { c });

    const std::string s("std::vector<std::string>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_vector_of_primitive_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_vector_of_primitive_produces_expected_name_trees");

    dogen::yarn::name_tree e;
    dogen::yarn::name_factory nf;
    e.current(nf.build_element_name("std", "vector"));

    dogen::yarn::name_tree c;
    c.current(nf.build_element_name("unsigned int"));

    e.children(std::list<dogen::yarn::name_tree> { c });

    const std::string s("std::vector<unsigned int>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(parsing_unordered_map_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_unordered_map_produces_expected_name_trees");

    dogen::yarn::name_tree e;

    dogen::yarn::name_factory nf;
    e.current(nf.build_element_name("std", "unordered_map"));

    dogen::yarn::name_tree c;
    c.current(nf.build_element_name("std", "string"));

    dogen::yarn::name_tree d;
    d.current(nf.build_element_name("my", "type"));

    e.children(std::list<dogen::yarn::name_tree> { c, d });

    const std::string s1("std::unordered_map<std::string,my::type>");
    BOOST_LOG_SEV(lg, info) << "input: " << s1;

    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a1(ntp.parse(s1));
    BOOST_CHECK(asserter::assert_equals(e, a1));

    const std::string s2("std::unordered_map<std::string,    my::type>");
    BOOST_LOG_SEV(lg, info) << "input: " << s2;

    const auto a2(ntp.parse(s2));
    BOOST_CHECK(asserter::assert_equals(e, a2));
}

BOOST_AUTO_TEST_CASE(parsing_vector_of_shared_ptr_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_vector_of_shared_ptr_produces_expected_name_trees");

    dogen::yarn::name_tree e;
    dogen::yarn::name_factory nf;
    e.current(nf.build_element_name("std", "vector"));

    dogen::yarn::name_tree c;
    c.current(nf.build_element_name("std", "shared_ptr"));

    dogen::yarn::name_tree d;
    d.current(nf.build_element_name("std", "string"));

    c.children(std::list<dogen::yarn::name_tree> { d });
    e.children(std::list<dogen::yarn::name_tree> { c });

    const std::string s("std::vector<std::shared_ptr<std::string>>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::yarn::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(names_that_partially_match_primitives_produce_expected_name_tree) {
    SETUP_TEST_LOG("names_that_partially_match_primitives_produce_expected_name_tree");

    BOOST_CHECK(test_primitive("character"));
    BOOST_CHECK(test_primitive("cha"));
    BOOST_CHECK(test_primitive("wchar_test"));
    BOOST_CHECK(test_primitive("wcha"));
    BOOST_CHECK(test_primitive("boolean"));
    BOOST_CHECK(test_primitive("boo"));
    BOOST_CHECK(test_primitive("shorter"));
    BOOST_CHECK(test_primitive("shor"));
    BOOST_CHECK(test_primitive("integer"));
    BOOST_CHECK(test_primitive("in"));
    BOOST_CHECK(test_primitive("voidest"));
    BOOST_CHECK(test_primitive("voi"));
    BOOST_CHECK(test_primitive("floating"));
    BOOST_CHECK(test_primitive("floa"));
    BOOST_CHECK(test_primitive("doubler"));
    BOOST_CHECK(test_primitive("doubl"));
}

BOOST_AUTO_TEST_SUITE_END()
