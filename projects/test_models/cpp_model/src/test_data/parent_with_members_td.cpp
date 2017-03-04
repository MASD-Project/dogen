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
#include "dogen/test_models/cpp_model/test_data/child_of_a_child1_td.hpp"
#include "dogen/test_models/cpp_model/test_data/child_of_a_child2_td.hpp"
#include "dogen/test_models/cpp_model/test_data/child_via_settings_td.hpp"
#include "dogen/test_models/cpp_model/test_data/parent_with_members_td.hpp"
#include "dogen/test_models/cpp_model/test_data/second_child_without_members_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

}

namespace dogen {
namespace test_models {
namespace cpp_model {

void parent_with_members_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_int(position + 0));
}

parent_with_members_generator::result_type*
parent_with_members_generator::create_ptr(const unsigned int position) {
    if ((position % 3) == 0)
        return dogen::test_models::cpp_model::child_of_a_child2_generator::create_ptr(position);
    if ((position % 3) == 1)
        return dogen::test_models::cpp_model::child_via_settings_generator::create_ptr(position);
    if ((position % 3) == 2)
        return dogen::test_models::cpp_model::second_child_without_members_generator::create_ptr(position);
    return dogen::test_models::cpp_model::child_of_a_child1_generator::create_ptr(position);
}

} } }
