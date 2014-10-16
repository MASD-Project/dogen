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
#include "dogen/cpp/test_data/class_aspects_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace cpp {

class_aspects_generator::class_aspects_generator() : position_(0) { }

void class_aspects_generator::
populate(const unsigned int position, result_type& v) {
    v.enable_complete_constructor(create_bool(position + 0));
    v.generate_defaulted_functions(create_bool(position + 1));
    v.generate_explicit_default_constructor(create_bool(position + 2));
    v.generate_explicit_move_constructor(create_bool(position + 3));
    v.generate_explicit_destructor(create_bool(position + 4));
    v.destructor_is_pure_virtual(create_bool(position + 5));
    v.generate_explicit_assignment_operator(create_bool(position + 6));
    v.generate_complete_constructor(create_bool(position + 7));
    v.generate_equality(create_bool(position + 8));
}

class_aspects_generator::result_type
class_aspects_generator::create(const unsigned int position) {
    class_aspects r;
    class_aspects_generator::populate(position, r);
    return r;
}
class_aspects_generator::result_type*
class_aspects_generator::create_ptr(const unsigned int position) {
    class_aspects* p = new class_aspects();
    class_aspects_generator::populate(position, *p);
    return p;
}

class_aspects_generator::result_type
class_aspects_generator::operator()() {
    return create(position_++);
}

} }
