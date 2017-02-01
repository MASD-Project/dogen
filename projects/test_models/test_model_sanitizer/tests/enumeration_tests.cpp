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
#include "dogen/test_models/enumeration/types/all.hpp"
#include "dogen/test_models/enumeration/io/all_io.hpp"
#include "dogen/test_models/enumeration/serialization/all_ser.hpp"
#include "dogen/test_models/test_model_sanitizer/register_types.hpp"
#include "dogen/test_models/enumeration/test_data/all_td.hpp"
#include "dogen/test_models/enumeration/hash/all_hash.hpp"

namespace {

const std::string empty;
const std::string test_module("test_model_sanitizer");
const std::string test_suite("enumeration_tests");

}

using namespace dogen::test_models::enumeration;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(enumeration_tests)

BOOST_AUTO_TEST_CASE(validate_equality) {
    SETUP_TEST_LOG("validate_equality");
    test_equality<book_types_generator>();
    test_equality<colour_types_generator>();
    test_equality<pkg1::shape_types_generator>();
    test_equality<a_class_generator>();
}

BOOST_AUTO_TEST_CASE(validate_serialisation) {
    SETUP_TEST_LOG("validate_serialisation");
    roundtrip_type<book_types_generator>();
    roundtrip_type<colour_types_generator>();
    roundtrip_type<pkg1::shape_types_generator>();
    roundtrip_type<a_class_generator>();
}

BOOST_AUTO_TEST_CASE(validate_hashing) {
    SETUP_TEST_LOG("validate_hashing");
    test_hashing<book_types_generator>();
    test_hashing<colour_types_generator>();
    test_hashing<pkg1::shape_types_generator>();
    test_hashing<a_class_generator>();
}

BOOST_AUTO_TEST_CASE(validate_swap) {
    SETUP_TEST_LOG("validate_swap");
    test_swap<book_types_generator>();
    test_swap<colour_types_generator>();
    test_swap<pkg1::shape_types_generator>();
    test_swap<a_class_generator>();
}

BOOST_AUTO_TEST_CASE(validate_io) {
    SETUP_TEST_LOG("validate_io");
    test_io<book_types_generator>();
    test_io<colour_types_generator>();
    test_io<pkg1::shape_types_generator>();
    test_io<a_class_generator>();
}

BOOST_AUTO_TEST_CASE(validate_move_assignment_copy) {
    SETUP_TEST_LOG("validate_move_assignment_copy");
    test_move_assignment_copy<book_types_generator>();
    test_move_assignment_copy<colour_types_generator>();
    test_move_assignment_copy<pkg1::shape_types_generator>();
    test_move_assignment_copy<a_class_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
