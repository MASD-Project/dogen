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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_SERIALIZATION_ALL_SER_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_SERIALIZATION_ALL_SER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/cpp_model/serialization/base_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/value_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/fluent_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/a_class_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/class_0_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/class_1_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/class_a_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/class_b_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/class_c_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/class_d_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/builtins_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/consumer_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/one_line_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/hex_flags_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/some_type_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/book_types_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/multi_line_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/short_enum_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/descendant1_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/descendant2_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/descendant3_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/colour_types_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/immutable_two_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/int_primitive_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/bool_primitive_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/char_primitive_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/immutable_four_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/immutable_zero_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/long_primitive_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/move_ctor_base_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/non_final_leaf_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/parent_outside_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/test_all_knobs_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/uint_primitive_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/float_primitive_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_6/child_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_8/child_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_9/child_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/short_primitive_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/uchar_primitive_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/ulong_primitive_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/double_primitive_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/non_final_orphan_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_6/parent_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_7/parent_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/ushort_primitive_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/child_of_a_child1_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/child_of_a_child2_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/further_inherited_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_1/class_1_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_1/class_2_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_1/class_3_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_1/class_4_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_1/class_5_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_2/class_1_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_2/class_2_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/child_via_settings_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/child_with_members_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/immutable_primitive_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/parent_with_members_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/move_ctor_descendant_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/child_without_members_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/immutable_one_builtin_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_4/shape_types_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/parent_without_members_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/third_child_with_members_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/base_with_object_template_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/immutable_one_non_builtin_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/move_ctor_empty_descendant_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_6/child_via_settings_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_8/child_via_settings_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_9/child_via_settings_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/second_child_without_members_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/base_object_template_instance_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/multi_object_template_instance_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/simple_object_template_instance_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/package_10/consume_object_template_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/descendant_object_template_instance_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/multiple_parents_object_template_instance_ser.hpp"
#include "dogen/test_models/cpp_model/serialization/second_descendant_object_template_instance_ser.hpp"

#endif
