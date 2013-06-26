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
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/stereotypes/types/all.hpp"
#include "dogen/stereotypes/io/all_io.hpp"
#include "dogen/stereotypes/serialization/all_ser.hpp"
#include "dogen/test_model_sanitizer/register_types.hpp"
#include "dogen/stereotypes/test_data/all_td.hpp"
#include "dogen/stereotypes/hash/all_hash.hpp"

namespace {

const std::string empty;
const std::string test_module("test_model_sanitizer");
const std::string test_suite("stereotypes");

}

using dogen::utility::test::asserter;
using namespace dogen::stereotypes;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(stereotypes)

BOOST_AUTO_TEST_CASE(validate_equality) {
    SETUP_TEST_LOG("validate_equality");
    test_equality<entity_generator>();
    test_equality<value_generator>();
    test_equality<immutable_four_generator>();
    test_equality<immutable_one_non_primitive_generator>();
    test_equality<immutable_one_primitive_generator>();
    test_equality<immutable_two_generator>();
    test_equality<fluent_generator>();
    test_equality<composite_identity_generator>();
    test_equality<composite_identity_unversioned_key_generator>();
    test_equality<composite_identity_ver_generator>();
    test_equality<composite_identity_ver_unversioned_key_generator>();
    test_equality<composite_identity_ver_versioned_key_generator>();
    test_equality<entity_generator>();
    test_equality<fluent_generator>();
    test_equality<identity_and_other_generator>();
    test_equality<identity_and_other_unversioned_key_generator>();
    test_equality<identity_and_other_ver_generator>();
    test_equality<identity_and_other_ver_unversioned_key_generator>();
    test_equality<identity_and_other_ver_versioned_key_generator>();
    test_equality<identity_pod_generator>();
    test_equality<identity_pod_unversioned_key_generator>();
    test_equality<identity_pod_versioned_key_generator>();
    test_equality<just_identity_generator>();
    test_equality<just_identity_unversioned_key_generator>();
    test_equality<just_identity_ver_generator>();
    test_equality<just_identity_ver_unversioned_key_generator>();
    test_equality<just_identity_ver_versioned_key_generator>();
    test_equality<pkg1::keyed_in_package_generator>();
    test_equality<pkg1::keyed_in_package_unversioned_key_generator>();
    test_equality<versioned_generator>();
    test_equality<aggregate_root_generator>();
    test_equality<simple_concept_model_generator>();
    test_equality<base_concept_model_generator>();
    test_equality<refinement_concept_model_generator>();
    test_equality<multiple_refinement_concept_model_generator>();
    test_equality<multi_concept_model_generator>();
    test_equality<further_refined_generator>();
}

BOOST_AUTO_TEST_CASE(validate_serialisation) {
    SETUP_TEST_LOG("validate_serialisation");
    rountrip_type<entity_generator>();
    rountrip_type<value_generator>();
    rountrip_type<immutable_four_generator>();
    rountrip_type<immutable_one_non_primitive_generator>();
    rountrip_type<immutable_one_primitive_generator>();
    rountrip_type<immutable_two_generator>();
    rountrip_type<fluent_generator>();
    rountrip_type<composite_identity_generator>();
    rountrip_type<composite_identity_unversioned_key_generator>();
    rountrip_type<composite_identity_ver_generator>();
    rountrip_type<composite_identity_ver_unversioned_key_generator>();
    rountrip_type<composite_identity_ver_versioned_key_generator>();
    rountrip_type<entity_generator>();
    rountrip_type<fluent_generator>();
    rountrip_type<identity_and_other_generator>();
    rountrip_type<identity_and_other_unversioned_key_generator>();
    rountrip_type<identity_and_other_ver_generator>();
    rountrip_type<identity_and_other_ver_unversioned_key_generator>();
    rountrip_type<identity_and_other_ver_versioned_key_generator>();
    rountrip_type<identity_pod_generator>();
    rountrip_type<identity_pod_unversioned_key_generator>();
    rountrip_type<identity_pod_versioned_key_generator>();
    rountrip_type<just_identity_generator>();
    rountrip_type<just_identity_unversioned_key_generator>();
    rountrip_type<just_identity_ver_generator>();
    rountrip_type<just_identity_ver_unversioned_key_generator>();
    rountrip_type<just_identity_ver_versioned_key_generator>();
    rountrip_type<pkg1::keyed_in_package_generator>();
    rountrip_type<pkg1::keyed_in_package_unversioned_key_generator>();
    rountrip_type<versioned_generator>();
    rountrip_type<aggregate_root_generator>();
    rountrip_type<simple_concept_model_generator>();
    rountrip_type<base_concept_model_generator>();
    rountrip_type<refinement_concept_model_generator>();
    rountrip_type<multiple_refinement_concept_model_generator>();
    rountrip_type<multi_concept_model_generator>();
    rountrip_type<further_refined_generator>();
}

BOOST_AUTO_TEST_CASE(validate_hashing) {
    SETUP_TEST_LOG("validate_hashing");
    test_hashing<entity_generator>();
    test_hashing<value_generator>();
    test_hashing<immutable_four_generator>();
    test_hashing<immutable_one_non_primitive_generator>();
    test_hashing<immutable_one_primitive_generator>();
    test_hashing<immutable_two_generator>();
    test_hashing<fluent_generator>();
    test_hashing<composite_identity_generator>();
    test_hashing<composite_identity_unversioned_key_generator>();
    test_hashing<composite_identity_ver_generator>();
    test_hashing<composite_identity_ver_unversioned_key_generator>();
    test_hashing<composite_identity_ver_versioned_key_generator>();
    test_hashing<entity_generator>();
    test_hashing<fluent_generator>();
    test_hashing<identity_and_other_generator>();
    test_hashing<identity_and_other_unversioned_key_generator>();
    test_hashing<identity_and_other_ver_generator>();
    test_hashing<identity_and_other_ver_unversioned_key_generator>();
    test_hashing<identity_and_other_ver_versioned_key_generator>();
    test_hashing<identity_pod_generator>();
    test_hashing<identity_pod_unversioned_key_generator>();
    test_hashing<identity_pod_versioned_key_generator>();
    test_hashing<just_identity_generator>();
    test_hashing<just_identity_unversioned_key_generator>();
    test_hashing<just_identity_ver_generator>();
    test_hashing<just_identity_ver_unversioned_key_generator>();
    test_hashing<just_identity_ver_versioned_key_generator>();
    test_hashing<pkg1::keyed_in_package_generator>();
    test_hashing<pkg1::keyed_in_package_unversioned_key_generator>();
    test_hashing<versioned_generator>();
    test_hashing<aggregate_root_generator>();
    test_hashing<simple_concept_model_generator>();
    test_hashing<base_concept_model_generator>();
    test_hashing<refinement_concept_model_generator>();
    test_hashing<multi_concept_model_generator>();
    test_hashing<further_refined_generator>();
}

BOOST_AUTO_TEST_CASE(validate_swap) {
    SETUP_TEST_LOG("validate_hashing");
    test_swap<entity_generator>();
    test_swap<value_generator>();
    test_swap<fluent_generator>();
    test_swap<composite_identity_generator>();
    test_swap<composite_identity_unversioned_key_generator>();
    test_swap<composite_identity_ver_generator>();
    test_swap<composite_identity_ver_unversioned_key_generator>();
    test_swap<composite_identity_ver_versioned_key_generator>();
    test_swap<entity_generator>();
    test_swap<fluent_generator>();
    test_swap<identity_and_other_generator>();
    test_swap<identity_and_other_unversioned_key_generator>();
    test_swap<identity_and_other_ver_generator>();
    test_swap<identity_and_other_ver_unversioned_key_generator>();
    test_swap<identity_and_other_ver_versioned_key_generator>();
    test_swap<identity_pod_generator>();
    test_swap<identity_pod_unversioned_key_generator>();
    test_swap<identity_pod_versioned_key_generator>();
    test_swap<just_identity_generator>();
    test_swap<just_identity_unversioned_key_generator>();
    test_swap<just_identity_ver_generator>();
    test_swap<just_identity_ver_unversioned_key_generator>();
    test_swap<just_identity_ver_versioned_key_generator>();
    test_swap<pkg1::keyed_in_package_generator>();
    test_swap<pkg1::keyed_in_package_unversioned_key_generator>();
    test_swap<versioned_generator>();
    test_swap<aggregate_root_generator>();
    test_swap<simple_concept_model_generator>();
    test_swap<base_concept_model_generator>();
    test_swap<refinement_concept_model_generator>();
    test_swap<multiple_refinement_concept_model_generator>();
}

BOOST_AUTO_TEST_CASE(validate_io) {
    SETUP_TEST_LOG("validate_io");
    test_io<entity_generator>();
    test_io<value_generator>();
    test_io<immutable_four_generator>();
    test_io<immutable_one_non_primitive_generator>();
    test_io<immutable_one_primitive_generator>();
    test_io<immutable_two_generator>();
    test_io<immutable_zero_generator>();
    test_io<fluent_generator>();
    test_io<composite_identity_generator>();
    test_io<composite_identity_unversioned_key_generator>();
    test_io<composite_identity_ver_generator>();
    test_io<composite_identity_ver_unversioned_key_generator>();
    test_io<composite_identity_ver_versioned_key_generator>();
    test_io<entity_generator>();
    test_io<fluent_generator>();
    test_io<identity_and_other_generator>();
    test_io<identity_and_other_unversioned_key_generator>();
    test_io<identity_and_other_ver_generator>();
    test_io<identity_and_other_ver_unversioned_key_generator>();
    test_io<identity_and_other_ver_versioned_key_generator>();
    test_io<identity_pod_generator>();
    test_io<identity_pod_unversioned_key_generator>();
    test_io<identity_pod_versioned_key_generator>();
    test_io<just_identity_generator>();
    test_io<just_identity_unversioned_key_generator>();
    test_io<just_identity_ver_generator>();
    test_io<just_identity_ver_unversioned_key_generator>();
    test_io<just_identity_ver_versioned_key_generator>();
    test_io<pkg1::keyed_in_package_generator>();
    test_io<pkg1::keyed_in_package_unversioned_key_generator>();
    test_io<versioned_generator>();
    test_io<aggregate_root_generator>();
    test_io<simple_concept_model_generator>();
    test_io<base_concept_model_generator>();
    test_io<refinement_concept_model_generator>();
    test_io<multiple_refinement_concept_model_generator>();
    test_io<multi_concept_model_generator>();
    test_io<further_refined_generator>();
}

BOOST_AUTO_TEST_CASE(validate_move_assignment_copy) {
    SETUP_TEST_LOG("validate_move_assignment_copy");
    // NOTE: skipping immutable_one_primitive because boolean types
    // don't play well with our requirement that the parameter passed
    // in must not be equal to a default constructed type.
    test_move_assignment_copy<entity_generator>();
    test_move_assignment_copy<value_generator>();
    test_move_assignment_copy<immutable_four_generator>();
    test_move_assignment_copy<immutable_one_non_primitive_generator>();
    test_move_assignment_copy<immutable_two_generator>();
    test_move_assignment_copy<fluent_generator>();
    test_move_assignment_copy<composite_identity_generator>();
    test_move_assignment_copy<composite_identity_unversioned_key_generator>();
    test_move_assignment_copy<composite_identity_ver_generator>();
    test_move_assignment_copy<composite_identity_ver_unversioned_key_generator>();
    test_move_assignment_copy<composite_identity_ver_versioned_key_generator>();
    test_move_assignment_copy<entity_generator>();
    test_move_assignment_copy<fluent_generator>();
    test_move_assignment_copy<identity_and_other_generator>();
    test_move_assignment_copy<identity_and_other_unversioned_key_generator>();
    test_move_assignment_copy<identity_and_other_ver_generator>();
    test_move_assignment_copy<identity_and_other_ver_unversioned_key_generator>();
    test_move_assignment_copy<identity_and_other_ver_versioned_key_generator>();
    test_move_assignment_copy<identity_pod_generator>();
    test_move_assignment_copy<identity_pod_unversioned_key_generator>();
    test_move_assignment_copy<identity_pod_versioned_key_generator>();
    test_move_assignment_copy<just_identity_generator>();
    test_move_assignment_copy<just_identity_unversioned_key_generator>();
    test_move_assignment_copy<just_identity_ver_generator>();
    test_move_assignment_copy<just_identity_ver_unversioned_key_generator>();
    test_move_assignment_copy<just_identity_ver_versioned_key_generator>();
    test_move_assignment_copy<pkg1::keyed_in_package_generator>();
    test_move_assignment_copy<pkg1::keyed_in_package_unversioned_key_generator>();
    test_move_assignment_copy<versioned_generator>();
    test_move_assignment_copy<aggregate_root_generator>();
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

BOOST_AUTO_TEST_CASE(versioned_stereotype_results_in_new_property_named_version) {
    SETUP_TEST_LOG("versioned_stereotype_results_in_new_property_named_version");

    versioned v;
    v.version(10);
}

BOOST_AUTO_TEST_SUITE_END()
