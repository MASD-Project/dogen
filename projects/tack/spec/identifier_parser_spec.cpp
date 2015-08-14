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
#include "dogen/utility/io/list_io.hpp"
#include "dogen/tack/types/model.hpp"
#include "dogen/tack/types/parsing_error.hpp"
#include "dogen/tack/io/nested_name_io.hpp"
#include "dogen/tack/io/name_io.hpp"
#include "dogen/tack/types/merging_error.hpp"
#include "dogen/tack/types/identifier_parser.hpp"
#include "dogen/tack/types/merger.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using dogen::utility::test::asserter;

namespace  {

const std::string empty;
const std::string test_module("tack");
const std::string test_suite("identifier_parser_spec");

bool test_primitive(const std::string& s) {
    dogen::tack::identifier_parser ip;
    const auto a(ip.parse_name(s));

    dogen::tack::nested_name nn;
    dogen::tack::name e;
    e.simple(s);
    nn.type(e);
    return asserter::assert_equals(nn, a);
}

}

using dogen::tack::parsing_error;

BOOST_AUTO_TEST_SUITE(identifier_parser)

BOOST_AUTO_TEST_CASE(parsing_string_with_many_nested_scopes_produces_expected_name) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_many_nested_scopes_produces_expected_name");
    const std::string s("a::b::c::z");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::tack::identifier_parser ip;
    const auto a(ip.parse_name(s));

    dogen::tack::nested_name nn;
    dogen::tack::name e;
    e.simple("z");
    e.location().internal_module_path(std::list<std::string> { "b", "c"});
    e.location().original_model_name("a");
    nn.type(e);
    BOOST_CHECK(asserter::assert_equals(nn, a));
}

BOOST_AUTO_TEST_CASE(parsing_string_without_scope_operator_produces_expected_name) {
    SETUP_TEST_LOG_SOURCE("parsing_string_without_scope_operator_produces_expected_name");
    const std::string s("zeta");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::tack::identifier_parser ip;
    const auto a(ip.parse_name(s));

    dogen::tack::nested_name nn;
    dogen::tack::name e;
    e.simple("zeta");
    nn.type(e);
    BOOST_CHECK(asserter::assert_equals(nn, a));
}

BOOST_AUTO_TEST_CASE(parsing_string_with_one_scope_operator_produces_expected_name) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_one_scope_operator_produces_expected_name");
    const std::string s("a::z");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::tack::identifier_parser ip;
    const auto a(ip.parse_name(s));

    dogen::tack::nested_name nn;
    dogen::tack::name e;
    e.location().original_model_name("a");
    e.simple("z");
    nn.type(e);
    BOOST_CHECK(asserter::assert_equals(nn, a));
}

BOOST_AUTO_TEST_CASE(parsing_string_with_single_colon_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_single_colon_fails_to_parse");
    const std::string s("a:z");
    BOOST_LOG_SEV(lg, info) << "input: " << s;
    dogen::tack::identifier_parser ip;
    BOOST_CHECK_THROW(ip.parse_name(s), parsing_error);
}

BOOST_AUTO_TEST_CASE(string_starting_with_digit_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("string_starting_with_digit_fails_to_parse");
    const std::string s("0a");
    BOOST_LOG_SEV(lg, info) << "input: " << s;
    dogen::tack::identifier_parser ip;
    BOOST_CHECK_THROW(ip.parse_name(s), parsing_error);
}

BOOST_AUTO_TEST_CASE(string_ending_with_scope_operator_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("string_ending_with_scope_operator_fails_to_parse");
    const std::string s("a::");
    BOOST_LOG_SEV(lg, info) << "input: " << s;
    dogen::tack::identifier_parser ip;
    BOOST_CHECK_THROW(ip.parse_name(s), parsing_error);
}

BOOST_AUTO_TEST_CASE(scope_operator_followed_by_scope_operator_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("scope_operator_followed_by_scope_operator_fails_to_parse");
    const std::string s("A::::");
    BOOST_LOG_SEV(lg, info) << "input: " << s;
    dogen::tack::identifier_parser ip;
    BOOST_CHECK_THROW(ip.parse_name(s), parsing_error);
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
    dogen::tack::identifier_parser ip;
    BOOST_CHECK_THROW(ip.parse_name("unsigned bool"), parsing_error);
    BOOST_CHECK_THROW(ip.parse_name("unsigned x"), parsing_error);
    BOOST_CHECK_THROW(ip.parse_name("unsigned float"), parsing_error);
    BOOST_CHECK_THROW(ip.parse_name("unsigned double"), parsing_error);
}

BOOST_AUTO_TEST_CASE(parsing_string_with_single_template_argument_produces_expected_nested_names) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_single_template_argument_produces_expected_nested_names");

    dogen::tack::identifier_parser ip;
    dogen::tack::nested_name nn;
    dogen::tack::name e;
    e.simple("type");
    nn.type(e);

    dogen::tack::name f;
    f.simple("abc");
    dogen::tack::nested_name c;
    c.type(f);
    nn.children(std::list<dogen::tack::nested_name> { c });

    const auto a(ip.parse_name("type<abc>"));
    BOOST_CHECK(asserter::assert_equals(nn, a));
}

BOOST_AUTO_TEST_CASE(parsing_string_with_two_template_argument_produces_expected_nested_names) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_two_template_argument_produces_expected_nested_names");
    dogen::tack::identifier_parser ip;
    dogen::tack::nested_name nn;
    dogen::tack::name e;
    e.simple("type");
    nn.type(e);

    dogen::tack::name f;
    f.simple("abc");
    dogen::tack::nested_name c;
    c.type(f);

    dogen::tack::name g;
    g.simple("cde");
    dogen::tack::nested_name d;
    d.type(g);
    nn.children(std::list<dogen::tack::nested_name> { c, d });

    const std::string s("type<abc,cde>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    const auto a(ip.parse_name(s));
    BOOST_CHECK(asserter::assert_equals(nn, a));
}

BOOST_AUTO_TEST_CASE(parsing_vector_of_string_produces_expected_nested_names) {
    SETUP_TEST_LOG_SOURCE("parsing_vector_of_string_produces_expected_nested_names");
    dogen::tack::identifier_parser ip;
    dogen::tack::nested_name nn;
    dogen::tack::name e;
    e.simple("vector");
    e.location().original_model_name("std");
    nn.type(e);

    dogen::tack::name f;
    f.simple("string");
    f.location().original_model_name("std");
    dogen::tack::nested_name c;
    c.type(f);
    nn.children(std::list<dogen::tack::nested_name> { c });

    const std::string s("std::vector<std::string>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    const auto a(ip.parse_name(s));
    BOOST_CHECK(asserter::assert_equals(nn, a));
}

BOOST_AUTO_TEST_CASE(parsing_vector_of_primitive_produces_expected_nested_names) {
    SETUP_TEST_LOG_SOURCE("parsing_vector_of_primitive_produces_expected_nested_names");
    dogen::tack::identifier_parser ip;
    dogen::tack::nested_name nn;
    dogen::tack::name e;
    e.simple("vector");
    e.location().original_model_name("std");
    nn.type(e);

    dogen::tack::name f;
    f.simple("unsigned int");
    dogen::tack::nested_name c;
    c.type(f);
    nn.children(std::list<dogen::tack::nested_name> { c });

    const std::string s("std::vector<unsigned int>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    const auto a(ip.parse_name(s));
    BOOST_CHECK(asserter::assert_equals(nn, a));
}

BOOST_AUTO_TEST_CASE(parsing_unordered_map_produces_expected_nested_names) {
    SETUP_TEST_LOG_SOURCE("parsing_unordered_map_produces_expected_nested_names");
    dogen::tack::identifier_parser ip;
    dogen::tack::nested_name nn;
    dogen::tack::name e;
    e.simple("unordered_map");
    e.location().original_model_name("std");
    nn.type(e);

    dogen::tack::name f;
    f.simple("string");
    f.location().original_model_name("std");
    dogen::tack::nested_name c;
    c.type(f);
    dogen::tack::name g;
    g.simple("type");
    g.location().original_model_name("my");
    dogen::tack::nested_name d;
    d.type(g);

    nn.children(std::list<dogen::tack::nested_name> { c, d });

    const std::string s1("std::unordered_map<std::string,my::type>");
    BOOST_LOG_SEV(lg, info) << "input: " << s1;
    const auto a1(ip.parse_name(s1));
    BOOST_CHECK(asserter::assert_equals(nn, a1));

    const std::string s2("std::unordered_map<std::string,    my::type>");
    BOOST_LOG_SEV(lg, info) << "input: " << s2;
    const auto a2(ip.parse_name(s2));
    BOOST_CHECK(asserter::assert_equals(nn, a2));
}

BOOST_AUTO_TEST_CASE(parsing_vector_of_shared_ptr_produces_expected_nested_names) {
    SETUP_TEST_LOG_SOURCE("parsing_vector_of_shared_ptr_produces_expected_nested_names");
    dogen::tack::identifier_parser ip;
    dogen::tack::nested_name nn;
    dogen::tack::name e;
    e.simple("vector");
    e.location().original_model_name("std");
    nn.type(e);

    dogen::tack::name f;
    f.simple("shared_ptr");
    f.location().original_model_name("std");
    dogen::tack::nested_name c;
    c.type(f);

    dogen::tack::name g;
    g.simple("string");
    g.location().original_model_name("std");
    dogen::tack::nested_name d;
    d.type(g);
    c.children(std::list<dogen::tack::nested_name> { d });
    nn.children(std::list<dogen::tack::nested_name> { c });

    const std::string s("std::vector<std::shared_ptr<std::string>>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    const auto a(ip.parse_name(s));
    BOOST_CHECK(asserter::assert_equals(nn, a));
}

BOOST_AUTO_TEST_CASE(names_that_partially_match_primitives_produce_expected_nested_name) {
    SETUP_TEST_LOG("names_that_partially_match_primitives_produce_expected_nested_name");

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
