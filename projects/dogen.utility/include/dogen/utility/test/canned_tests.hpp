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
#ifndef DOGEN_UTILITY_TEST_CANNED_TESTS_HPP
#define DOGEN_UTILITY_TEST_CANNED_TESTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/io_tester.hpp"
#include "dogen/utility/test/hash_tester.hpp"
#include "dogen/utility/test/move_assignment_copy_tester.hpp"
#include "dogen/utility/test/equality_tester.hpp"
#include "dogen/utility/test/serialization_tester.hpp"

namespace dogen {
namespace utility {
namespace test {

template<typename Sequence>
void test_equality() {
    Sequence sequence;
    const auto a(sequence());
    const auto b(a);
    const auto c(sequence());

    typedef utility::test::equality_tester
        <typename Sequence::result_type> tester;
    tester::an_object_is_equal_to_itself(a);
    tester::identical_objects_are_equal(a, b);
    tester::distinct_objects_are_unequal(a, c);
}

template<typename Sequence>
void test_move_assignment_copy() {
    Sequence sequence;
    sequence(); // throw the first one away
    const auto a(sequence());

    typedef utility::test::move_assignment_copy_tester
        <typename Sequence::result_type> tester;
    tester::moved_objects_are_equal(a);
    tester::assigned_objects_are_equal(a);
    tester::copy_constructed_objects_are_equal(a);
}

template<typename Sequence>
void roundtrip_type() {
    Sequence sequence;
    sequence(); // throw the first one away
    utility::test::serialization_tester<typename Sequence::result_type>::
        all_roundtrips_produce_the_same_entity(sequence());
}

template<typename Sequence>
void test_hashing() {
    utility::test::hash_tester<Sequence>::
        equal_objects_must_generate_the_same_hash();

    utility::test::hash_tester<Sequence>::
        unequal_objects_must_generate_different_hashes();
}

template<typename Sequence>
void test_swap() {
    Sequence seq;
    const auto a(seq());
    const auto b(seq());

    auto c(a);
    auto d(b);
    BOOST_CHECK(c == a);
    BOOST_CHECK(d == b);

    std::swap(c, d);
    BOOST_CHECK(c == b);
    BOOST_CHECK(d == a);
}

template<typename Sequence>
void test_io() {
    Sequence seq;
    utility::test::io_tester<typename Sequence::result_type>::
        inserter_operator_produces_valid_json(seq());
}

} } }

#endif
