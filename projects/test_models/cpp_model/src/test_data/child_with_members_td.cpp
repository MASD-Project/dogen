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
#include "dogen/test_models/cpp_model/test_data/child_with_members_td.hpp"
#include "dogen/test_models/cpp_model/test_data/parent_without_members_td.hpp"

namespace {

unsigned int create_unsigned_int(const unsigned int position) {
    return static_cast<unsigned int>(position);
}

}

namespace dogen {
namespace test_models {
namespace cpp_model {

child_with_members_generator::child_with_members_generator() : position_(0) { }

void child_with_members_generator::
populate(const unsigned int position, result_type& v) {
    dogen::test_models::cpp_model::parent_without_members_generator::populate(position, v);
    v.prop_0(create_unsigned_int(position + 0));
}

child_with_members_generator::result_type
child_with_members_generator::create(const unsigned int position) {
    child_with_members r;
    child_with_members_generator::populate(position, r);
    return r;
}

child_with_members_generator::result_type*
child_with_members_generator::create_ptr(const unsigned int position) {
    child_with_members* p = new child_with_members();
    child_with_members_generator::populate(position, *p);
    return p;
}

child_with_members_generator::result_type
child_with_members_generator::operator()() {
    return create(position_++);
}

} } }
