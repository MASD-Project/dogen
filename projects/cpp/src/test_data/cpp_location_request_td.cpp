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
#include "dogen/config/test_data/cpp_facet_types_td.hpp"
#include "dogen/cpp/test_data/cpp_aspect_types_td.hpp"
#include "dogen/cpp/test_data/cpp_file_types_td.hpp"
#include "dogen/cpp/test_data/cpp_location_request_td.hpp"

namespace {

dogen::config::cpp_facet_types
create_dogen_config_cpp_facet_types(const unsigned int position) {
    return dogen::config::cpp_facet_types_generator::create(position);
}

dogen::cpp::cpp_file_types
create_dogen_cpp_cpp_file_types(const unsigned int position) {
    return dogen::cpp::cpp_file_types_generator::create(position);
}

dogen::cpp::cpp_aspect_types
create_dogen_cpp_cpp_aspect_types(const unsigned int position) {
    return dogen::cpp::cpp_aspect_types_generator::create(position);
}

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

}

namespace dogen {
namespace cpp {

cpp_location_request_generator::cpp_location_request_generator() : position_(0) { }

void cpp_location_request_generator::
populate(const unsigned int position, result_type& v) {
    v.facet_type(create_dogen_config_cpp_facet_types(position + 0));
    v.file_type(create_dogen_cpp_cpp_file_types(position + 1));
    v.aspect_type(create_dogen_cpp_cpp_aspect_types(position + 2));
    v.model_name(create_std_string(position + 3));
    v.external_package_path(create_std_list_std_string(position + 4));
    v.package_path(create_std_list_std_string(position + 5));
    v.file_name(create_std_string(position + 6));
}

cpp_location_request_generator::result_type
cpp_location_request_generator::create(const unsigned int position) {
    cpp_location_request r;
    cpp_location_request_generator::populate(position, r);
    return r;
}
cpp_location_request_generator::result_type*
cpp_location_request_generator::create_ptr(const unsigned int position) {
    cpp_location_request* p = new cpp_location_request();
    cpp_location_request_generator::populate(position, *p);
    return p;
}

cpp_location_request_generator::result_type
cpp_location_request_generator::operator()() {
    return create(position_++);
}

} }
