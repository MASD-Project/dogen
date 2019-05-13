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
#include "dogen.generation.cpp/test_data/formattables/odb_properties_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

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

std::unordered_map<std::string, std::list<std::string> > create_std_unordered_map_std_string_std_list_std_string(unsigned int position) {
    std::unordered_map<std::string, std::list<std::string> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_list_std_string(position + i)));
    }
    return r;
}

}

namespace dogen::generation::cpp::formattables {

odb_properties_generator::odb_properties_generator() : position_(0) { }

void odb_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.is_value(create_bool(position + 0));
    v.top_level_odb_pragmas(create_std_list_std_string(position + 1));
    v.attribute_level_odb_pragmas(create_std_unordered_map_std_string_std_list_std_string(position + 2));
}

odb_properties_generator::result_type
odb_properties_generator::create(const unsigned int position) {
    odb_properties r;
    odb_properties_generator::populate(position, r);
    return r;
}

odb_properties_generator::result_type*
odb_properties_generator::create_ptr(const unsigned int position) {
    odb_properties* p = new odb_properties();
    odb_properties_generator::populate(position, *p);
    return p;
}

odb_properties_generator::result_type
odb_properties_generator::operator()() {
    return create(position_++);
}

}
