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
#include "dogen/om/test_data/cpp_abstract_function_td.hpp"
#include "dogen/om/test_data/cpp_member_function_td.hpp"
#include "dogen/om/test_data/cpp_member_function_types_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

dogen::om::cpp_member_function_types
create_dogen_om_cpp_member_function_types(const unsigned int position) {
    return dogen::om::cpp_member_function_types_generator::create(position);
}

}

namespace dogen {
namespace om {

cpp_member_function_generator::cpp_member_function_generator() : position_(0) { }

void cpp_member_function_generator::
populate(const unsigned int position, result_type& v) {
    dogen::om::cpp_abstract_function_generator::populate(position, v);
    v.is_virtual(create_bool(position + 0));
    v.is_explicit(create_bool(position + 1));
    v.is_pure(create_bool(position + 2));
    v.is_override(create_bool(position + 3));
    v.is_final(create_bool(position + 4));
    v.is_default(create_bool(position + 5));
    v.is_static(create_bool(position + 6));
    v.type(create_dogen_om_cpp_member_function_types(position + 7));
}

cpp_member_function_generator::result_type
cpp_member_function_generator::create(const unsigned int position) {
    cpp_member_function r;
    cpp_member_function_generator::populate(position, r);
    return r;
}
cpp_member_function_generator::result_type*
cpp_member_function_generator::create_ptr(const unsigned int position) {
    cpp_member_function* p = new cpp_member_function();
    cpp_member_function_generator::populate(position, *p);
    return p;
}

cpp_member_function_generator::result_type
cpp_member_function_generator::operator()() {
    return create(position_++);
}

} }
