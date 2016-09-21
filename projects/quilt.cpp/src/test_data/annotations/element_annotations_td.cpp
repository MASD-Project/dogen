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
#include "dogen/quilt.cpp/test_data/annotations/opaque_annotations_td.hpp"
#include "dogen/quilt.cpp/test_data/annotations/element_annotations_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::quilt::cpp::annotations::opaque_annotations*
create_dogen_quilt_cpp_annotations_opaque_annotations_ptr(const unsigned int position) {
    return dogen::quilt::cpp::annotations::opaque_annotations_generator::create_ptr(position);
}

boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations>
create_boost_shared_ptr_dogen_quilt_cpp_annotations_opaque_annotations(unsigned int position) {
    boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> r(
        create_dogen_quilt_cpp_annotations_opaque_annotations_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> > create_std_unordered_map_std_string_boost_shared_ptr_dogen_quilt_cpp_annotations_opaque_annotations(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_dogen_quilt_cpp_annotations_opaque_annotations(position + i)));
    }
    return r;
}

std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> > > create_std_unordered_map_std_string_std_unordered_map_std_string_boost_shared_ptr_dogen_quilt_cpp_annotations_opaque_annotations(unsigned int position) {
    std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> > > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_unordered_map_std_string_boost_shared_ptr_dogen_quilt_cpp_annotations_opaque_annotations(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

element_annotations_generator::element_annotations_generator() : position_(0) { }

void element_annotations_generator::
populate(const unsigned int position, result_type& v) {
    v.opaque_annotations(create_std_unordered_map_std_string_boost_shared_ptr_dogen_quilt_cpp_annotations_opaque_annotations(position + 0));
    v.opaque_annotations_for_property(create_std_unordered_map_std_string_std_unordered_map_std_string_boost_shared_ptr_dogen_quilt_cpp_annotations_opaque_annotations(position + 1));
}

element_annotations_generator::result_type
element_annotations_generator::create(const unsigned int position) {
    element_annotations r;
    element_annotations_generator::populate(position, r);
    return r;
}

element_annotations_generator::result_type*
element_annotations_generator::create_ptr(const unsigned int position) {
    element_annotations* p = new element_annotations();
    element_annotations_generator::populate(position, *p);
    return p;
}

element_annotations_generator::result_type
element_annotations_generator::operator()() {
    return create(position_++);
}

} } } }
