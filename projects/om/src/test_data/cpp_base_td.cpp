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
#include "dogen/om/test_data/cpp_access_specifier_types_td.hpp"
#include "dogen/om/test_data/cpp_base_td.hpp"
#include "dogen/om/test_data/cpp_typeref_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

dogen::om::cpp_access_specifier_types
create_dogen_om_cpp_access_specifier_types(const unsigned int position) {
    return dogen::om::cpp_access_specifier_types_generator::create(position);
}

dogen::om::cpp_typeref
create_dogen_om_cpp_typeref(const unsigned int position) {
    return dogen::om::cpp_typeref_generator::create(position);
}

}

namespace dogen {
namespace om {

cpp_base_generator::cpp_base_generator() : position_(0) { }

void cpp_base_generator::
populate(const unsigned int position, result_type& v) {
    v.is_virtual(create_bool(position + 0));
    v.access(create_dogen_om_cpp_access_specifier_types(position + 1));
    v.type(create_dogen_om_cpp_typeref(position + 2));
}

cpp_base_generator::result_type
cpp_base_generator::create(const unsigned int position) {
    cpp_base r;
    cpp_base_generator::populate(position, r);
    return r;
}
cpp_base_generator::result_type*
cpp_base_generator::create_ptr(const unsigned int position) {
    cpp_base* p = new cpp_base();
    cpp_base_generator::populate(position, *p);
    return p;
}

cpp_base_generator::result_type
cpp_base_generator::operator()() {
    return create(position_++);
}

} }
