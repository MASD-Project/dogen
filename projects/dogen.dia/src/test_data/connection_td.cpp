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
#include "dogen.dia/test_data/connection_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen::dia {

connection_generator::connection_generator() : position_(0) { }

void connection_generator::
populate(const unsigned int position, result_type& v) {
    v.handle(create_std_string(position + 0));
    v.to(create_std_string(position + 1));
    v.connection_slot(create_std_string(position + 2));
}

connection_generator::result_type
connection_generator::create(const unsigned int position) {
    connection r;
    connection_generator::populate(position, r);
    return r;
}

connection_generator::result_type*
connection_generator::create_ptr(const unsigned int position) {
    connection* p = new connection();
    connection_generator::populate(position, *p);
    return p;
}

connection_generator::result_type
connection_generator::operator()() {
    return create(position_++);
}

}
