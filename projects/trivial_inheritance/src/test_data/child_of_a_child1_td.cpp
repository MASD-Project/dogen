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
#include "dogen/trivial_inheritance/test_data/child_of_a_child1_td.hpp"
#include "dogen/trivial_inheritance/test_data/third_child_with_members_td.hpp"



namespace dogen {
namespace trivial_inheritance {

child_of_a_child1_generator::child_of_a_child1_generator() : position_(0) { }


child_of_a_child1_generator::result_type
child_of_a_child1_generator::create(const unsigned int position) {
    child_of_a_child1 r;
    dogen::trivial_inheritance::third_child_with_members_generator::populate(position, r);
    return r;
}

child_of_a_child1_generator::result_type
child_of_a_child1_generator::operator()() {
    return create(position_++);
}

} }
