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
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/test_models/stereotypes/types/all.hpp"
#include "dogen/test_models/stereotypes/io/all_io.hpp"
#include "dogen/test_models/stereotypes/serialization/all_ser.hpp"
#include "dogen/test_models/test_model_sanitizer/register_types.hpp"
#include "dogen/test_models/stereotypes/test_data/all_td.hpp"
#include "dogen/test_models/stereotypes/hash/all_hash.hpp"

namespace {

const std::string empty;
const std::string test_module("test_model_sanitizer");
const std::string test_suite("stereotypes_tests");

}

using dogen::utility::test::asserter;
using namespace dogen::test_models::stereotypes;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(stereotypes_tests)

BOOST_AUTO_TEST_CASE(validate_equality) {
    SETUP_TEST_LOG("validate_equality");
    test_equality<value_generator>();
    test_equality<immutable_four_generator>();
    test_equality<immutable_one_non_builtin_generator>();
    test_equality<immutable_one_builtin_generator>();
    test_equality<immutable_two_generator>();
    test_equality<fluent_generator>();
    test_equality<fluent_generator>();
    test_equality<simple_concept_model_generator>();
    test_equality<base_concept_model_generator>();
    test_equality<refinement_concept_model_generator>();
    test_equality<multiple_refinement_concept_model_generator>();
    test_equality<multi_concept_model_generator>();
    test_equality<further_refined_generator>();
}

BOOST_AUTO_TEST_CASE(validate_serialisation) {
    SETUP_TEST_LOG("validate_serialisation");
    roundtrip_type<value_generator>();
    roundtrip_type<immutable_four_generator>();
    roundtrip_type<immutable_one_non_builtin_generator>();
    roundtrip_type<immutable_one_builtin_generator>();
    roundtrip_type<immutable_two_generator>();
    roundtrip_type<fluent_generator>();
    roundtrip_type<fluent_generator>();
    roundtrip_type<simple_concept_model_generator>();
    roundtrip_type<base_concept_model_generator>();
    roundtrip_type<refinement_concept_model_generator>();
    roundtrip_type<multiple_refinement_concept_model_generator>();
    roundtrip_type<multi_concept_model_generator>();
    roundtrip_type<further_refined_generator>();
}

BOOST_AUTO_TEST_CASE(validate_hashing) {
    SETUP_TEST_LOG("validate_hashing");
    test_hashing<value_generator>();
    test_hashing<immutable_four_generator>();
    test_hashing<immutable_one_non_builtin_generator>();
    test_hashing<immutable_one_builtin_generator>();
    test_hashing<immutable_two_generator>();
    test_hashing<fluent_generator>();
    test_hashing<fluent_generator>();
    test_hashing<simple_concept_model_generator>();
    test_hashing<base_concept_model_generator>();
    test_hashing<refinement_concept_model_generator>();
    test_hashing<multi_concept_model_generator>();
    test_hashing<further_refined_generator>();
}

BOOST_AUTO_TEST_CASE(validate_swap) {
    SETUP_TEST_LOG("validate_hashing");
    test_swap<value_generator>();
    test_swap<fluent_generator>();
    test_swap<simple_concept_model_generator>();
    test_swap<base_concept_model_generator>();
    test_swap<refinement_concept_model_generator>();
    test_swap<multiple_refinement_concept_model_generator>();
}

BOOST_AUTO_TEST_CASE(validate_io) {
    SETUP_TEST_LOG("validate_io");
    test_io<value_generator>();
    test_io<immutable_four_generator>();
    test_io<immutable_one_non_builtin_generator>();
    test_io<immutable_one_builtin_generator>();
    test_io<immutable_two_generator>();
    test_io<immutable_zero_generator>();
    test_io<fluent_generator>();
    test_io<fluent_generator>();
    test_io<simple_concept_model_generator>();
    test_io<base_concept_model_generator>();
    test_io<refinement_concept_model_generator>();
    test_io<multiple_refinement_concept_model_generator>();
    test_io<multi_concept_model_generator>();
    test_io<further_refined_generator>();
}

BOOST_AUTO_TEST_CASE(validate_move_assignment_copy) {
    SETUP_TEST_LOG("validate_move_assignment_copy");
    // NOTE: skipping immutable_one_builtin because boolean types
    // don't play well with our requirement that the parameter passed
    // in must not be equal to a default constructed type.
    test_move_assignment_copy<value_generator>();
    test_move_assignment_copy<immutable_four_generator>();
    test_move_assignment_copy<immutable_one_non_builtin_generator>();
    test_move_assignment_copy<immutable_two_generator>();
    test_move_assignment_copy<fluent_generator>();
    test_move_assignment_copy<fluent_generator>();
        test_move_assignment_copy<simple_concept_model_generator>();
    test_move_assignment_copy<base_concept_model_generator>();
    test_move_assignment_copy<refinement_concept_model_generator>();
    test_move_assignment_copy<multiple_refinement_concept_model_generator>();
    test_move_assignment_copy<multi_concept_model_generator>();
    test_move_assignment_copy<further_refined_generator>();
}

BOOST_AUTO_TEST_CASE(setting_properties_using_the_fluent_interface_produces_expected_result) {
    SETUP_TEST_LOG("setting_properties_using_the_fluent_interface_produces_expected_result");

    const value z(15);
    const std::string s("a string");
    const fluent e(1234, s, z);
    fluent a;
    a.prop_0(1234).prop_1(s).prop_2(z);
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_SUITE_END()
