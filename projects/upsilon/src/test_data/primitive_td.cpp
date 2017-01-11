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
#include <sstream>
#include "dogen/upsilon/test_data/type_td.hpp"
#include "dogen/upsilon/test_data/primitive_td.hpp"
#include "dogen/upsilon/test_data/intrinsic_types_td.hpp"

namespace {

dogen::upsilon::intrinsic_types
create_dogen_upsilon_intrinsic_types(const unsigned int position) {
    return dogen::upsilon::intrinsic_types_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace upsilon {

primitive_generator::primitive_generator() : position_(0) { }

void primitive_generator::
populate(const unsigned int position, result_type& v) {
    dogen::upsilon::type_generator::populate(position, v);
    v.intrinsic(create_dogen_upsilon_intrinsic_types(position + 0));
    v.default_value(create_std_string(position + 1));
}

primitive_generator::result_type
primitive_generator::create(const unsigned int position) {
    primitive r;
    primitive_generator::populate(position, r);
    return r;
}

primitive_generator::result_type*
primitive_generator::create_ptr(const unsigned int position) {
    primitive* p = new primitive();
    primitive_generator::populate(position, *p);
    return p;
}

primitive_generator::result_type
primitive_generator::operator()() {
    return create(position_++);
}

} }
