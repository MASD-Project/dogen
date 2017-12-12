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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_IO_ALL_IO_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_IO_ALL_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/cpp_model/io/base_io.hpp"
#include "dogen/test_models/cpp_model/io/value_io.hpp"
#include "dogen/test_models/cpp_model/io/fluent_io.hpp"
#include "dogen/test_models/cpp_model/io/a_class_io.hpp"
#include "dogen/test_models/cpp_model/io/class_0_io.hpp"
#include "dogen/test_models/cpp_model/io/class_1_io.hpp"
#include "dogen/test_models/cpp_model/io/class_a_io.hpp"
#include "dogen/test_models/cpp_model/io/class_b_io.hpp"
#include "dogen/test_models/cpp_model/io/class_c_io.hpp"
#include "dogen/test_models/cpp_model/io/class_d_io.hpp"
#include "dogen/test_models/cpp_model/io/builtins_io.hpp"
#include "dogen/test_models/cpp_model/io/consumer_io.hpp"
#include "dogen/test_models/cpp_model/io/one_line_io.hpp"
#include "dogen/test_models/cpp_model/io/hex_flags_io.hpp"
#include "dogen/test_models/cpp_model/io/some_type_io.hpp"
#include "dogen/test_models/cpp_model/io/book_types_io.hpp"
#include "dogen/test_models/cpp_model/io/multi_line_io.hpp"
#include "dogen/test_models/cpp_model/io/short_enum_io.hpp"
#include "dogen/test_models/cpp_model/io/descendant1_io.hpp"
#include "dogen/test_models/cpp_model/io/descendant2_io.hpp"
#include "dogen/test_models/cpp_model/io/descendant3_io.hpp"
#include "dogen/test_models/cpp_model/io/colour_types_io.hpp"
#include "dogen/test_models/cpp_model/io/immutable_two_io.hpp"
#include "dogen/test_models/cpp_model/io/int_primitive_io.hpp"
#include "dogen/test_models/cpp_model/io/bool_primitive_io.hpp"
#include "dogen/test_models/cpp_model/io/char_primitive_io.hpp"
#include "dogen/test_models/cpp_model/io/immutable_four_io.hpp"
#include "dogen/test_models/cpp_model/io/immutable_zero_io.hpp"
#include "dogen/test_models/cpp_model/io/long_primitive_io.hpp"
#include "dogen/test_models/cpp_model/io/move_ctor_base_io.hpp"
#include "dogen/test_models/cpp_model/io/non_final_leaf_io.hpp"
#include "dogen/test_models/cpp_model/io/parent_outside_io.hpp"
#include "dogen/test_models/cpp_model/io/test_all_knobs_io.hpp"
#include "dogen/test_models/cpp_model/io/uint_primitive_io.hpp"
#include "dogen/test_models/cpp_model/io/float_primitive_io.hpp"
#include "dogen/test_models/cpp_model/io/package_6/child_io.hpp"
#include "dogen/test_models/cpp_model/io/package_8/child_io.hpp"
#include "dogen/test_models/cpp_model/io/package_9/child_io.hpp"
#include "dogen/test_models/cpp_model/io/short_primitive_io.hpp"
#include "dogen/test_models/cpp_model/io/uchar_primitive_io.hpp"
#include "dogen/test_models/cpp_model/io/ulong_primitive_io.hpp"
#include "dogen/test_models/cpp_model/io/double_primitive_io.hpp"
#include "dogen/test_models/cpp_model/io/non_final_orphan_io.hpp"
#include "dogen/test_models/cpp_model/io/package_6/parent_io.hpp"
#include "dogen/test_models/cpp_model/io/package_7/parent_io.hpp"
#include "dogen/test_models/cpp_model/io/ushort_primitive_io.hpp"
#include "dogen/test_models/cpp_model/io/child_of_a_child1_io.hpp"
#include "dogen/test_models/cpp_model/io/child_of_a_child2_io.hpp"
#include "dogen/test_models/cpp_model/io/further_inherited_io.hpp"
#include "dogen/test_models/cpp_model/io/package_1/class_1_io.hpp"
#include "dogen/test_models/cpp_model/io/package_1/class_2_io.hpp"
#include "dogen/test_models/cpp_model/io/package_1/class_3_io.hpp"
#include "dogen/test_models/cpp_model/io/package_1/class_4_io.hpp"
#include "dogen/test_models/cpp_model/io/package_1/class_5_io.hpp"
#include "dogen/test_models/cpp_model/io/package_2/class_1_io.hpp"
#include "dogen/test_models/cpp_model/io/package_2/class_2_io.hpp"
#include "dogen/test_models/cpp_model/io/child_via_settings_io.hpp"
#include "dogen/test_models/cpp_model/io/child_with_members_io.hpp"
#include "dogen/test_models/cpp_model/io/immutable_primitive_io.hpp"
#include "dogen/test_models/cpp_model/io/parent_with_members_io.hpp"
#include "dogen/test_models/cpp_model/io/move_ctor_descendant_io.hpp"
#include "dogen/test_models/cpp_model/io/child_without_members_io.hpp"
#include "dogen/test_models/cpp_model/io/immutable_one_builtin_io.hpp"
#include "dogen/test_models/cpp_model/io/package_4/shape_types_io.hpp"
#include "dogen/test_models/cpp_model/io/parent_without_members_io.hpp"
#include "dogen/test_models/cpp_model/io/third_child_with_members_io.hpp"
#include "dogen/test_models/cpp_model/io/base_with_object_template_io.hpp"
#include "dogen/test_models/cpp_model/io/immutable_one_non_builtin_io.hpp"
#include "dogen/test_models/cpp_model/io/move_ctor_empty_descendant_io.hpp"
#include "dogen/test_models/cpp_model/io/package_6/child_via_settings_io.hpp"
#include "dogen/test_models/cpp_model/io/package_8/child_via_settings_io.hpp"
#include "dogen/test_models/cpp_model/io/package_9/child_via_settings_io.hpp"
#include "dogen/test_models/cpp_model/io/second_child_without_members_io.hpp"
#include "dogen/test_models/cpp_model/io/base_object_template_instance_io.hpp"
#include "dogen/test_models/cpp_model/io/multi_object_template_instance_io.hpp"
#include "dogen/test_models/cpp_model/io/simple_object_template_instance_io.hpp"
#include "dogen/test_models/cpp_model/io/package_10/consume_object_template_io.hpp"
#include "dogen/test_models/cpp_model/io/descendant_object_template_instance_io.hpp"
#include "dogen/test_models/cpp_model/io/multiple_parents_object_template_instance_io.hpp"
#include "dogen/test_models/cpp_model/io/second_descendant_object_template_instance_io.hpp"

#endif
