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
#include "dogen/cpp/test_data/formattables/nested_type_info_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

dogen::cpp::formattables::nested_type_info
create_dogen_cpp_formattables_nested_type_info(const unsigned int) {
    return dogen::cpp::formattables::nested_type_info();
}

std::list<dogen::cpp::formattables::nested_type_info> create_std_list_dogen_cpp_formattables_nested_type_info(unsigned int position) {
    std::list<dogen::cpp::formattables::nested_type_info> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_cpp_formattables_nested_type_info(position + i));
    }
    return r;
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
namespace formattables {

nested_type_info_generator::nested_type_info_generator() : position_(0) { }

void nested_type_info_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_std_string(position + 0));
    v.qualified_name(create_std_string(position + 1));
    v.identifiable_name(create_std_string(position + 2));
    v.complete_name(create_std_string(position + 3));
    v.complete_identifiable_name(create_std_string(position + 4));
    v.is_primitive(create_bool(position + 5));
    v.is_enumeration(create_bool(position + 6));
    v.is_string_like(create_bool(position + 7));
    v.is_char_like(create_bool(position + 8));
    v.is_int_like(create_bool(position + 9));
    v.is_sequence_container(create_bool(position + 10));
    v.is_associative_container(create_bool(position + 11));
    v.is_smart_pointer(create_bool(position + 12));
    v.is_optional_like(create_bool(position + 13));
    v.is_variant_like(create_bool(position + 14));
    v.children(create_std_list_dogen_cpp_formattables_nested_type_info(position + 15));
    v.namespaces(create_std_list_std_string(position + 16));
    v.is_filesystem_path(create_bool(position + 17));
    v.is_date(create_bool(position + 18));
    v.is_ptime(create_bool(position + 19));
    v.is_time_duration(create_bool(position + 20));
    v.is_pair(create_bool(position + 21));
    v.is_ptree(create_bool(position + 22));
}

nested_type_info_generator::result_type
nested_type_info_generator::create(const unsigned int position) {
    nested_type_info r;
    nested_type_info_generator::populate(position, r);
    return r;
}

nested_type_info_generator::result_type*
nested_type_info_generator::create_ptr(const unsigned int position) {
    nested_type_info* p = new nested_type_info();
    nested_type_info_generator::populate(position, *p);
    return p;
}

nested_type_info_generator::result_type
nested_type_info_generator::operator()() {
    return create(position_++);
}

} } }
