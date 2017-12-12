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
#include "dogen.utility/test/logging.hpp"
#include "dogen.utility/test/canned_tests.hpp"
#include "dogen/test_models/cpp_98/types/all.hpp"
#include "dogen/test_models/cpp_98/io/all_io.hpp"
#include "dogen/test_models/cpp_98/serialization/all_ser.hpp"
#include "dogen/test_models/cpp_98/test_data/all_td.hpp"
#include "dogen/test_models/test_model_sanitizer/register_types.hpp"

namespace {

const std::string test_module("test_model_sanitizer");
const std::string test_suite("cpp_98_tests");

}

using namespace dogen::test_models::cpp_98;
using namespace dogen::test_models::cpp_98::package1;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(cpp_98_tests)

BOOST_AUTO_TEST_CASE(validate_equality) {
    SETUP_TEST_LOG("validate_equality");
    test_equality<first_class_generator>();
    test_equality<child_generator>();
}

BOOST_AUTO_TEST_CASE(validate_swap) {
    SETUP_TEST_LOG("validate_swap");
    test_swap<first_class_generator>();
    test_swap<child_generator>();
}

BOOST_AUTO_TEST_CASE(validate_move_assignment_copy) {
    SETUP_TEST_LOG("validate_move_assignment_copy");
    test_move_assignment_copy<first_class_generator>();
    test_move_assignment_copy<child_generator>();
}

BOOST_AUTO_TEST_CASE(validate_serialisation) {
    SETUP_TEST_LOG("validate_serialisation");
    roundtrip_type<first_class_generator>();
    roundtrip_type<child_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
