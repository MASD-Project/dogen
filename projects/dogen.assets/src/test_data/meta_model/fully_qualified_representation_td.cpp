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
#include "dogen.assets/test_data/meta_model/fully_qualified_representation_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen::assets::meta_model {

fully_qualified_representation_generator::fully_qualified_representation_generator() : position_(0) { }

void fully_qualified_representation_generator::
populate(const unsigned int position, result_type& v) {
    v.dot(create_std_string(position + 0));
    v.colon(create_std_string(position + 1));
    v.identifiable(create_std_string(position + 2));
}

fully_qualified_representation_generator::result_type
fully_qualified_representation_generator::create(const unsigned int position) {
    fully_qualified_representation r;
    fully_qualified_representation_generator::populate(position, r);
    return r;
}

fully_qualified_representation_generator::result_type*
fully_qualified_representation_generator::create_ptr(const unsigned int position) {
    fully_qualified_representation* p = new fully_qualified_representation();
    fully_qualified_representation_generator::populate(position, *p);
    return p;
}

fully_qualified_representation_generator::result_type
fully_qualified_representation_generator::operator()() {
    return create(position_++);
}

}
