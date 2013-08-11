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
#include "dogen/cpp/test_data/access_specifier_types_td.hpp"
#include "dogen/cpp/test_data/base_specifier_td.hpp"
#include "dogen/cpp/test_data/qualified_id_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

dogen::cpp::access_specifier_types
create_dogen_cpp_access_specifier_types(const unsigned int position) {
    return dogen::cpp::access_specifier_types_generator::create(position);
}

dogen::cpp::qualified_id
create_dogen_cpp_qualified_id(const unsigned int position) {
    return dogen::cpp::qualified_id_generator::create(position);
}

}

namespace dogen {
namespace cpp {

base_specifier_generator::base_specifier_generator() : position_(0) { }

void base_specifier_generator::
populate(const unsigned int position, result_type& v) {
    v.is_virtual(create_bool(position + 0));
    v.access(create_dogen_cpp_access_specifier_types(position + 1));
    v.name(create_dogen_cpp_qualified_id(position + 2));
}

base_specifier_generator::result_type
base_specifier_generator::create(const unsigned int position) {
    base_specifier r;
    base_specifier_generator::populate(position, r);
    return r;
}
base_specifier_generator::result_type*
base_specifier_generator::create_ptr(const unsigned int position) {
    base_specifier* p = new base_specifier();
    base_specifier_generator::populate(position, *p);
    return p;
}

base_specifier_generator::result_type
base_specifier_generator::operator()() {
    return create(position_++);
}

} }
