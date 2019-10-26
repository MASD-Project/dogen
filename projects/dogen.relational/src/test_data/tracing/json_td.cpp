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
#include "dogen.relational/test_data/tracing/json_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen::relational::tracing {

json_generator::json_generator() : position_(0) { }

void json_generator::
populate(const unsigned int position, result_type& v) {
    v.value(create_std_string(position + 1));
}

json_generator::result_type
json_generator::create(const unsigned int position) {
    json r;
    json_generator::populate(position, r);
    return r;
}

json_generator::result_type*
json_generator::create_ptr(const unsigned int position) {
    json* r = new json();
    json_generator::populate(position, *r);
    return r;
}

json_generator::result_type
json_generator::operator()() {
    return create(position_++);
}

}
