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
#include "dogen/quilt.cpp/test_data/formattables/helper_instance_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/helper_instances_repository_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::quilt::cpp::formattables::helper_instance
create_dogen_quilt_cpp_formattables_helper_instance(const unsigned int position) {
    return dogen::quilt::cpp::formattables::helper_instance_generator::create(position);
}

std::list<dogen::quilt::cpp::formattables::helper_instance> create_std_list_dogen_quilt_cpp_formattables_helper_instance(unsigned int position) {
    std::list<dogen::quilt::cpp::formattables::helper_instance> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_quilt_cpp_formattables_helper_instance(position + i));
    }
    return r;
}

std::unordered_map<std::string, std::list<dogen::quilt::cpp::formattables::helper_instance> > create_std_unordered_map_std_string_std_list_dogen_quilt_cpp_formattables_helper_instance_(unsigned int position) {
    std::unordered_map<std::string, std::list<dogen::quilt::cpp::formattables::helper_instance> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_list_dogen_quilt_cpp_formattables_helper_instance(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

helper_instances_repository_generator::helper_instances_repository_generator() : position_(0) { }

void helper_instances_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.helper_instances_by_name(create_std_unordered_map_std_string_std_list_dogen_quilt_cpp_formattables_helper_instance_(position + 0));
}

helper_instances_repository_generator::result_type
helper_instances_repository_generator::create(const unsigned int position) {
    helper_instances_repository r;
    helper_instances_repository_generator::populate(position, r);
    return r;
}

helper_instances_repository_generator::result_type*
helper_instances_repository_generator::create_ptr(const unsigned int position) {
    helper_instances_repository* p = new helper_instances_repository();
    helper_instances_repository_generator::populate(position, *p);
    return p;
}

helper_instances_repository_generator::result_type
helper_instances_repository_generator::operator()() {
    return create(position_++);
}

} } } }
