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
#include "dogen/dia/test_data/layer_td.hpp"
#include "dogen/dia/test_data/object_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

dogen::dia::object
create_dogen_dia_object(const unsigned int position) {
    return dogen::dia::object_generator::create(position);
}

std::vector<dogen::dia::object> create_std_vector_dogen_dia_object(unsigned int position) {
    std::vector<dogen::dia::object> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_dia_object(position + i));
    }
    return r;
}

}

namespace dogen {
namespace dia {

layer_generator::layer_generator() : position_(0) { }

void layer_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_std_string(position + 0));
    v.visible(create_bool(position + 1));
    v.active(create_bool(position + 2));
    v.objects(create_std_vector_dogen_dia_object(position + 3));
}

layer_generator::result_type
layer_generator::create(const unsigned int position) {
    layer r;
    layer_generator::populate(position, r);
    return r;
}

layer_generator::result_type*
layer_generator::create_ptr(const unsigned int position) {
    layer* p = new layer();
    layer_generator::populate(position, *p);
    return p;
}

layer_generator::result_type
layer_generator::operator()() {
    return create(position_++);
}

} }
