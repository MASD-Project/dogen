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
#include "dogen/test_models/cpp_model/test_data/package_8/child_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_7/parent_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

}

namespace dogen {
namespace test_models {
namespace cpp_model {
namespace package_8 {

child_generator::child_generator() : position_(0) { }

void child_generator::
populate(const unsigned int position, result_type& v) {
    dogen::test_models::cpp_model::package_7::parent_generator::populate(position, v);
    v.prop_1(create_int(position + 0));
}

child_generator::result_type
child_generator::create(const unsigned int position) {
    child r;
    child_generator::populate(position, r);
    return r;
}

child_generator::result_type*
child_generator::create_ptr(const unsigned int position) {
    child* p = new child();
    child_generator::populate(position, *p);
    return p;
}

child_generator::result_type
child_generator::operator()() {
    return create(position_++);
}

} } } }
