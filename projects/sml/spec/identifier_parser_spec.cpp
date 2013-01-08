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
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/parsing_error.hpp"
#include "dogen/sml/io/nested_qualified_name_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/types/merging_error.hpp"
#include "dogen/sml/types/identifier_parser.hpp"
#include "dogen/sml/types/merger.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

using dogen::utility::test::asserter;

namespace  {

const std::string empty;
const std::string test_module("sml");
const std::string test_suite("identifier_parser_spec");

bool test_primitive(const std::string& s) {
    dogen::sml::identifier_parser ip;
    const auto a(ip.parse_qualified_name(s));

    dogen::sml::nested_qualified_name nqn;
    dogen::sml::qname e;
    e.type_name(s);
    nqn.type(e);
    return asserter::assert_equals(nqn, a);
}

}

using dogen::sml::parsing_error;

BOOST_AUTO_TEST_SUITE(identifier_parser)

BOOST_AUTO_TEST_CASE(parsing_string_with_inner_namespaces_produces_expected_qualified_name) {
    SETUP_TEST_LOG("parsing_string_with_inner_namespaces_produces_expected_qualified_name");
    const std::string s("a::b::c::z");
    dogen::sml::identifier_parser ip;
    const auto a(ip.parse_qualified_name(s));

    dogen::sml::nested_qualified_name nqn;
    dogen::sml::qname e;
    e.type_name("z");
    e.package_path(std::list<std::string> { "b", "c"});
    e.model_name("a");
    nqn.type(e);
    BOOST_CHECK(asserter::assert_equals(nqn, a));
}

BOOST_AUTO_TEST_CASE(parsing_string_with_scope_operator_produces_expected_qualified_name) {
    SETUP_TEST_LOG("parsing_string_with_scope_operator_produces_expected_qualified_name");
    const std::string s("zeta");
    dogen::sml::identifier_parser ip;
    const auto a(ip.parse_qualified_name(s));

    dogen::sml::nested_qualified_name nqn;
    dogen::sml::qname e;
    e.type_name("zeta");
    nqn.type(e);
    BOOST_CHECK(asserter::assert_equals(nqn, a));
}

BOOST_AUTO_TEST_CASE(parsing_string_with_one_colon_produces_expected_qualified_name) {
    SETUP_TEST_LOG("parsing_string_with_one_colon_produces_expected_qualified_name");
    const std::string s("a::z");
    dogen::sml::identifier_parser ip;
    const auto a(ip.parse_qualified_name(s));

    dogen::sml::nested_qualified_name nqn;
    dogen::sml::qname e;
    e.model_name("a");
    e.type_name("z");
    nqn.type(e);
    BOOST_CHECK(asserter::assert_equals(nqn, a));
}

BOOST_AUTO_TEST_CASE(string_starting_with_digit_fails_to_parse) {
    SETUP_TEST_LOG("string_starting_with_digit_fails_to_parse");
    const std::string s("0a");
    dogen::sml::identifier_parser ip;
    BOOST_CHECK_THROW(ip.parse_qualified_name(s), parsing_error);
}

BOOST_AUTO_TEST_CASE(string_ending_with_scope_operator_fails_to_parse) {
    SETUP_TEST_LOG("string_ending_with_scope_operator_fails_to_parse");
    const std::string s("a::");
    dogen::sml::identifier_parser ip;
    BOOST_CHECK_THROW(ip.parse_qualified_name(s), parsing_error);
}

BOOST_AUTO_TEST_CASE(scope_operator_followed_by_scope_operator_fails_to_parse) {
    SETUP_TEST_LOG("scope_operator_followed_by_scope_operator_fails_to_parse");
    const std::string s("A::::");
    dogen::sml::identifier_parser ip;
    BOOST_CHECK_THROW(ip.parse_qualified_name(s), parsing_error);
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
    dogen::sml::identifier_parser ip;
    BOOST_CHECK_THROW(ip.parse_qualified_name("unsigned bool"), parsing_error);
    BOOST_CHECK_THROW(ip.parse_qualified_name("unsigned x"), parsing_error);
    BOOST_CHECK_THROW(ip.parse_qualified_name("unsigned float"), parsing_error);
    BOOST_CHECK_THROW(ip.parse_qualified_name("unsigned double"), parsing_error);
}

BOOST_AUTO_TEST_CASE(parsing_string_with_single_template_argument_produces_expected_nested_qualified_names) {
    SETUP_TEST_LOG("parsing_string_with_single_template_argument_produces_expected_nested_qualified_names");
    dogen::sml::identifier_parser ip;
    dogen::sml::nested_qualified_name nqn;
    dogen::sml::qname e;
    e.type_name("type");
    nqn.type(e);

    dogen::sml::qname f;
    f.type_name("abc");
    dogen::sml::nested_qualified_name c;
    c.type(f);
    nqn.children(std::list<dogen::sml::nested_qualified_name> { c });

    const auto a(ip.parse_qualified_name("type<abc>"));
    BOOST_CHECK(asserter::assert_equals(nqn, a));

    ip.parse_qualified_name("type<abc,cde>");
    ip.parse_qualified_name("std::vector<std::string>");
    ip.parse_qualified_name("std::vector<unsigned int>");
    ip.parse_qualified_name("std::unordered_map<std::string,my::type>");
    ip.parse_qualified_name("std::vector<std::shared_ptr<std::string>>");
}

BOOST_AUTO_TEST_CASE(parsing_string_with_two_template_argument_produces_expected_nested_qualified_names) {
    SETUP_TEST_LOG("parsing_string_with_two_template_argument_produces_expected_nested_qualified_names");
    dogen::sml::identifier_parser ip;
    dogen::sml::nested_qualified_name nqn;
    dogen::sml::qname e;
    e.type_name("type");
    nqn.type(e);

    dogen::sml::qname f;
    f.type_name("abc");
    dogen::sml::nested_qualified_name c;
    c.type(f);

    dogen::sml::qname g;
    g.type_name("cde");
    dogen::sml::nested_qualified_name d;
    d.type(g);
    nqn.children(std::list<dogen::sml::nested_qualified_name> { c, d });

    const auto a(ip.parse_qualified_name("type<abc,cde>"));
    BOOST_CHECK(asserter::assert_equals(nqn, a));
}

BOOST_AUTO_TEST_CASE(parsing_vector_of_string_produces_expected_nested_qualified_names) {
    SETUP_TEST_LOG("parsing_vector_of_string_produces_expected_nested_qualified_names");
    dogen::sml::identifier_parser ip;
    dogen::sml::nested_qualified_name nqn;
    dogen::sml::qname e;
    e.type_name("vector");
    e.model_name("std");
    nqn.type(e);

    dogen::sml::qname f;
    f.type_name("string");
    f.model_name("std");
    dogen::sml::nested_qualified_name c;
    c.type(f);
    nqn.children(std::list<dogen::sml::nested_qualified_name> { c });

    const auto a(ip.parse_qualified_name("std::vector<std::string>"));
    BOOST_CHECK(asserter::assert_equals(nqn, a));
}

BOOST_AUTO_TEST_CASE(parsing_vector_of_primitive_produces_expected_nested_qualified_names) {
    SETUP_TEST_LOG("parsing_vector_of_primitive_produces_expected_nested_qualified_names");
    dogen::sml::identifier_parser ip;
    dogen::sml::nested_qualified_name nqn;
    dogen::sml::qname e;
    e.type_name("vector");
    e.model_name("std");
    nqn.type(e);

    dogen::sml::qname f;
    f.type_name("unsigned int");
    dogen::sml::nested_qualified_name c;
    c.type(f);
    nqn.children(std::list<dogen::sml::nested_qualified_name> { c });

    const auto a(ip.parse_qualified_name("std::vector<unsigned int>"));
    BOOST_CHECK(asserter::assert_equals(nqn, a));
}

BOOST_AUTO_TEST_CASE(parsing_unordered_map_produces_expected_nested_qualified_names) {
    SETUP_TEST_LOG("parsing_unordered_map_produces_expected_nested_qualified_names");
    dogen::sml::identifier_parser ip;
    dogen::sml::nested_qualified_name nqn;
    dogen::sml::qname e;
    e.type_name("unordered_map");
    e.model_name("std");
    nqn.type(e);

    dogen::sml::qname f;
    f.type_name("string");
    f.model_name("std");
    dogen::sml::nested_qualified_name c;
    c.type(f);
    dogen::sml::qname g;
    g.type_name("type");
    g.model_name("my");
    dogen::sml::nested_qualified_name d;
    d.type(g);

    nqn.children(std::list<dogen::sml::nested_qualified_name> { c, d });

    const auto a(ip.parse_qualified_name("std::unordered_map<std::string,my::type>"));
    BOOST_CHECK(asserter::assert_equals(nqn, a));
}

BOOST_AUTO_TEST_CASE(parsing_vector_of_shared_ptr_produces_expected_nested_qualified_names) {
    SETUP_TEST_LOG("parsing_vector_of_shared_ptr_produces_expected_nested_qualified_names");
    dogen::sml::identifier_parser ip;
    dogen::sml::nested_qualified_name nqn;
    dogen::sml::qname e;
    e.type_name("vector");
    e.model_name("std");
    nqn.type(e);

    dogen::sml::qname f;
    f.type_name("shared_ptr");
    f.model_name("std");
    dogen::sml::nested_qualified_name c;
    c.type(f);

    dogen::sml::qname g;
    g.type_name("string");
    g.model_name("std");
    dogen::sml::nested_qualified_name d;
    d.type(g);
    c.children(std::list<dogen::sml::nested_qualified_name> { d });
    nqn.children(std::list<dogen::sml::nested_qualified_name> { c });

    const auto a(ip.parse_qualified_name("std::vector<std::shared_ptr<std::string>>"));
    BOOST_CHECK(asserter::assert_equals(nqn, a));
}

BOOST_AUTO_TEST_CASE(names_that_partially_match_primitives_produce_expected_nested_qualified_name) {
    SETUP_TEST_LOG("names_that_partially_match_primitives_produce_expected_nested_qualified_name");

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
