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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/trivial_inheritance/domain/all.hpp"
#include "dogen/trivial_inheritance/io/all_io.hpp"
#include "dogen/trivial_inheritance/serialization/all_ser.hpp"
#include "dogen/test_model_sanitizer/register_types.hpp"
#include "dogen/trivial_inheritance/test_data/all_td.hpp"
#include "dogen/trivial_inheritance/hash/all_hash.hpp"

namespace {

const std::string empty;
const std::string test_module("test_model_sanitizer");
const std::string test_suite("trivial_inheritance");

}

using namespace dogen::trivial_inheritance;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(trivial_inheritance)

BOOST_AUTO_TEST_CASE(validate_equality) {
    SETUP_TEST_LOG("validate_equality");
    test_equality<child_without_members_generator>();
    test_equality<second_child_without_members_generator>();
    test_equality<child_of_a_child1_generator>();
    test_equality<child_of_a_child2_generator>();
    test_equality<pkg1::child_generator>();
    test_equality<pkg3::child_generator>();
    test_equality<pkg4::child_generator>();
}

BOOST_AUTO_TEST_CASE(validate_serialisation) {
    SETUP_TEST_LOG("validate_serialisation");
    rountrip_type<child_without_members_generator>();
    rountrip_type<second_child_without_members_generator>();
    rountrip_type<child_of_a_child1_generator>();
    rountrip_type<child_of_a_child2_generator>();
    rountrip_type<pkg1::child_generator>();
    rountrip_type<pkg3::child_generator>();
    rountrip_type<pkg4::child_generator>();
}

BOOST_AUTO_TEST_CASE(validate_hashing) {
    SETUP_TEST_LOG("validate_hashing");
    test_hashing<child_without_members_generator>();
    test_hashing<second_child_without_members_generator>();
    test_hashing<child_of_a_child1_generator>();
    test_hashing<child_of_a_child2_generator>();
    test_hashing<pkg1::child_generator>();
    test_hashing<pkg3::child_generator>();
    test_hashing<pkg4::child_generator>();
}

BOOST_AUTO_TEST_CASE(validate_swap) {
    SETUP_TEST_LOG("validate_hashing");
    test_swap<child_without_members_generator>();
    test_swap<second_child_without_members_generator>();
    test_swap<child_of_a_child1_generator>();
    test_swap<child_of_a_child2_generator>();
    test_swap<pkg1::child_generator>();
    test_swap<pkg3::child_generator>();
    test_swap<pkg4::child_generator>();
}

BOOST_AUTO_TEST_CASE(validate_io) {
    SETUP_TEST_LOG("validate_io");
    test_io<child_without_members_generator>();
    test_io<second_child_without_members_generator>();
    test_io<child_of_a_child1_generator>();
    test_io<child_of_a_child2_generator>();
    test_io<pkg1::child_generator>();
    test_io<pkg3::child_generator>();
    test_io<pkg4::child_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
