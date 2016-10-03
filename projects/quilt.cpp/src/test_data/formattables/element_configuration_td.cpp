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
#include "dogen/quilt.cpp/test_data/formattables/facet_configuration_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/aspect_configuration_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/helper_configuration_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/element_configuration_td.hpp"
#include "dogen/quilt.cpp/test_data/formattables/formatter_configuration_td.hpp"

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

dogen::quilt::cpp::formattables::aspect_configuration
create_dogen_quilt_cpp_formattables_aspect_configuration(const unsigned int position) {
    return dogen::quilt::cpp::formattables::aspect_configuration_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::quilt::cpp::formattables::formatter_configuration
create_dogen_quilt_cpp_formattables_formatter_configuration(const unsigned int position) {
    return dogen::quilt::cpp::formattables::formatter_configuration_generator::create(position);
}

std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_configuration> create_std_unordered_map_std_string_dogen_quilt_cpp_formattables_formatter_configuration(unsigned int position) {
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::formatter_configuration> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_quilt_cpp_formattables_formatter_configuration(position + i)));
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

dogen::quilt::cpp::formattables::facet_configuration
create_dogen_quilt_cpp_formattables_facet_configuration(const unsigned int position) {
    return dogen::quilt::cpp::formattables::facet_configuration_generator::create(position);
}

std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_configuration> create_std_unordered_map_std_string_dogen_quilt_cpp_formattables_facet_configuration(unsigned int position) {
    std::unordered_map<std::string, dogen::quilt::cpp::formattables::facet_configuration> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_quilt_cpp_formattables_facet_configuration(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

element_configuration_generator::element_configuration_generator() : position_(0) { }

void element_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.decoration_configuration(create_boost_optional_dogen_formatters_decoration_configuration(position + 0));
    v.aspect_configuration(create_dogen_quilt_cpp_formattables_aspect_configuration(position + 1));
    v.formatter_configurations(create_std_unordered_map_std_string_dogen_quilt_cpp_formattables_formatter_configuration(position + 2));
    v.helper_configurations(create_std_list_dogen_quilt_cpp_formattables_helper_configuration(position + 3));
    v.facet_configurations(create_std_unordered_map_std_string_dogen_quilt_cpp_formattables_facet_configuration(position + 4));
}

element_configuration_generator::result_type
element_configuration_generator::create(const unsigned int position) {
    element_configuration r;
    element_configuration_generator::populate(position, r);
    return r;
}

element_configuration_generator::result_type*
element_configuration_generator::create_ptr(const unsigned int position) {
    element_configuration* p = new element_configuration();
    element_configuration_generator::populate(position, *p);
    return p;
}

element_configuration_generator::result_type
element_configuration_generator::operator()() {
    return create(position_++);
}

} } } }
