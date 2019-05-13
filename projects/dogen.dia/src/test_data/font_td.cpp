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
#include "dogen.dia/test_data/font_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen::dia {

font_generator::font_generator() : position_(0) { }

void font_generator::
populate(const unsigned int position, result_type& v) {
    v.family(create_std_string(position + 0));
    v.style(create_std_string(position + 1));
    v.name(create_std_string(position + 2));
}

font_generator::result_type
font_generator::create(const unsigned int position) {
    font r;
    font_generator::populate(position, r);
    return r;
}

font_generator::result_type*
font_generator::create_ptr(const unsigned int position) {
    font* p = new font();
    font_generator::populate(position, *p);
    return p;
}

font_generator::result_type
font_generator::operator()() {
    return create(position_++);
}

}
