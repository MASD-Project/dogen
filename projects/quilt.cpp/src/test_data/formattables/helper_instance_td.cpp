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
#include "dogen/quilt.cpp/test_data/settings/helper_settings_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/helper_instance_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/helper_instance_properties_td.hpp"

namespace {

dogen::quilt::cpp::formattables::helper_instance_properties
create_dogen_quilt_cpp_formattables_helper_instance_properties(const unsigned int position) {
    return dogen::quilt::cpp::formattables::helper_instance_properties_generator::create(position);
}

std::list<dogen::quilt::cpp::formattables::helper_instance_properties> create_std_list_dogen_quilt_cpp_formattables_helper_instance_properties(unsigned int position) {
    std::list<dogen::quilt::cpp::formattables::helper_instance_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_quilt_cpp_formattables_helper_instance_properties(position + i));
    }
    return r;
}

dogen::quilt::cpp::settings::helper_settings
create_dogen_quilt_cpp_settings_helper_settings(const unsigned int position) {
    return dogen::quilt::cpp::settings::helper_settings_generator::create(position);
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

helper_instance_generator::helper_instance_generator() : position_(0) { }

void helper_instance_generator::
populate(const unsigned int position, result_type& v) {
    v.properties(create_dogen_quilt_cpp_formattables_helper_instance_properties(position + 0));
    v.associated_helpers(create_std_list_dogen_quilt_cpp_formattables_helper_instance_properties(position + 1));
    v.settings(create_dogen_quilt_cpp_settings_helper_settings(position + 2));
}

helper_instance_generator::result_type
helper_instance_generator::create(const unsigned int position) {
    helper_instance r;
    helper_instance_generator::populate(position, r);
    return r;
}

helper_instance_generator::result_type*
helper_instance_generator::create_ptr(const unsigned int position) {
    helper_instance* p = new helper_instance();
    helper_instance_generator::populate(position, *p);
    return p;
}

helper_instance_generator::result_type
helper_instance_generator::operator()() {
    return create(position_++);
}

} } } }
