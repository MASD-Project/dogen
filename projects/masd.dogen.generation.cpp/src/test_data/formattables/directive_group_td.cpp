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
#include "masd.dogen.generation.cpp/test_data/formattables/directive_group_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace masd::dogen::generation::cpp::formattables {

directive_group_generator::directive_group_generator() : position_(0) { }

void directive_group_generator::
populate(const unsigned int position, result_type& v) {
    v.primary(create_std_string(position + 0));
    v.secondary(create_std_list_std_string(position + 1));
}

directive_group_generator::result_type
directive_group_generator::create(const unsigned int position) {
    directive_group r;
    directive_group_generator::populate(position, r);
    return r;
}

directive_group_generator::result_type*
directive_group_generator::create_ptr(const unsigned int position) {
    directive_group* p = new directive_group();
    directive_group_generator::populate(position, *p);
    return p;
}

directive_group_generator::result_type
directive_group_generator::operator()() {
    return create(position_++);
}

}
