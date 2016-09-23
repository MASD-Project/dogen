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
#include "dogen/quilt.cpp/test_data/formattables/aspect_configuration_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/aspect_properties_repository_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::quilt::cpp::formattables::aspect_configuration
create_dogen_quilt_cpp_formattables_aspect_configuration(const unsigned int position) {
    return dogen::quilt::cpp::formattables::aspect_configuration_generator::create(position);
}

std::unordered_map<std::string, dogen::quilt::cpp::formattables::aspect_configuration> create_std_unordered_map_std_string_dogen_quilt_cpp_formattables_aspect_configuration(unsigned int position) {
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::aspect_configuration> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_quilt_cpp_formattables_aspect_configuration(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

aspect_properties_repository_generator::aspect_properties_repository_generator() : position_(0) { }

void aspect_properties_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.by_id(create_std_unordered_map_std_string_dogen_quilt_cpp_formattables_aspect_configuration(position + 0));
}

aspect_properties_repository_generator::result_type
aspect_properties_repository_generator::create(const unsigned int position) {
    aspect_properties_repository r;
    aspect_properties_repository_generator::populate(position, r);
    return r;
}

aspect_properties_repository_generator::result_type*
aspect_properties_repository_generator::create_ptr(const unsigned int position) {
    aspect_properties_repository* p = new aspect_properties_repository();
    aspect_properties_repository_generator::populate(position, *p);
    return p;
}

aspect_properties_repository_generator::result_type
aspect_properties_repository_generator::operator()() {
    return create(position_++);
}

} } } }
