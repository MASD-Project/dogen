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
#include "dogen/cpp/test_data/qualified_id_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace cpp {

qualified_id_generator::qualified_id_generator() : position_(0) { }

void qualified_id_generator::
populate(const unsigned int position, result_type& v) {
    v.unqualified_id(create_std_string(position + 0));
    v.nested_name_specifier(create_std_list_std_string(position + 1));
    v.start_at_global_scope(create_bool(position + 2));
}

qualified_id_generator::result_type
qualified_id_generator::create(const unsigned int position) {
    qualified_id r;
    qualified_id_generator::populate(position, r);
    return r;
}
qualified_id_generator::result_type*
qualified_id_generator::create_ptr(const unsigned int position) {
    qualified_id* p = new qualified_id();
    qualified_id_generator::populate(position, *p);
    return p;
}

qualified_id_generator::result_type
qualified_id_generator::operator()() {
    return create(position_++);
}

} }
