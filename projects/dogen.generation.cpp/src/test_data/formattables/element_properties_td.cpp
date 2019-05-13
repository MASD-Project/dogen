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
#include "dogen.generation.cpp/test_data/formattables/odb_properties_td.hpp"
#include "dogen.generation.cpp/test_data/formattables/aspect_properties_td.hpp"
#include "dogen.generation.cpp/test_data/formattables/helper_properties_td.hpp"
#include "dogen.generation.cpp/test_data/formattables/element_properties_td.hpp"
#include "dogen.generation.cpp/test_data/formattables/artefact_properties_td.hpp"
#include "dogen.generation.cpp/test_data/formattables/test_data_properties_td.hpp"

namespace {

dogen::generation::cpp::formattables::aspect_properties
create_dogen_generation_cpp_formattables_aspect_properties(const unsigned int position) {
    return dogen::generation::cpp::formattables::aspect_properties_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::generation::cpp::formattables::artefact_properties
create_dogen_generation_cpp_formattables_artefact_properties(const unsigned int position) {
    return dogen::generation::cpp::formattables::artefact_properties_generator::create(position);
}

std::unordered_map<std::string, dogen::generation::cpp::formattables::artefact_properties> create_std_unordered_map_std_string_dogen_generation_cpp_formattables_artefact_properties(unsigned int position) {
    std::unordered_map<std::string, dogen::generation::cpp::formattables::artefact_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_generation_cpp_formattables_artefact_properties(position + i)));
    }
    return r;
}

dogen::generation::cpp::formattables::helper_properties
create_dogen_generation_cpp_formattables_helper_properties(const unsigned int position) {
    return dogen::generation::cpp::formattables::helper_properties_generator::create(position);
}

std::list<dogen::generation::cpp::formattables::helper_properties> create_std_list_dogen_generation_cpp_formattables_helper_properties(unsigned int position) {
    std::list<dogen::generation::cpp::formattables::helper_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_generation_cpp_formattables_helper_properties(position + i));
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

dogen::generation::cpp::formattables::odb_properties
create_dogen_generation_cpp_formattables_odb_properties(const unsigned int position) {
    return dogen::generation::cpp::formattables::odb_properties_generator::create(position);
}

boost::optional<dogen::generation::cpp::formattables::odb_properties>
create_boost_optional_dogen_generation_cpp_formattables_odb_properties(unsigned int position) {
    boost::optional<dogen::generation::cpp::formattables::odb_properties> r(
        create_dogen_generation_cpp_formattables_odb_properties(position));
    return r;
}

dogen::generation::cpp::formattables::test_data_properties
create_dogen_generation_cpp_formattables_test_data_properties(const unsigned int position) {
    return dogen::generation::cpp::formattables::test_data_properties_generator::create(position);
}

std::unordered_map<std::string, dogen::generation::cpp::formattables::test_data_properties> create_std_unordered_map_std_string_dogen_generation_cpp_formattables_test_data_properties(unsigned int position) {
    std::unordered_map<std::string, dogen::generation::cpp::formattables::test_data_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_generation_cpp_formattables_test_data_properties(position + i)));
    }
    return r;
}

}

namespace dogen::generation::cpp::formattables {

element_properties_generator::element_properties_generator() : position_(0) { }

void element_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.aspect_properties(create_dogen_generation_cpp_formattables_aspect_properties(position + 0));
    v.artefact_properties(create_std_unordered_map_std_string_dogen_generation_cpp_formattables_artefact_properties(position + 1));
    v.helper_properties(create_std_list_dogen_generation_cpp_formattables_helper_properties(position + 2));
    v.canonical_archetype_to_archetype(create_std_unordered_map_std_string_std_string(position + 3));
    v.odb_properties(create_boost_optional_dogen_generation_cpp_formattables_odb_properties(position + 4));
    v.attribute_level_test_data_properties(create_std_unordered_map_std_string_dogen_generation_cpp_formattables_test_data_properties(position + 5));
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

}
