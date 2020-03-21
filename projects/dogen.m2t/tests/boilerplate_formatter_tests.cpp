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
#include "dogen.utility/types/test/asserter.hpp"
#include "dogen.utility/types/test/logging.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/filesystem/path.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.logical/types/entities/technical_space.hpp"
#include "dogen.m2t/types/formatters/indent_filter.hpp"
#include "dogen.m2t/types/formatters/boilerplate_properties.hpp"
#include "dogen.m2t/io/formatters/boilerplate_properties_io.hpp"
#include "dogen.m2t/types/formatters/boilerplate_formatter.hpp"

namespace {

const std::string test_module("dogen.m2t.tests");
const std::string test_suite("boilerplate_formatter_tests");
const std::string empty;

const std::string preamble(
    R"(This is a preamble
line 1
line 2
last line
)");

const std::string postamble(
    R"(now for the postamble
at the end line 1
at the end line 2
at the end last line
)");

const std::list<std::string> dependencies = {
    "first dependency",
    "second dependency"
};

const std::string expected_cpp_all_properties(
    R"(This is a preamble
line 1
line 2
last line
#ifndef this_is_a_guard
#define this_is_a_guard

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include first dependency
#include second dependency

now for the postamble
at the end line 1
at the end line 2
at the end last line
#endif
)");

const std::string expected_csharp_all_properties(
    R"(This is a preamble
line 1
line 2
last line
using first dependency
using second dependency

now for the postamble
at the end line 1
at the end line 2
at the end last line
)");

const std::string expected_cpp_no_guards(
    R"(This is a preamble
line 1
line 2
last line
#include first dependency
#include second dependency

now for the postamble
at the end line 1
at the end line 2
at the end last line
)");

const std::string expected_cpp_no_dependencies(
    R"(This is a preamble
line 1
line 2
last line
#ifndef this_is_a_guard
#define this_is_a_guard

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

now for the postamble
at the end line 1
at the end line 2
at the end last line
#endif
)");

const std::string expected_csharp_no_dependencies(
    R"(This is a preamble
line 1
line 2
last line
now for the postamble
at the end line 1
at the end line 2
at the end last line
)");

const std::string expected_cpp_no_preamble(
    R"(#ifndef this_is_a_guard
#define this_is_a_guard

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include first dependency
#include second dependency

#endif
)");

const std::string expected_csharp_no_preamble(
    R"(using first dependency
using second dependency
)");

using dogen::logical::entities::technical_space;
using dogen::m2t::formatters::boilerplate_properties;

boilerplate_properties make_all_properties(const technical_space ts) {
    boilerplate_properties r;

    r.generate_preamble(true);
    r.generate_header_guards(true);

    r.preamble(preamble);
    r.postamble(postamble);
    r.technical_space(ts);
    r.dependencies(dependencies);
    r.header_guard("this_is_a_guard");

    return r;
}

std::string format(const boilerplate_properties& bp) {
    std::ostringstream s;
    boost::iostreams::filtering_ostream fo;
    dogen::m2t::formatters::indent_filter::push(fo, 4);
    fo.push(s);

    dogen::m2t::formatters::boilerplate_formatter f(fo, bp);
    f.format_begin();
    f.format_end();
    return s.str();
}
}

using namespace dogen::m2t::formatters;
using namespace dogen::utility::test;
using dogen::utility::test::asserter;

BOOST_AUTO_TEST_SUITE(boilerplate_formatter_tests)

BOOST_AUTO_TEST_CASE(cpp_all_properties_are_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("cpp_all_properties_are_formatted_correctly");

    const auto bp(make_all_properties(technical_space::cpp));
    const auto a(format(bp));

    const auto& e(expected_cpp_all_properties);
    BOOST_CHECK(asserter::assert_equals_string(e, a));
}

BOOST_AUTO_TEST_CASE(csharp_all_properties_are_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("csharp_all_properties_are_formatted_correctly");

    const auto bp(make_all_properties(technical_space::csharp));
    const auto a(format(bp));

    const auto &e(expected_csharp_all_properties);
    BOOST_CHECK(asserter::assert_equals_string(e, a));
}

BOOST_AUTO_TEST_CASE(cpp_no_guards_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("cpp_no_guards_is_formatted_correctly");

    auto bp(make_all_properties(technical_space::cpp));
    bp.generate_header_guards(true);
    bp.header_guard("");

    const auto a(format(bp));

    const auto &e(expected_cpp_no_guards);
    BOOST_CHECK(asserter::assert_equals_string(e, a));
}

BOOST_AUTO_TEST_CASE(cpp_no_dependencies_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("cpp_no_dependencies_is_formatted_correctly");

    auto bp(make_all_properties(technical_space::cpp));
    bp.dependencies(std::list<std::string>());

    const auto a(format(bp));

    const auto &e(expected_cpp_no_dependencies);
    BOOST_CHECK(asserter::assert_equals_string(e, a));
}

BOOST_AUTO_TEST_CASE(csharp_no_dependencies_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("csharp_no_dependencies_is_formatted_correctly");

    auto bp(make_all_properties(technical_space::csharp));
    bp.dependencies(std::list<std::string>());

    const auto a(format(bp));

    const auto &e(expected_csharp_no_dependencies);
    BOOST_CHECK(asserter::assert_equals_string(e, a));
}

BOOST_AUTO_TEST_CASE(cpp_disabled_preamble_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("cpp_disabled_preamble_is_formatted_correctly");

    auto bp(make_all_properties(technical_space::cpp));
    bp.generate_preamble(false);

    const auto a(format(bp));

    const auto &e(expected_cpp_no_preamble);
    BOOST_CHECK(asserter::assert_equals_string(e, a));
}

BOOST_AUTO_TEST_CASE(csharp_disabled_preamble_is_formatted_correctly) {
    SETUP_TEST_LOG_SOURCE("csharp_disabled_preamble_is_formatted_correctly");

    auto bp(make_all_properties(technical_space::csharp));
    bp.generate_preamble(false);

    const auto a(format(bp));

    const auto &e(expected_csharp_no_preamble);
    BOOST_CHECK(asserter::assert_equals_string(e, a));
}

BOOST_AUTO_TEST_SUITE_END()
