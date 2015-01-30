/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/cpp/test_data/inheritance_td.hpp"
#include "dogen/cpp/test_data/parent_info_td.hpp"

namespace {

dogen::cpp::parent_info
create_dogen_cpp_parent_info(const unsigned int position) {
    return dogen::cpp::parent_info_generator::create(position);
}

std::list<dogen::cpp::parent_info> create_std_list_dogen_cpp_parent_info(unsigned int position) {
    std::list<dogen::cpp::parent_info> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_cpp_parent_info(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
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

}

namespace dogen {
namespace cpp {

inheritance_generator::inheritance_generator() : position_(0) { }

void inheritance_generator::
populate(const unsigned int position, result_type& v) {
    v.parents(create_std_list_dogen_cpp_parent_info(position + 0));
    v.is_parent(create_bool(position + 1));
    v.original_parent_name(create_std_string(position + 2));
    v.original_parent_name_qualified(create_std_string(position + 3));
    v.leaves(create_std_list_std_string(position + 4));
    v.is_final(create_bool(position + 5));
}

inheritance_generator::result_type
inheritance_generator::create(const unsigned int position) {
    inheritance r;
    inheritance_generator::populate(position, r);
    return r;
}
inheritance_generator::result_type*
inheritance_generator::create_ptr(const unsigned int position) {
    inheritance* p = new inheritance();
    inheritance_generator::populate(position, *p);
    return p;
}

inheritance_generator::result_type
inheritance_generator::operator()() {
    return create(position_++);
}

} }
