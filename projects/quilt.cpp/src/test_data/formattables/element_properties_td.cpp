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
#include "dogen/formatters/test_data/decoration_configuration_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/profile_group_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/aspect_properties_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/odb_configuration_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/element_properties_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/formatter_properties_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/helper_configuration_td.hpp"

namespace {

dogen::formatters::decoration_configuration
create_dogen_formatters_decoration_configuration(const unsigned int position) {
    return dogen::formatters::decoration_configuration_generator::create(position);
}

boost::optional<dogen::formatters::decoration_configuration>
create_boost_optional_dogen_formatters_decoration_configuration(unsigned int position) {
    boost::optional<dogen::formatters::decoration_configuration> r(
        create_dogen_formatters_decoration_configuration(position));
    return r;
}

dogen::quilt::cpp::formattables::aspect_properties
create_dogen_quilt_cpp_formattables_aspect_properties(const unsigned int position) {
    return dogen::quilt::cpp::formattables::aspect_properties_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::quilt::cpp::formattables::formatter_properties
create_dogen_quilt_cpp_formattables_formatter_properties(const unsigned int position) {
    return dogen::quilt::cpp::formattables::formatter_properties_generator::create(position);
}

std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_properties> create_std_unordered_map_std_string_dogen_quilt_cpp_formattables_formatter_properties(unsigned int position) {
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_quilt_cpp_formattables_formatter_properties(position + i)));
    }
    return r;
}

dogen::quilt::cpp::formattables::helper_configuration
create_dogen_quilt_cpp_formattables_helper_configuration(const unsigned int position) {
    return dogen::quilt::cpp::formattables::helper_configuration_generator::create(position);
}

std::list<dogen::quilt::cpp::formattables::helper_configuration> create_std_list_dogen_quilt_cpp_formattables_helper_configuration(unsigned int position) {
    std::list<dogen::quilt::cpp::formattables::helper_configuration> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_quilt_cpp_formattables_helper_configuration(position + i));
    }
    return r;
}

std::unordered_map<std::string, std::string> create_std_unordered_map_std_string_std_string(unsigned int position) {
    std::unordered_map<std::string, std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_string(position + i)));
    }
    return r;
}

dogen::quilt::cpp::formattables::profile_group
create_dogen_quilt_cpp_formattables_profile_group(const unsigned int position) {
    return dogen::quilt::cpp::formattables::profile_group_generator::create(position);
}

boost::optional<dogen::quilt::cpp::formattables::profile_group>
create_boost_optional_dogen_quilt_cpp_formattables_profile_group(unsigned int position) {
    boost::optional<dogen::quilt::cpp::formattables::profile_group> r(
        create_dogen_quilt_cpp_formattables_profile_group(position));
    return r;
}

dogen::quilt::cpp::formattables::odb_configuration
create_dogen_quilt_cpp_formattables_odb_configuration(const unsigned int position) {
    return dogen::quilt::cpp::formattables::odb_configuration_generator::create(position);
}

boost::optional<dogen::quilt::cpp::formattables::odb_configuration>
create_boost_optional_dogen_quilt_cpp_formattables_odb_configuration(unsigned int position) {
    boost::optional<dogen::quilt::cpp::formattables::odb_configuration> r(
        create_dogen_quilt_cpp_formattables_odb_configuration(position));
    return r;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

element_properties_generator::element_properties_generator() : position_(0) { }

void element_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.decoration_configuration(create_boost_optional_dogen_formatters_decoration_configuration(position + 0));
    v.aspect_properties(create_dogen_quilt_cpp_formattables_aspect_properties(position + 1));
    v.formatter_properties(create_std_unordered_map_std_string_dogen_quilt_cpp_formattables_formatter_properties(position + 2));
    v.helper_configurations(create_std_list_dogen_quilt_cpp_formattables_helper_configuration(position + 3));
    v.canonical_formatter_to_formatter(create_std_unordered_map_std_string_std_string(position + 4));
    v.local_profile_group(create_boost_optional_dogen_quilt_cpp_formattables_profile_group(position + 5));
    v.odb_configuration(create_boost_optional_dogen_quilt_cpp_formattables_odb_configuration(position + 6));
}

element_properties_generator::result_type
element_properties_generator::create(const unsigned int position) {
    element_properties r;
    element_properties_generator::populate(position, r);
    return r;
}

element_properties_generator::result_type*
element_properties_generator::create_ptr(const unsigned int position) {
    element_properties* p = new element_properties();
    element_properties_generator::populate(position, *p);
    return p;
}

element_properties_generator::result_type
element_properties_generator::operator()() {
    return create(position_++);
}

} } } }
