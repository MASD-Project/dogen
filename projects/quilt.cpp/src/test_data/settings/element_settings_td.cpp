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
#include "dogen/quilt.cpp/test_data/settings/aspect_settings_td.hpp"
#include "dogen/quilt.cpp/test_data/settings/opaque_settings_td.hpp"
#include "dogen/quilt.cpp/test_data/settings/element_settings_td.hpp"

namespace {

dogen::quilt::cpp::settings::aspect_settings
create_dogen_quilt_cpp_settings_aspect_settings(const unsigned int position) {
    return dogen::quilt::cpp::settings::aspect_settings_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::quilt::cpp::settings::opaque_settings*
create_dogen_quilt_cpp_settings_opaque_settings_ptr(const unsigned int position) {
    return dogen::quilt::cpp::settings::opaque_settings_generator::create_ptr(position);
}

boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings>
create_boost_shared_ptr_dogen_quilt_cpp_settings_opaque_settings(unsigned int position) {
    boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> r(
        create_dogen_quilt_cpp_settings_opaque_settings_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> > create_std_unordered_map_std_string_boost_shared_ptr_dogen_quilt_cpp_settings_opaque_settings_(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_dogen_quilt_cpp_settings_opaque_settings(position + i)));
    }
    return r;
}

std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> > > create_std_unordered_map_std_string_std_unordered_map_std_string_boost_shared_ptr_dogen_quilt_cpp_settings_opaque_settings__(unsigned int position) {
    std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> > > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_unordered_map_std_string_boost_shared_ptr_dogen_quilt_cpp_settings_opaque_settings_(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace settings {

element_settings_generator::element_settings_generator() : position_(0) { }

void element_settings_generator::
populate(const unsigned int position, result_type& v) {
    v.aspect_settings(create_dogen_quilt_cpp_settings_aspect_settings(position + 0));
    v.opaque_settings(create_std_unordered_map_std_string_boost_shared_ptr_dogen_quilt_cpp_settings_opaque_settings_(position + 1));
    v.opaque_settings_for_property(create_std_unordered_map_std_string_std_unordered_map_std_string_boost_shared_ptr_dogen_quilt_cpp_settings_opaque_settings__(position + 2));
}

element_settings_generator::result_type
element_settings_generator::create(const unsigned int position) {
    element_settings r;
    element_settings_generator::populate(position, r);
    return r;
}

element_settings_generator::result_type*
element_settings_generator::create_ptr(const unsigned int position) {
    element_settings* p = new element_settings();
    element_settings_generator::populate(position, *p);
    return p;
}

element_settings_generator::result_type
element_settings_generator::operator()() {
    return create(position_++);
}

} } } }
