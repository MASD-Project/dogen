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
#include "dogen/cpp/test_data/settings/opaque_settings_td.hpp"
#include "dogen/cpp/test_data/formattables/property_info_td.hpp"
#include "dogen/cpp/test_data/formattables/nested_type_info_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::cpp::formattables::nested_type_info
create_dogen_cpp_formattables_nested_type_info(const unsigned int position) {
    return dogen::cpp::formattables::nested_type_info_generator::create(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

dogen::cpp::settings::opaque_settings*
create_dogen_cpp_settings_opaque_settings_ptr(const unsigned int position) {
    return dogen::cpp::settings::opaque_settings_generator::create_ptr(position);
}

boost::shared_ptr<dogen::cpp::settings::opaque_settings>
create_boost_shared_ptr_dogen_cpp_settings_opaque_settings(unsigned int position) {
    boost::shared_ptr<dogen::cpp::settings::opaque_settings> r(
        create_dogen_cpp_settings_opaque_settings_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::cpp::settings::opaque_settings> > create_std_unordered_map_std_string_boost_shared_ptr_dogen_cpp_settings_opaque_settings_(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<dogen::cpp::settings::opaque_settings> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_dogen_cpp_settings_opaque_settings(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace cpp {
namespace formattables {

property_info_generator::property_info_generator() : position_(0) { }

void property_info_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_std_string(position + 0));
    v.qualified_name(create_std_string(position + 1));
    v.documentation(create_std_string(position + 2));
    v.type(create_dogen_cpp_formattables_nested_type_info(position + 3));
    v.is_immutable(create_bool(position + 4));
    v.is_fluent(create_bool(position + 5));
    v.opaque_settings(create_std_unordered_map_std_string_boost_shared_ptr_dogen_cpp_settings_opaque_settings_(position + 6));
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

} } }
