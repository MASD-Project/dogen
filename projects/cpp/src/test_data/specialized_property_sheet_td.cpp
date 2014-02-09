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
#include "dogen/cpp/test_data/specialized_property_sheet_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace cpp {

specialized_property_sheet_generator::specialized_property_sheet_generator() : position_(0) { }

void specialized_property_sheet_generator::
populate(const unsigned int position, result_type& v) {
    v.generate_header_guards(create_bool(position + 0));
    v.split_project(create_bool(position + 1));
    v.source_directory(create_std_string(position + 2));
    v.include_directory(create_std_string(position + 3));
    v.header_file_extension(create_std_string(position + 4));
    v.implementation_file_extension(create_std_string(position + 5));
    v.forward_declaration_postfix(create_std_string(position + 6));
}

specialized_property_sheet_generator::result_type
specialized_property_sheet_generator::create(const unsigned int position) {
    specialized_property_sheet r;
    specialized_property_sheet_generator::populate(position, r);
    return r;
}
specialized_property_sheet_generator::result_type*
specialized_property_sheet_generator::create_ptr(const unsigned int position) {
    specialized_property_sheet* p = new specialized_property_sheet();
    specialized_property_sheet_generator::populate(position, *p);
    return p;
}

specialized_property_sheet_generator::result_type
specialized_property_sheet_generator::operator()() {
    return create(position_++);
}

} }
