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
#include <boost/exception/diagnostic_information.hpp>
#include "dogen.utility/io/vector_io.hpp"
#include "dogen.utility/test/logging.hpp"
#include "dogen.utility/test/canned_tests.hpp"
#include "dogen/test_models/cpp_model/types/all.hpp"
#include "dogen/test_models/cpp_model/io/all_io.hpp"
#include "dogen/test_models/cpp_model/serialization/all_ser.hpp"
#include "dogen/test_models/test_model_sanitizer/register_types.hpp"
#include "dogen/test_models/cpp_model/test_data/all_td.hpp"
#include "dogen/test_models/cpp_model/hash/all_hash.hpp"

namespace {

const std::string empty;
const std::string test_module("test_model_sanitizer");
const std::string test_suite("cpp_model_serialisation_tests");

}

using namespace dogen::test_models::cpp_model;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(cpp_model_serialisation_tests)

BOOST_AUTO_TEST_CASE(validate_serialisation) {
    SETUP_TEST_LOG("validate_serialisation");
    roundtrip_type<a_class_generator>();
    roundtrip_type<class_1_generator>();

    roundtrip_type<package_1::class_1_generator>();
    roundtrip_type<package_1::class_2_generator>();
    roundtrip_type<package_1::class_3_generator>();
    roundtrip_type<package_1::class_4_generator>();
    roundtrip_type<package_1::class_5_generator>();
    roundtrip_type<package_2::class_1_generator>();

    roundtrip_type<book_types_generator>();
    roundtrip_type<colour_types_generator>();
    roundtrip_type<package_4::shape_types_generator>();
    roundtrip_type<a_class_generator>();

    roundtrip_type<short_primitive_generator>();
    roundtrip_type<ushort_primitive_generator>();
    roundtrip_type<long_primitive_generator>();
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

    roundtrip_type<value_generator>();
    roundtrip_type<immutable_four_generator>();
    roundtrip_type<immutable_one_non_builtin_generator>();
    roundtrip_type<immutable_one_builtin_generator>();
    roundtrip_type<immutable_two_generator>();
    roundtrip_type<fluent_generator>();
    roundtrip_type<fluent_generator>();
    roundtrip_type<simple_object_template_instance_generator>();
    roundtrip_type<base_object_template_instance_generator>();
    roundtrip_type<descendant_object_template_instance_generator>();
    roundtrip_type<multiple_parents_object_template_instance_generator>();
    roundtrip_type<multi_object_template_instance_generator>();
    roundtrip_type<further_inherited_generator>();

    roundtrip_type<class_a_generator>();
    roundtrip_type<class_b_generator>();

    roundtrip_type<child_with_members_generator>();
    roundtrip_type<second_child_without_members_generator>();
    roundtrip_type<child_of_a_child1_generator>();
    roundtrip_type<child_of_a_child2_generator>();
    roundtrip_type<package_6::child_generator>();
    roundtrip_type<package_8::child_generator>();
    roundtrip_type<package_9::child_generator>();
    roundtrip_type<move_ctor_descendant_generator>();
    roundtrip_type<move_ctor_empty_descendant_generator>();
    roundtrip_type<child_via_settings_generator>();
    roundtrip_type<package_6::child_via_settings_generator>();
    roundtrip_type<package_8::child_via_settings_generator>();
    roundtrip_type<package_9::child_via_settings_generator>();
    roundtrip_type<non_final_leaf_generator>();
    roundtrip_type<non_final_orphan_generator>();
    roundtrip_type<descendant2_generator>();
    roundtrip_type<descendant3_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
