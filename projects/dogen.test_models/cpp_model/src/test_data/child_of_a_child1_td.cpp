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
#include "dogen/test_models/cpp_model/test_data/third_child_with_members_td.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

child_of_a_child1_generator::child_of_a_child1_generator() : position_(0) { }

void child_of_a_child1_generator::
populate(const unsigned int position, result_type& v) {
    dogen::test_models::cpp_model::third_child_with_members_generator::populate(position, v);
}

child_of_a_child1_generator::result_type
child_of_a_child1_generator::create(const unsigned int position) {
    child_of_a_child1 r;
    child_of_a_child1_generator::populate(position, r);
    return r;
}

child_of_a_child1_generator::result_type*
child_of_a_child1_generator::create_ptr(const unsigned int position) {
    child_of_a_child1* p = new child_of_a_child1();
    child_of_a_child1_generator::populate(position, *p);
    return p;
}

child_of_a_child1_generator::result_type
child_of_a_child1_generator::operator()() {
    return create(position_++);
}

} } }
