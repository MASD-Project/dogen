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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_HASH_ALL_HASH_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_HASH_ALL_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/cpp_model/hash/base_hash.hpp"
#include "dogen/test_models/cpp_model/hash/value_hash.hpp"
#include "dogen/test_models/cpp_model/hash/fluent_hash.hpp"
#include "dogen/test_models/cpp_model/hash/a_class_hash.hpp"
#include "dogen/test_models/cpp_model/hash/class_0_hash.hpp"
#include "dogen/test_models/cpp_model/hash/class_1_hash.hpp"
#include "dogen/test_models/cpp_model/hash/class_a_hash.hpp"
#include "dogen/test_models/cpp_model/hash/class_b_hash.hpp"
#include "dogen/test_models/cpp_model/hash/class_c_hash.hpp"
#include "dogen/test_models/cpp_model/hash/class_d_hash.hpp"
#include "dogen/test_models/cpp_model/hash/builtins_hash.hpp"
#include "dogen/test_models/cpp_model/hash/consumer_hash.hpp"
#include "dogen/test_models/cpp_model/hash/one_line_hash.hpp"
#include "dogen/test_models/cpp_model/hash/hex_flags_hash.hpp"
#include "dogen/test_models/cpp_model/hash/some_type_hash.hpp"
#include "dogen/test_models/cpp_model/hash/book_types_hash.hpp"
#include "dogen/test_models/cpp_model/hash/multi_line_hash.hpp"
#include "dogen/test_models/cpp_model/hash/short_enum_hash.hpp"
#include "dogen/test_models/cpp_model/hash/descendant1_hash.hpp"
#include "dogen/test_models/cpp_model/hash/descendant2_hash.hpp"
#include "dogen/test_models/cpp_model/hash/descendant3_hash.hpp"
#include "dogen/test_models/cpp_model/hash/colour_types_hash.hpp"
#include "dogen/test_models/cpp_model/hash/immutable_two_hash.hpp"
#include "dogen/test_models/cpp_model/hash/int_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/bool_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/char_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/immutable_four_hash.hpp"
#include "dogen/test_models/cpp_model/hash/immutable_zero_hash.hpp"
#include "dogen/test_models/cpp_model/hash/long_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/move_ctor_base_hash.hpp"
#include "dogen/test_models/cpp_model/hash/non_final_leaf_hash.hpp"
#include "dogen/test_models/cpp_model/hash/parent_outside_hash.hpp"
#include "dogen/test_models/cpp_model/hash/test_all_knobs_hash.hpp"
#include "dogen/test_models/cpp_model/hash/uint_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/float_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/package_6/child_hash.hpp"
#include "dogen/test_models/cpp_model/hash/package_8/child_hash.hpp"
#include "dogen/test_models/cpp_model/hash/package_9/child_hash.hpp"
#include "dogen/test_models/cpp_model/hash/short_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/uchar_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/ulong_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/double_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/non_final_orphan_hash.hpp"
#include "dogen/test_models/cpp_model/hash/package_6/parent_hash.hpp"
#include "dogen/test_models/cpp_model/hash/package_7/parent_hash.hpp"
#include "dogen/test_models/cpp_model/hash/ushort_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/child_of_a_child1_hash.hpp"
#include "dogen/test_models/cpp_model/hash/child_of_a_child2_hash.hpp"
#include "dogen/test_models/cpp_model/hash/further_inherited_hash.hpp"
#include "dogen/test_models/cpp_model/hash/package_1/class_1_hash.hpp"
#include "dogen/test_models/cpp_model/hash/package_1/class_2_hash.hpp"
#include "dogen/test_models/cpp_model/hash/package_1/class_3_hash.hpp"
#include "dogen/test_models/cpp_model/hash/package_1/class_4_hash.hpp"
#include "dogen/test_models/cpp_model/hash/package_1/class_5_hash.hpp"
#include "dogen/test_models/cpp_model/hash/package_2/class_1_hash.hpp"
#include "dogen/test_models/cpp_model/hash/package_2/class_2_hash.hpp"
#include "dogen/test_models/cpp_model/hash/child_via_settings_hash.hpp"
#include "dogen/test_models/cpp_model/hash/child_with_members_hash.hpp"
#include "dogen/test_models/cpp_model/hash/immutable_primitive_hash.hpp"
#include "dogen/test_models/cpp_model/hash/parent_with_members_hash.hpp"
#include "dogen/test_models/cpp_model/hash/move_ctor_descendant_hash.hpp"
#include "dogen/test_models/cpp_model/hash/child_without_members_hash.hpp"
#include "dogen/test_models/cpp_model/hash/immutable_one_builtin_hash.hpp"
#include "dogen/test_models/cpp_model/hash/package_4/shape_types_hash.hpp"
#include "dogen/test_models/cpp_model/hash/parent_without_members_hash.hpp"
#include "dogen/test_models/cpp_model/hash/third_child_with_members_hash.hpp"
#include "dogen/test_models/cpp_model/hash/base_with_object_template_hash.hpp"
#include "dogen/test_models/cpp_model/hash/immutable_one_non_builtin_hash.hpp"
#include "dogen/test_models/cpp_model/hash/move_ctor_empty_descendant_hash.hpp"
#include "dogen/test_models/cpp_model/hash/package_6/child_via_settings_hash.hpp"
#include "dogen/test_models/cpp_model/hash/package_8/child_via_settings_hash.hpp"
#include "dogen/test_models/cpp_model/hash/package_9/child_via_settings_hash.hpp"
#include "dogen/test_models/cpp_model/hash/second_child_without_members_hash.hpp"
#include "dogen/test_models/cpp_model/hash/base_object_template_instance_hash.hpp"
#include "dogen/test_models/cpp_model/hash/multi_object_template_instance_hash.hpp"
#include "dogen/test_models/cpp_model/hash/simple_object_template_instance_hash.hpp"
#include "dogen/test_models/cpp_model/hash/package_10/consume_object_template_hash.hpp"
#include "dogen/test_models/cpp_model/hash/descendant_object_template_instance_hash.hpp"
#include "dogen/test_models/cpp_model/hash/multiple_parents_object_template_instance_hash.hpp"
#include "dogen/test_models/cpp_model/hash/second_descendant_object_template_instance_hash.hpp"

#endif
