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
#include "dogen/yarn/test_data/name_tree_td.hpp"
#include "dogen/quilt.cpp/test_data/properties/property_info_td.hpp"
#include "dogen/quilt.cpp/test_data/properties/nested_type_info_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::quilt::cpp::properties::nested_type_info
create_dogen_quilt_cpp_properties_nested_type_info(const unsigned int position) {
    return dogen::quilt::cpp::properties::nested_type_info_generator::create(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

dogen::yarn::name_tree
create_dogen_yarn_name_tree(const unsigned int position) {
    return dogen::yarn::name_tree_generator::create(position);
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

property_info_generator::property_info_generator() : position_(0) { }

void property_info_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_std_string(position + 0));
    v.qualified_name(create_std_string(position + 1));
    v.documentation(create_std_string(position + 2));
    v.type(create_dogen_quilt_cpp_properties_nested_type_info(position + 3));
    v.is_immutable(create_bool(position + 4));
    v.is_fluent(create_bool(position + 5));
    v.id(create_std_string(position + 6));
    v.name_tree(create_dogen_yarn_name_tree(position + 7));
}

property_info_generator::result_type
property_info_generator::create(const unsigned int position) {
    property_info r;
    property_info_generator::populate(position, r);
    return r;
}

property_info_generator::result_type*
property_info_generator::create_ptr(const unsigned int position) {
    property_info* p = new property_info();
    property_info_generator::populate(position, *p);
    return p;
}

property_info_generator::result_type
property_info_generator::operator()() {
    return create(position_++);
}

} } } }
