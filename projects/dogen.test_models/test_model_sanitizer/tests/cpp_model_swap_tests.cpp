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
const std::string test_suite("cpp_model_swap_tests");

}

using namespace dogen::test_models::cpp_model;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(cpp_model_swap_tests)

BOOST_AUTO_TEST_CASE(validate_swap) {
    SETUP_TEST_LOG("validate_swap");
    test_swap<a_class_generator>();
    test_swap<class_1_generator>();

    test_swap<package_1::class_1_generator>();
    test_swap<package_1::class_2_generator>();
    test_swap<package_1::class_3_generator>();
    test_swap<package_1::class_4_generator>();
    test_swap<package_1::class_5_generator>();
    test_swap<package_2::class_1_generator>();

    test_swap<book_types_generator>();
    test_swap<colour_types_generator>();
    test_swap<package_4::shape_types_generator>();
    test_swap<a_class_generator>();

    test_swap<short_primitive_generator>();
    test_swap<ushort_primitive_generator>();
    test_swap<long_primitive_generator>();
    test_swap<ulong_primitive_generator>();
    test_swap<int_primitive_generator>();
    test_swap<uint_primitive_generator>();
    test_swap<char_primitive_generator>();
    test_swap<uchar_primitive_generator>();
    test_swap<double_primitive_generator>();
    test_swap<float_primitive_generator>();
    test_swap<bool_primitive_generator>();

    test_swap<consumer_generator>();

    test_swap<value_generator>();
    test_swap<fluent_generator>();

    test_swap<simple_object_template_instance_generator>();
    test_swap<base_object_template_instance_generator>();
    test_swap<descendant_object_template_instance_generator>();
    test_swap<multiple_parents_object_template_instance_generator>();

    test_swap<class_a_generator>();
    test_swap<class_b_generator>();

    test_swap<child_with_members_generator>();
    test_swap<second_child_without_members_generator>();
    test_swap<child_of_a_child1_generator>();
    test_swap<child_of_a_child2_generator>();
    test_swap<package_6::child_generator>();
    test_swap<package_8::child_generator>();
    test_swap<package_9::child_generator>();
    test_swap<move_ctor_descendant_generator>();
    test_swap<move_ctor_empty_descendant_generator>();
    test_swap<child_via_settings_generator>();
    test_swap<package_6::child_via_settings_generator>();
    test_swap<package_8::child_via_settings_generator>();
    test_swap<package_9::child_via_settings_generator>();
    test_swap<non_final_leaf_generator>();
    test_swap<non_final_orphan_generator>();
    test_swap<descendant2_generator>();
    test_swap<descendant3_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
