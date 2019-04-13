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
#include <string>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "masd.dogen.archetypes/io/location_io.hpp"
#include "masd.dogen.archetypes/types/location.hpp"
#include "masd.dogen.archetypes/test_data/location_td.hpp"

BOOST_AUTO_TEST_SUITE(location_tests)

BOOST_AUTO_TEST_CASE(identical_objects_are_equal) {
    masd::dogen::archetypes::location_generator g;
    const auto a(g());
    const auto b(a);

    BOOST_CHECK(a == b);
    BOOST_CHECK(b == a);
    BOOST_CHECK(!(a != b));
}

BOOST_AUTO_TEST_CASE(an_object_is_equal_to_itself) {
    masd::dogen::archetypes::location_generator g;
    const auto a(g());

    BOOST_CHECK(a == a);
    BOOST_CHECK(!(a != a));
}

BOOST_AUTO_TEST_CASE(distinct_objects_are_unequal) {
    masd::dogen::archetypes::location_generator g;
    const auto a(g());
    const auto b(g());

    BOOST_CHECK(!(a == b));
    BOOST_CHECK(a != b);
}

BOOST_AUTO_TEST_CASE(assigning_an_object_to_itself_results_in_the_same_object) {
#if defined(__clang__) && !defined(__apple_build_version__)  && (__clang_major__ >= 7)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wself-assign-overloaded"
#endif
    masd::dogen::archetypes::location_generator g;
    auto a(g());
    const auto b(a);
    const auto c(g());

    a = a;
    BOOST_CHECK(a == b);
    BOOST_CHECK(a != c);
#if defined(__clang__) && !defined(__apple_build_version__)  && (__clang_major__ >= 7)
#pragma clang diagnostic pop
#endif
}

BOOST_AUTO_TEST_CASE(moved_objects_are_equal) {
    masd::dogen::archetypes::location_generator g;
    g();
    auto a(g());
    const auto b = masd::dogen::archetypes::location();
    const auto c(a);
    BOOST_CHECK(a != b);
    BOOST_CHECK(a == c);

    const auto d = std::move(a);
    BOOST_CHECK(d == c);
    BOOST_CHECK(d != b);
}

BOOST_AUTO_TEST_CASE(assigned_objects_are_equal) {
    masd::dogen::archetypes::location_generator g;
    g();
    const auto a(g());
    masd::dogen::archetypes::location b;
    BOOST_CHECK(a != b);

    b = a;
    BOOST_CHECK(a == b);
}

BOOST_AUTO_TEST_CASE(copy_constructed_objects_are_equal) {
    masd::dogen::archetypes::location_generator g;
    g();
    const auto a(g());
    auto b(a);
    BOOST_CHECK(a == b);

    b = masd::dogen::archetypes::location();
    BOOST_CHECK(a != b);
}

BOOST_AUTO_TEST_CASE(swapping_objects_results_in_the_expected_state) {
    masd::dogen::archetypes::location_generator g;
    const auto a(g());
    const auto b(g());

    auto c(a);
    auto d(b);
    BOOST_CHECK(c == a);
    BOOST_CHECK(d == b);

    std::swap(c, d);
    BOOST_CHECK(c == b);
    BOOST_CHECK(d == a);
}

BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {
    masd::dogen::archetypes::location_generator g;
    const auto a(g());
    std::stringstream s;
    s << a;

    boost::property_tree::ptree pt;
    BOOST_REQUIRE_NO_THROW(read_json(s, pt));
}

BOOST_AUTO_TEST_SUITE_END()
