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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TEST_DATA_ALL_TD_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TEST_DATA_ALL_TD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/cpp_model/test_data/base_td.hpp"
#include "dogen/test_models/cpp_model/test_data/value_td.hpp"
#include "dogen/test_models/cpp_model/test_data/fluent_td.hpp"
#include "dogen/test_models/cpp_model/test_data/a_class_td.hpp"
#include "dogen/test_models/cpp_model/test_data/class_0_td.hpp"
#include "dogen/test_models/cpp_model/test_data/class_1_td.hpp"
#include "dogen/test_models/cpp_model/test_data/class_a_td.hpp"
#include "dogen/test_models/cpp_model/test_data/class_b_td.hpp"
#include "dogen/test_models/cpp_model/test_data/class_c_td.hpp"
#include "dogen/test_models/cpp_model/test_data/class_d_td.hpp"
#include "dogen/test_models/cpp_model/test_data/builtins_td.hpp"
#include "dogen/test_models/cpp_model/test_data/consumer_td.hpp"
#include "dogen/test_models/cpp_model/test_data/one_line_td.hpp"
#include "dogen/test_models/cpp_model/test_data/hex_flags_td.hpp"
#include "dogen/test_models/cpp_model/test_data/some_type_td.hpp"
#include "dogen/test_models/cpp_model/test_data/book_types_td.hpp"
#include "dogen/test_models/cpp_model/test_data/multi_line_td.hpp"
#include "dogen/test_models/cpp_model/test_data/short_enum_td.hpp"
#include "dogen/test_models/cpp_model/test_data/descendant1_td.hpp"
#include "dogen/test_models/cpp_model/test_data/descendant2_td.hpp"
#include "dogen/test_models/cpp_model/test_data/descendant3_td.hpp"
#include "dogen/test_models/cpp_model/test_data/colour_types_td.hpp"
#include "dogen/test_models/cpp_model/test_data/immutable_two_td.hpp"
#include "dogen/test_models/cpp_model/test_data/int_primitive_td.hpp"
#include "dogen/test_models/cpp_model/test_data/bool_primitive_td.hpp"
#include "dogen/test_models/cpp_model/test_data/char_primitive_td.hpp"
#include "dogen/test_models/cpp_model/test_data/immutable_four_td.hpp"
#include "dogen/test_models/cpp_model/test_data/immutable_zero_td.hpp"
#include "dogen/test_models/cpp_model/test_data/long_primitive_td.hpp"
#include "dogen/test_models/cpp_model/test_data/move_ctor_base_td.hpp"
#include "dogen/test_models/cpp_model/test_data/non_final_leaf_td.hpp"
#include "dogen/test_models/cpp_model/test_data/parent_outside_td.hpp"
#include "dogen/test_models/cpp_model/test_data/test_all_knobs_td.hpp"
#include "dogen/test_models/cpp_model/test_data/uint_primitive_td.hpp"
#include "dogen/test_models/cpp_model/test_data/float_primitive_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_6/child_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_8/child_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_9/child_td.hpp"
#include "dogen/test_models/cpp_model/test_data/short_primitive_td.hpp"
#include "dogen/test_models/cpp_model/test_data/uchar_primitive_td.hpp"
#include "dogen/test_models/cpp_model/test_data/ulong_primitive_td.hpp"
#include "dogen/test_models/cpp_model/test_data/double_primitive_td.hpp"
#include "dogen/test_models/cpp_model/test_data/non_final_orphan_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_6/parent_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_7/parent_td.hpp"
#include "dogen/test_models/cpp_model/test_data/ushort_primitive_td.hpp"
#include "dogen/test_models/cpp_model/test_data/child_of_a_child1_td.hpp"
#include "dogen/test_models/cpp_model/test_data/child_of_a_child2_td.hpp"
#include "dogen/test_models/cpp_model/test_data/further_inherited_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_1/class_1_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_1/class_2_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_1/class_3_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_1/class_4_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_1/class_5_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_2/class_1_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_2/class_2_td.hpp"
#include "dogen/test_models/cpp_model/test_data/child_via_settings_td.hpp"
#include "dogen/test_models/cpp_model/test_data/child_with_members_td.hpp"
#include "dogen/test_models/cpp_model/test_data/immutable_primitive_td.hpp"
#include "dogen/test_models/cpp_model/test_data/parent_with_members_td.hpp"
#include "dogen/test_models/cpp_model/test_data/move_ctor_descendant_td.hpp"
#include "dogen/test_models/cpp_model/test_data/child_without_members_td.hpp"
#include "dogen/test_models/cpp_model/test_data/immutable_one_builtin_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_4/shape_types_td.hpp"
#include "dogen/test_models/cpp_model/test_data/parent_without_members_td.hpp"
#include "dogen/test_models/cpp_model/test_data/third_child_with_members_td.hpp"
#include "dogen/test_models/cpp_model/test_data/base_with_object_template_td.hpp"
#include "dogen/test_models/cpp_model/test_data/immutable_one_non_builtin_td.hpp"
#include "dogen/test_models/cpp_model/test_data/move_ctor_empty_descendant_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_6/child_via_settings_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_8/child_via_settings_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_9/child_via_settings_td.hpp"
#include "dogen/test_models/cpp_model/test_data/second_child_without_members_td.hpp"
#include "dogen/test_models/cpp_model/test_data/base_object_template_instance_td.hpp"
#include "dogen/test_models/cpp_model/test_data/multi_object_template_instance_td.hpp"
#include "dogen/test_models/cpp_model/test_data/simple_object_template_instance_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_10/consume_object_template_td.hpp"
#include "dogen/test_models/cpp_model/test_data/descendant_object_template_instance_td.hpp"
#include "dogen/test_models/cpp_model/test_data/multiple_parents_object_template_instance_td.hpp"
#include "dogen/test_models/cpp_model/test_data/second_descendant_object_template_instance_td.hpp"

#endif
