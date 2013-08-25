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
#include "dogen/om/test_data/cpp_typeref_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

dogen::om::cpp_typeref
create_dogen_om_cpp_typeref(const unsigned int) {
    return dogen::om::cpp_typeref();
}

std::list<dogen::om::cpp_typeref> create_std_list_dogen_om_cpp_typeref(unsigned int position) {
    std::list<dogen::om::cpp_typeref> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_om_cpp_typeref(position + i));
    }
    return r;
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace dogen {
namespace om {

cpp_typeref_generator::cpp_typeref_generator() : position_(0) { }

void cpp_typeref_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_std_string(position + 0));
    v.start_at_global_scope(create_bool(position + 1));
    v.type_arguments(create_std_list_dogen_om_cpp_typeref(position + 2));
    v.namespaces(create_std_list_std_string(position + 3));
}

cpp_typeref_generator::result_type
cpp_typeref_generator::create(const unsigned int position) {
    cpp_typeref r;
    cpp_typeref_generator::populate(position, r);
    return r;
}
cpp_typeref_generator::result_type*
cpp_typeref_generator::create_ptr(const unsigned int position) {
    cpp_typeref* p = new cpp_typeref();
    cpp_typeref_generator::populate(position, *p);
    return p;
}

cpp_typeref_generator::result_type
cpp_typeref_generator::operator()() {
    return create(position_++);
}

} }
