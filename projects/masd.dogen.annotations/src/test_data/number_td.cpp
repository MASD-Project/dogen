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
#include "masd.dogen.annotations/test_data/value_td.hpp"
#include "masd.dogen.annotations/test_data/number_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

}

namespace masd::dogen::annotations {

number_generator::number_generator() : position_(0) { }

void number_generator::
populate(const unsigned int position, result_type& v) {
    masd::dogen::annotations::value_generator::populate(position, v);
    v.content(create_int(position + 0));
}

number_generator::result_type
number_generator::create(const unsigned int position) {
    number r;
    number_generator::populate(position, r);
    return r;
}

number_generator::result_type*
number_generator::create_ptr(const unsigned int position) {
    number* p = new number();
    number_generator::populate(position, *p);
    return p;
}

number_generator::result_type
number_generator::operator()() {
    return create(position_++);
}

}
