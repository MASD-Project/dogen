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
#include "dogen.identification/types/entities/technical_space.hpp"

/*
#include "dogen.logical/types/name_builder.hpp"
#include "dogen.logical/types/name_factory.hpp"
#include "dogen.logical/types/model.hpp"
#include "dogen.logical/types/parsing_error.hpp"
#include "dogen.logical/io/name_tree_io.hpp"
#include "dogen.logical/io/name_io.hpp"
#include "dogen.logical/types/merging_error.hpp"
#include "dogen.logical/types/name_tree_parser.hpp"
#include "dogen.logical/types/merger.hpp"*/
#include "dogen.utility/types/test/exception_checkers.hpp"
#include "dogen.identification/types/helpers/new_logical_name_tree_parser.hpp"

namespace  {

const std::string empty;
const std::string test_module("dogen.logical.tests");
const std::string test_suite("new_logical_name_tree_parser_tests");

const auto cpp(dogen::identification::entities::technical_space::cpp);

const auto top_level_modules = std::unordered_set<std::string>();
const auto model_location = dogen::identification::entities::logical_location();



struct test_dummy_builder
{

};

bool applied = false;
name_tree_listener<test_dummy_builder> listener{};

template<>
void name_tree_listener<test_dummy_builder>::apply()
{
    applied = true;
}

bool check_parse(const std::string & s)
{
    applied = false;
    listener = name_tree_listener<test_dummy_builder>{};

    grammar<std::string::const_iterator, ascii::space_type, test_dummy_builder> g(listener, cpp);

    std::string::const_iterator i(s.begin());
    std::string::const_iterator end(s.end());

    const bool ok = boost::spirit::qi::phrase_parse(i, end, g, ascii::space);

    return ok && (i == end);
}

}

BOOST_AUTO_TEST_SUITE(new_name_tree_parser_tests)

BOOST_AUTO_TEST_CASE(parsing_string_with_many_nested_scopes_produces_expected_name) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_many_nested_scopes_produces_expected_name");

    {
        custom_type_grammar<std::string::const_iterator, ascii::space_type, test_dummy_builder> ctg{&listener, cpp};

        listener.type_name.clear();
        std::string s = "abc";
        auto itr = s.cbegin();
        BOOST_CHECK(boost::spirit::qi::phrase_parse(itr, s.cend(), ctg, ascii::space));
        BOOST_CHECK(itr == s.cend());
        BOOST_CHECK_EQUAL(listener.type_name, "abc");

        listener.type_name.clear();
        s = "a1::b2:: _c";
        itr = s.cbegin();
        BOOST_CHECK(boost::spirit::qi::phrase_parse(itr, s.cend(), ctg, ascii::space));
        BOOST_CHECK(itr == s.cend());
        BOOST_CHECK_EQUAL(listener.type_name, "a1::b2::_c");

        listener.type_name.clear();
        s = "a::b::c::z";
        itr = s.cbegin();
        BOOST_CHECK(boost::spirit::qi::phrase_parse(itr, s.cend(), ctg, ascii::space));
        BOOST_CHECK(itr == s.cend());
        BOOST_CHECK_EQUAL(listener.type_name, "a::b::c::z");

        listener.type_name.clear();
        s = "::__a";
        itr = s.cbegin();
        BOOST_CHECK(boost::spirit::qi::phrase_parse(itr, s.cend(), ctg, ascii::space));
        BOOST_CHECK(itr == s.cend());
        BOOST_CHECK_EQUAL(listener.type_name, "__a");

        s = "-a";
        itr = s.cbegin();
        BOOST_CHECK(!boost::spirit::qi::phrase_parse(itr, s.cend(), ctg, ascii::space));
        BOOST_CHECK(itr != s.cend());

        s = "a::7::D";
        itr = s.cbegin();
        BOOST_CHECK(itr != s.cend());

        s = "a: :x";
        itr = s.cbegin();
        BOOST_CHECK(itr != s.cend());

    }

    BOOST_CHECK(check_parse("a :: b :: c :: z"));
    BOOST_CHECK(applied);
    BOOST_CHECK(!listener.is_const);
    BOOST_CHECK(!listener.is_volatile);
    BOOST_CHECK(!listener.sign);
    BOOST_CHECK_EQUAL(listener.type_name, "a::b::c::z");
    BOOST_CHECK(listener.pointers.empty());
    BOOST_CHECK(!listener.is_reference);
    BOOST_CHECK(!listener.is_array);

    BOOST_CHECK(check_parse("const a :: b :: c :: z"));
    BOOST_CHECK(applied);
    BOOST_CHECK(listener.is_const);
    BOOST_CHECK(!listener.is_volatile);
    BOOST_CHECK(!listener.sign);
    BOOST_CHECK_EQUAL(listener.type_name, "a::b::c::z");
    BOOST_CHECK(listener.pointers.empty());
    BOOST_CHECK(!listener.is_reference);
    BOOST_CHECK(!listener.is_array);

    BOOST_CHECK(check_parse("consta :: b :: c :: z"));
    BOOST_CHECK(applied);
    BOOST_CHECK(!listener.is_const);
    BOOST_CHECK(!listener.is_volatile);
    BOOST_CHECK(!listener.sign);
    BOOST_CHECK_EQUAL(listener.type_name, "consta::b::c::z");
    BOOST_CHECK(listener.pointers.empty());
    BOOST_CHECK(!listener.is_reference);
    BOOST_CHECK(!listener.is_array);

    BOOST_CHECK(check_parse("const volatile a :: b :: c :: z"));
    BOOST_CHECK(applied);
    BOOST_CHECK(listener.is_const);
    BOOST_CHECK(listener.is_volatile);
    BOOST_CHECK(!listener.sign);
    BOOST_CHECK_EQUAL(listener.type_name, "a::b::c::z");
    BOOST_CHECK(listener.pointers.empty());
    BOOST_CHECK(!listener.is_reference);
    BOOST_CHECK(!listener.is_array);

    BOOST_CHECK(check_parse("const a :: b :: c :: z &"));
    BOOST_CHECK(applied);
    BOOST_CHECK(listener.is_const);
    BOOST_CHECK(!listener.is_volatile);
    BOOST_CHECK(!listener.sign);
    BOOST_CHECK_EQUAL(listener.type_name, "a::b::c::z");
    BOOST_CHECK(listener.pointers.empty());
    BOOST_CHECK(listener.is_reference);
    BOOST_CHECK(!listener.is_array);

    BOOST_CHECK(check_parse("const std::string & ** const volatile * const * volatile"));
    BOOST_CHECK(applied);
    BOOST_CHECK(listener.is_const);
    BOOST_CHECK(!listener.is_volatile);
    BOOST_CHECK(!listener.sign);
    BOOST_CHECK_EQUAL(listener.type_name, "std::string");
    BOOST_CHECK(listener.is_reference);
    BOOST_CHECK(!listener.is_array);
    BOOST_REQUIRE_EQUAL(listener.pointers.size(), 4);

    BOOST_CHECK(!listener.pointers[0].is_const);
    BOOST_CHECK(!listener.pointers[0].is_volatile);

    BOOST_CHECK(listener.pointers[1].is_const);
    BOOST_CHECK(listener.pointers[1].is_volatile);

    BOOST_CHECK( listener.pointers[2].is_const);
    BOOST_CHECK(!listener.pointers[2].is_volatile);

    BOOST_CHECK(!listener.pointers[3].is_const);
    BOOST_CHECK( listener.pointers[3].is_volatile);

    BOOST_CHECK(check_parse("const thingy [3]"));
    BOOST_CHECK(applied);
    BOOST_CHECK(listener.is_const);
    BOOST_CHECK(!listener.is_volatile);
    BOOST_CHECK(!listener.sign);
    BOOST_CHECK_EQUAL(listener.type_name, "thingy");
    BOOST_CHECK(listener.pointers.empty());
    BOOST_CHECK(!listener.is_reference);
    BOOST_CHECK(listener.is_array);
    BOOST_CHECK_EQUAL(*listener.is_array, 3);

    //check that it does not accidentally parse keywords in scope

    BOOST_CHECK(!check_parse("signed::foo::bar"));
    BOOST_CHECK(!check_parse("foo::volatile::bar"));
    BOOST_CHECK(!check_parse("foo::bar::unsigned"));

}


BOOST_AUTO_TEST_CASE(parsing_string_without_scope_operator_produces_expected_name) {
    SETUP_TEST_LOG_SOURCE("parsing_string_without_scope_operator_produces_expected_name");

    BOOST_CHECK(check_parse("zeta"));
    BOOST_CHECK(applied);
    BOOST_CHECK(!listener.is_const);
    BOOST_CHECK(!listener.is_volatile);
    BOOST_CHECK(!listener.sign);
    BOOST_CHECK_EQUAL(listener.type_name, "zeta");
    BOOST_CHECK(listener.pointers.empty());
    BOOST_CHECK(!listener.is_reference);
    BOOST_CHECK(!listener.is_array);

    BOOST_CHECK(check_parse("const thingy [3]"));
    BOOST_CHECK(applied);
    BOOST_CHECK(listener.is_const);
    BOOST_CHECK(!listener.is_volatile);
    BOOST_CHECK(!listener.sign);
    BOOST_CHECK_EQUAL(listener.type_name, "thingy");
    BOOST_CHECK(listener.pointers.empty());
    BOOST_CHECK(!listener.is_reference);
    BOOST_REQUIRE(listener.is_array);
    BOOST_CHECK_EQUAL(*listener.is_array, 3);
}


BOOST_AUTO_TEST_CASE(parsing_string_with_one_scope_operator_produces_expected_name) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_one_scope_operator_produces_expected_name");
    const std::string s("a::z");

    BOOST_CHECK(check_parse(s));
    BOOST_CHECK(applied);
    BOOST_CHECK(!listener.is_const);
    BOOST_CHECK(!listener.is_volatile);
    BOOST_CHECK(!listener.sign);
    BOOST_CHECK_EQUAL(listener.type_name, s);
    BOOST_CHECK(listener.pointers.empty());
    BOOST_CHECK(!listener.is_reference);
    BOOST_CHECK(!listener.is_array);

}

BOOST_AUTO_TEST_CASE(parsing_string_with_single_colon_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_single_colon_fails_to_parse");
    const std::string s("a:z");

    custom_type_grammar<std::string::const_iterator, ascii::space_type, test_dummy_builder> ctg{&listener, cpp};

    listener.type_name.clear();
    auto itr = s.cbegin();
    BOOST_CHECK(boost::spirit::qi::phrase_parse(itr, s.cend(), ctg, ascii::space));
    BOOST_CHECK(itr != s.cend());
    BOOST_CHECK_EQUAL(listener.type_name, "a");
}


BOOST_AUTO_TEST_CASE(string_starting_with_digit_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("string_starting_with_digit_fails_to_parse");
    const std::string s("0a");

    custom_type_grammar<std::string::const_iterator, ascii::space_type, test_dummy_builder> ctg{&listener, cpp};

    listener.type_name.clear();
    auto itr = s.cbegin();
    BOOST_CHECK(!boost::spirit::qi::phrase_parse(itr, s.cend(), ctg, ascii::space));
    BOOST_CHECK(itr != s.cend());
}

BOOST_AUTO_TEST_CASE(string_ending_with_scope_operator_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("string_ending_with_scope_operator_fails_to_parse");
    const std::string s("a::");

    custom_type_grammar<std::string::const_iterator, ascii::space_type, test_dummy_builder> ctg{&listener, cpp};

    listener.type_name.clear();
    auto itr = s.cbegin();
    BOOST_CHECK(boost::spirit::qi::phrase_parse(itr, s.cend(), ctg, ascii::space));
    BOOST_CHECK(itr != s.cend());

}

BOOST_AUTO_TEST_CASE(scope_operator_followed_by_scope_operator_fails_to_parse) {
    SETUP_TEST_LOG_SOURCE("scope_operator_followed_by_scope_operator_fails_to_parse");
    const std::string s("A::::");

    custom_type_grammar<std::string::const_iterator, ascii::space_type, test_dummy_builder> ctg{&listener, cpp};

    listener.type_name.clear();
    auto itr = s.cbegin();
    BOOST_CHECK(boost::spirit::qi::phrase_parse(itr, s.cend(), ctg, ascii::space));
    BOOST_CHECK(itr != s.cend());
}

BOOST_AUTO_TEST_CASE(all_builtin_types_are_valid) {
    SETUP_TEST_LOG("all_builtin_types_are_valid");

    BOOST_CHECK(check_parse("char"));
    BOOST_CHECK(applied);
    BOOST_CHECK(!listener.is_const);
    BOOST_CHECK(!listener.is_volatile);
    BOOST_CHECK(!listener.sign);
    BOOST_CHECK_EQUAL(listener.type_name, "char");
    BOOST_CHECK(listener.pointers.empty());
    BOOST_CHECK(!listener.is_reference);
    BOOST_CHECK(!listener.is_array);

    BOOST_CHECK(check_parse("char unsigned"));
    BOOST_CHECK(applied);
    BOOST_CHECK(!listener.is_const);
    BOOST_CHECK(!listener.is_volatile);
    BOOST_REQUIRE(listener.sign);
    BOOST_CHECK(!*listener.sign);
    BOOST_CHECK_EQUAL(listener.type_name, "char");
    BOOST_CHECK(listener.pointers.empty());
    BOOST_CHECK(!listener.is_reference);
    BOOST_CHECK(!listener.is_array);


    BOOST_CHECK(check_parse("unsigned wchar_t"));
    BOOST_CHECK(applied);
    BOOST_CHECK(!listener.is_const);
    BOOST_CHECK(!listener.is_volatile);
    BOOST_REQUIRE(listener.sign);
    BOOST_CHECK(!*listener.sign);
    BOOST_CHECK_EQUAL(listener.type_name, "wchar_t");
    BOOST_CHECK(listener.pointers.empty());
    BOOST_CHECK(!listener.is_reference);
    BOOST_CHECK(!listener.is_array);


    BOOST_CHECK(check_parse("short int"));
    BOOST_CHECK(applied);
    BOOST_CHECK(!listener.is_const);
    BOOST_CHECK(!listener.is_volatile);
    BOOST_CHECK(!listener.sign);
    BOOST_CHECK_EQUAL(listener.type_name, "short");
    BOOST_CHECK(listener.pointers.empty());
    BOOST_CHECK(!listener.is_reference);
    BOOST_CHECK(!listener.is_array);

    BOOST_CHECK(check_parse("unsigned short"));
    BOOST_CHECK(applied);
    BOOST_CHECK(!listener.is_const);
    BOOST_CHECK(!listener.is_volatile);
    BOOST_REQUIRE(listener.sign);
    BOOST_CHECK(!*listener.sign);
    BOOST_CHECK_EQUAL(listener.type_name, "short");
    BOOST_CHECK(listener.pointers.empty());
    BOOST_CHECK(!listener.is_reference);
    BOOST_CHECK(!listener.is_array);

    BOOST_CHECK(check_parse("long signed long"));
    BOOST_CHECK(applied);
    BOOST_CHECK(!listener.is_const);
    BOOST_CHECK(!listener.is_volatile);
    BOOST_REQUIRE(listener.sign);
    BOOST_CHECK(*listener.sign);
    BOOST_CHECK_EQUAL(listener.type_name, "long long");
    BOOST_CHECK(listener.pointers.empty());
    BOOST_CHECK(!listener.is_reference);
    BOOST_CHECK(!listener.is_array);

    BOOST_CHECK(check_parse("double long"));
    BOOST_CHECK(applied);
    BOOST_CHECK(!listener.is_const);
    BOOST_CHECK(!listener.is_volatile);
    BOOST_CHECK(!listener.sign);
    BOOST_CHECK_EQUAL(listener.type_name, "long double");
    BOOST_CHECK(listener.pointers.empty());
    BOOST_CHECK(!listener.is_reference);
    BOOST_CHECK(!listener.is_array);

    BOOST_CHECK(check_parse("int signed volatile long const long &"));
    BOOST_CHECK(applied);
    BOOST_CHECK(listener.is_const);
    BOOST_CHECK(listener.is_volatile);
    BOOST_REQUIRE(listener.sign);
    BOOST_CHECK(*listener.sign);
    BOOST_CHECK_EQUAL(listener.type_name, "long long");
    BOOST_CHECK(listener.pointers.empty());
    BOOST_CHECK(listener.is_reference);
    BOOST_CHECK(!listener.is_array);
}


BOOST_AUTO_TEST_CASE(unsignable_types_cannot_be_unsigned) {
    SETUP_TEST_LOG("unsignable_types_cannot_be_unsigned");

    BOOST_CHECK(!check_parse("unsigned bool"));
    BOOST_CHECK(!check_parse("unsigned x"));
    BOOST_CHECK(!check_parse("unsigned float"));
    BOOST_CHECK(!check_parse("unsigned double"));
}

BOOST_AUTO_TEST_CASE(parsing_string_with_single_template_argument_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_single_template_argument_produces_expected_name_trees");
/*
    dogen::logical::name_tree e;
    dogen::logical::name_factory nf;
    e.current(nf.build_element_name("type"));

    dogen::logical::name_tree c;
    c.current(nf.build_element_name("abc"));

    e.children(std::list<dogen::logical::name_tree> { c });

    const std::string s("type<abc>");
    dogen::logical::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));*/
}

BOOST_AUTO_TEST_CASE(parsing_string_with_two_template_argument_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_string_with_two_template_argument_produces_expected_name_trees");
/*
    dogen::logical::name_tree e;
    dogen::logical::name_factory nf;
    e.current(nf.build_element_name("type"));

    dogen::logical::name_tree c;
    c.current(nf.build_element_name("abc"));

    dogen::logical::name_tree d;
    d.current(nf.build_element_name("cde"));

    e.children(std::list<dogen::logical::name_tree> { c, d });

    const std::string s("type<abc,cde>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::logical::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));*/
}

BOOST_AUTO_TEST_CASE(parsing_vector_of_string_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_vector_of_string_produces_expected_name_trees");
 /*   dogen::logical::name_tree e;
    dogen::logical::name_factory nf;
    e.current(nf.build_element_name("std", "vector"));

    dogen::logical::name_tree c;
    c.current(nf.build_element_name("std", "string"));

    e.children(std::list<dogen::logical::name_tree> { c });

    const std::string s("std::vector<std::string>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::logical::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));*/
}

BOOST_AUTO_TEST_CASE(parsing_vector_of_builtin_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_vector_of_builtin_produces_expected_name_trees");
/*
    dogen::logical::name_tree e;
    dogen::logical::name_factory nf;
    e.current(nf.build_element_name("std", "vector"));

    dogen::logical::name_tree c;
    c.current(nf.build_element_name("unsigned int"));

    e.children(std::list<dogen::logical::name_tree> { c });

    const std::string s("std::vector<unsigned int>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::logical::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));*/
}

BOOST_AUTO_TEST_CASE(parsing_unordered_map_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_unordered_map_produces_expected_name_trees");
/*
    dogen::logical::name_tree e;

    dogen::logical::name_factory nf;
    e.current(nf.build_element_name("std", "unordered_map"));

    dogen::logical::name_tree c;
    c.current(nf.build_element_name("std", "string"));

    dogen::logical::name_tree d;
    d.current(nf.build_element_name("my", "type"));

    e.children(std::list<dogen::logical::name_tree> { c, d });

    const std::string s1("std::unordered_map<std::string,my::type>");
    BOOST_LOG_SEV(lg, info) << "input: " << s1;

    dogen::logical::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a1(ntp.parse(s1));
    BOOST_CHECK(asserter::assert_equals(e, a1));

    const std::string s2("std::unordered_map<std::string,    my::type>");
    BOOST_LOG_SEV(lg, info) << "input: " << s2;

    const auto a2(ntp.parse(s2));
    BOOST_CHECK(asserter::assert_equals(e, a2));*/
}

BOOST_AUTO_TEST_CASE(parsing_vector_of_shared_ptr_produces_expected_name_trees) {
    SETUP_TEST_LOG_SOURCE("parsing_vector_of_shared_ptr_produces_expected_name_trees");

  /*  dogen::logical::name_tree e;
    dogen::logical::name_factory nf;
    e.current(nf.build_element_name("std", "vector"));

    dogen::logical::name_tree c;
    c.current(nf.build_element_name("std", "shared_ptr"));

    dogen::logical::name_tree d;
    d.current(nf.build_element_name("std", "string"));

    c.children(std::list<dogen::logical::name_tree> { d });
    e.children(std::list<dogen::logical::name_tree> { c });

    const std::string s("std::vector<std::shared_ptr<std::string>>");
    BOOST_LOG_SEV(lg, info) << "input: " << s;

    dogen::logical::name_tree_parser ntp(top_level_modules, model_location, cpp);
    const auto a(ntp.parse(s));
    BOOST_CHECK(asserter::assert_equals(e, a));*/
}

BOOST_AUTO_TEST_CASE(names_that_partially_match_builtins_produce_expected_name_tree) {
    SETUP_TEST_LOG("names_that_partially_match_builtins_produce_expected_name_tree");
/*
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
    BOOST_CHECK(test_builtin("longer"));*/
}

BOOST_AUTO_TEST_SUITE_END()
