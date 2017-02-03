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
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/test_models/primitive/types/all.hpp"
#include "dogen/test_models/primitive/io/all_io.hpp"
#include "dogen/test_models/primitive/serialization/all_ser.hpp"
#include "dogen/test_models/test_model_sanitizer/register_types.hpp"
#include "dogen/test_models/primitive/test_data/all_td.hpp"
#include "dogen/test_models/primitive/hash/all_hash.hpp"

namespace {

const std::string empty;
const std::string test_module("test_model_sanitizer");
const std::string test_suite("primitive_tests");

}

using namespace dogen::test_models::primitive;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(primitive_tests)

BOOST_AUTO_TEST_CASE(validate_equality) {
    SETUP_TEST_LOG("validate_equality");
    test_equality<short_primitive_generator>();
    test_equality<ushort_primitive_generator>();
    test_equality<a_long_primitive_generator>();
    test_equality<ulong_primitive_generator>();
    test_equality<int_primitive_generator>();
    test_equality<uint_primitive_generator>();
    test_equality<char_primitive_generator>();
    test_equality<uchar_primitive_generator>();
    test_equality<double_primitive_generator>();
    test_equality<float_primitive_generator>();
    test_equality<bool_primitive_generator>();
    test_equality<immutable_primitive_generator>();

    test_equality<consumer_generator>();
}

BOOST_AUTO_TEST_CASE(validate_serialisation) {
    SETUP_TEST_LOG("validate_serialisation");
    roundtrip_type<short_primitive_generator>();
    roundtrip_type<ushort_primitive_generator>();
    roundtrip_type<a_long_primitive_generator>();
    roundtrip_type<ulong_primitive_generator>();
    roundtrip_type<int_primitive_generator>();
    roundtrip_type<uint_primitive_generator>();
    roundtrip_type<char_primitive_generator>();
    roundtrip_type<uchar_primitive_generator>();
    roundtrip_type<double_primitive_generator>();
    roundtrip_type<float_primitive_generator>();
    roundtrip_type<bool_primitive_generator>();
    roundtrip_type<immutable_primitive_generator>();

    roundtrip_type<consumer_generator>();
}

BOOST_AUTO_TEST_CASE(validate_hashing) {
    SETUP_TEST_LOG("validate_hashing");
    test_hashing<short_primitive_generator>();
    test_hashing<ushort_primitive_generator>();
    test_hashing<a_long_primitive_generator>();
    test_hashing<ulong_primitive_generator>();
    test_hashing<int_primitive_generator>();
    test_hashing<uint_primitive_generator>();
    test_hashing<char_primitive_generator>();
    test_hashing<uchar_primitive_generator>();
    test_hashing<double_primitive_generator>();
    test_hashing<float_primitive_generator>();
    test_hashing<bool_primitive_generator>();
    test_hashing<immutable_primitive_generator>();

    test_hashing<consumer_generator>();
}

BOOST_AUTO_TEST_CASE(validate_swap) {
    SETUP_TEST_LOG("validate_swap");
    test_swap<short_primitive_generator>();
    test_swap<ushort_primitive_generator>();
    test_swap<a_long_primitive_generator>();
    test_swap<ulong_primitive_generator>();
    test_swap<int_primitive_generator>();
    test_swap<uint_primitive_generator>();
    test_swap<char_primitive_generator>();
    test_swap<uchar_primitive_generator>();
    test_swap<double_primitive_generator>();
    test_swap<float_primitive_generator>();
    test_swap<bool_primitive_generator>();

    test_swap<consumer_generator>();
}

BOOST_AUTO_TEST_CASE(validate_io) {
    SETUP_TEST_LOG("validate_io");
    test_io<short_primitive_generator>();
    test_io<ushort_primitive_generator>();
    test_io<a_long_primitive_generator>();
    test_io<ulong_primitive_generator>();
    test_io<int_primitive_generator>();
    test_io<uint_primitive_generator>();
    test_io<char_primitive_generator>();
    test_io<uchar_primitive_generator>();
    test_io<double_primitive_generator>();
    test_io<float_primitive_generator>();
    test_io<bool_primitive_generator>();
    test_io<immutable_primitive_generator>();

    test_io<consumer_generator>();
}

BOOST_AUTO_TEST_CASE(validate_move_assignment_copy) {
    SETUP_TEST_LOG("validate_move_assignment_copy");
    test_move_assignment_copy<short_primitive_generator>();
    test_move_assignment_copy<ushort_primitive_generator>();
    test_move_assignment_copy<a_long_primitive_generator>();
    test_move_assignment_copy<ulong_primitive_generator>();
    test_move_assignment_copy<int_primitive_generator>();
    test_move_assignment_copy<uint_primitive_generator>();
    test_move_assignment_copy<char_primitive_generator>();
    test_move_assignment_copy<uchar_primitive_generator>();
    test_move_assignment_copy<double_primitive_generator>();
    test_move_assignment_copy<float_primitive_generator>();
    // FIXME: commented out due to the well-known oscillation problems
    // with booleans.
    // test_move_assignment_copy<bool_primitive_generator>();
    test_move_assignment_copy<immutable_primitive_generator>();

    test_move_assignment_copy<consumer_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
