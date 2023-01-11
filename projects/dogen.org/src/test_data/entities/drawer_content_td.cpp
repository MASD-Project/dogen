/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#include "dogen.org/test_data/entities/drawer_content_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen::org::entities {

drawer_content_generator::drawer_content_generator() : position_(0) { }

void drawer_content_generator::
populate(const unsigned int position, result_type& v) {
    v.key(create_std_string(position + 0));
    v.value(create_std_string(position + 1));
}

drawer_content_generator::result_type
drawer_content_generator::create(const unsigned int position) {
    drawer_content r;
    drawer_content_generator::populate(position, r);
    return r;
}

drawer_content_generator::result_type*
drawer_content_generator::create_ptr(const unsigned int position) {
    drawer_content* p = new drawer_content();
    drawer_content_generator::populate(position, *p);
    return p;
}

drawer_content_generator::result_type
drawer_content_generator::operator()() {
    return create(position_++);
}

}
