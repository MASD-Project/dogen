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
#include "dogen/test_models/compressed/test_data/package1/first_class_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

}

namespace dogen {
namespace test_models {
namespace compressed {
namespace package1 {

first_class_generator::first_class_generator() : position_(0) { }

void first_class_generator::
populate(const unsigned int position, result_type& v) {
    v.public_attribute(create_int(position + 0));
    v.private_attribute(create_int(position + 1));
}

first_class_generator::result_type
first_class_generator::create(const unsigned int position) {
    first_class r;
    first_class_generator::populate(position, r);
    return r;
}

first_class_generator::result_type*
first_class_generator::create_ptr(const unsigned int position) {
    first_class* p = new first_class();
    first_class_generator::populate(position, *p);
    return p;
}

first_class_generator::result_type
first_class_generator::operator()() {
    return create(position_++);
}

} } } }
