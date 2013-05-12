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
#include "dogen/cpp/test_data/class_view_model_td.hpp"
#include "dogen/cpp/test_data/parent_view_model_td.hpp"
#include "dogen/cpp/test_data/property_view_model_td.hpp"

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

dogen::cpp::property_view_model
create_dogen_cpp_property_view_model(const unsigned int position) {
    return dogen::cpp::property_view_model_generator::create(position);
}

std::list<dogen::cpp::property_view_model> create_std_list_dogen_cpp_property_view_model(unsigned int position) {
    std::list<dogen::cpp::property_view_model> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_cpp_property_view_model(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

dogen::cpp::parent_view_model
create_dogen_cpp_parent_view_model(const unsigned int position) {
    return dogen::cpp::parent_view_model_generator::create(position);
}

std::list<dogen::cpp::parent_view_model> create_std_list_dogen_cpp_parent_view_model(unsigned int position) {
    std::list<dogen::cpp::parent_view_model> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_cpp_parent_view_model(position + i));
    }
    return r;
}

std::pair<std::string, std::string>
create_std_pair_std_string_std_string(unsigned int position) {
    std::pair<std::string, std::string> r(
        create_std_string(position),
        create_std_string(position));
    return r;
}

std::vector<std::pair<std::string, std::string> > create_std_vector_std_pair_std_string_std_string_(unsigned int position) {
    std::vector<std::pair<std::string, std::string> > r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_std_pair_std_string_std_string(position + i));
    }
    return r;
}

}

namespace dogen {
namespace cpp {

class_view_model_generator::class_view_model_generator() : position_(0) { }

void class_view_model_generator::
populate(const unsigned int position, result_type& v) {
    v.namespaces(create_std_list_std_string(position + 0));
    v.name(create_std_string(position + 1));
    v.properties(create_std_list_dogen_cpp_property_view_model(position + 2));
    v.all_properties(create_std_list_dogen_cpp_property_view_model(position + 3));
    v.has_primitive_properties(create_bool(position + 4));
    v.requires_stream_manipulators(create_bool(position + 5));
    v.requires_manual_move_constructor(create_bool(position + 6));
    v.requires_manual_default_constructor(create_bool(position + 7));
    v.parents(create_std_list_dogen_cpp_parent_view_model(position + 8));
    v.is_parent(create_bool(position + 9));
    v.documentation(create_std_string(position + 10));
    v.original_parent_name(create_std_string(position + 11));
    v.original_parent_name_qualified(create_std_string(position + 12));
    v.leaves(create_std_list_std_string(position + 13));
    v.implementation_specific_parameters(create_std_vector_std_pair_std_string_std_string_(position + 14));
    v.is_comparable(create_bool(position + 15));
    v.is_visitable(create_bool(position + 16));
    v.is_immutable(create_bool(position + 17));
    v.is_original_parent_visitable(create_bool(position + 18));
}

class_view_model_generator::result_type
class_view_model_generator::create(const unsigned int position) {
    class_view_model r;
    class_view_model_generator::populate(position, r);
    return r;
}
class_view_model_generator::result_type*
class_view_model_generator::create_ptr(const unsigned int position) {
    class_view_model* p = new class_view_model();
    class_view_model_generator::populate(position, *p);
    return p;
}

class_view_model_generator::result_type
class_view_model_generator::operator()() {
    return create(position_++);
}

} }
