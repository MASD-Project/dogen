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
#include "dogen/quilt.cpp/test_data/formattables/helper_descriptor_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/helper_configuration_td.hpp"

namespace {

dogen::quilt::cpp::formattables::helper_descriptor
create_dogen_quilt_cpp_formattables_helper_descriptor(const unsigned int position) {
    return dogen::quilt::cpp::formattables::helper_descriptor_generator::create(position);
}

std::list<dogen::quilt::cpp::formattables::helper_descriptor> create_std_list_dogen_quilt_cpp_formattables_helper_descriptor(unsigned int position) {
    std::list<dogen::quilt::cpp::formattables::helper_descriptor> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_quilt_cpp_formattables_helper_descriptor(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

helper_configuration_generator::helper_configuration_generator() : position_(0) { }

void helper_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.current(create_dogen_quilt_cpp_formattables_helper_descriptor(position + 0));
    v.direct_descendants(create_std_list_dogen_quilt_cpp_formattables_helper_descriptor(position + 1));
    v.in_inheritance_relationship(create_bool(position + 2));
}

helper_configuration_generator::result_type
helper_configuration_generator::create(const unsigned int position) {
    helper_configuration r;
    helper_configuration_generator::populate(position, r);
    return r;
}

helper_configuration_generator::result_type*
helper_configuration_generator::create_ptr(const unsigned int position) {
    helper_configuration* p = new helper_configuration();
    helper_configuration_generator::populate(position, *p);
    return p;
}

helper_configuration_generator::result_type
helper_configuration_generator::operator()() {
    return create(position_++);
}

} } } }
