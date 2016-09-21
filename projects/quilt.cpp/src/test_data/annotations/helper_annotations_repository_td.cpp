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
#include "dogen/quilt.cpp/test_data/annotations/helper_annotations_td.hpp"
#include "dogen/quilt.cpp/test_data/annotations/helper_annotations_repository_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::quilt::cpp::annotations::helper_annotations
create_dogen_quilt_cpp_annotations_helper_annotations(const unsigned int position) {
    return dogen::quilt::cpp::annotations::helper_annotations_generator::create(position);
}

std::unordered_map<std::string, dogen::quilt::cpp::annotations::helper_annotations> create_std_unordered_map_std_string_dogen_quilt_cpp_annotations_helper_annotations(unsigned int position) {
    std::unordered_map<std::string, dogen::quilt::cpp::annotations::helper_annotations> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_quilt_cpp_annotations_helper_annotations(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

helper_annotations_repository_generator::helper_annotations_repository_generator() : position_(0) { }

void helper_annotations_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.by_id(create_std_unordered_map_std_string_dogen_quilt_cpp_annotations_helper_annotations(position + 0));
}

helper_annotations_repository_generator::result_type
helper_annotations_repository_generator::create(const unsigned int position) {
    helper_annotations_repository r;
    helper_annotations_repository_generator::populate(position, r);
    return r;
}

helper_annotations_repository_generator::result_type*
helper_annotations_repository_generator::create_ptr(const unsigned int position) {
    helper_annotations_repository* p = new helper_annotations_repository();
    helper_annotations_repository_generator::populate(position, *p);
    return p;
}

helper_annotations_repository_generator::result_type
helper_annotations_repository_generator::operator()() {
    return create(position_++);
}

} } } }
