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
#ifndef DOGEN_UTILITY_TEST_CANNED_TESTS_HPP
#define DOGEN_UTILITY_TEST_CANNED_TESTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/hash_tester.hpp"
#include "dogen/utility/test/equality_tester.hpp"
#include "dogen/utility/test/serialization_tester.hpp"

namespace dogen {
namespace utility {
namespace test {

template<typename Sequence>
void test_equality() {
    Sequence sequence;
    const typename Sequence::value_type a(sequence());
    const typename Sequence::value_type b(a);
    const typename Sequence::value_type c(sequence());

    typedef utility::test::equality_tester
        <typename Sequence::value_type> equality_tester;
    equality_tester::an_object_is_equal_to_itself(a);
    equality_tester::identical_objects_are_equal(a, b);
    equality_tester::distinct_objects_are_unequal(a, c);
}

template<typename Sequence>
void rountrip_type() {
    Sequence sequence;
    utility::test::serialization_tester<typename Sequence::value_type>::
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

} } }

#endif
