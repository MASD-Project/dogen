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
#include "dogen.coding/test_data/meta_model/name_td.hpp"
#include "dogen.generation.cpp/test_data/formattables/model_td.hpp"
#include "dogen.generation.cpp/test_data/formattables/formattable_td.hpp"
#include "dogen.generation.cpp/test_data/formattables/cpp_standards_td.hpp"
#include "dogen.generation.cpp/test_data/formattables/facet_properties_td.hpp"
#include "dogen.generation.cpp/test_data/formattables/streaming_properties_td.hpp"

namespace {

dogen::coding::meta_model::name
create_dogen_coding_meta_model_name(const unsigned int position) {
    return dogen::coding::meta_model::name_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::generation::cpp::formattables::streaming_properties
create_dogen_generation_cpp_formattables_streaming_properties(const unsigned int position) {
    return dogen::generation::cpp::formattables::streaming_properties_generator::create(position);
}

std::unordered_map<std::string, dogen::generation::cpp::formattables::streaming_properties> create_std_unordered_map_std_string_dogen_generation_cpp_formattables_streaming_properties(unsigned int position) {
    std::unordered_map<std::string, dogen::generation::cpp::formattables::streaming_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_generation_cpp_formattables_streaming_properties(position + i)));
    }
    return r;
}

dogen::generation::cpp::formattables::formattable
create_dogen_generation_cpp_formattables_formattable(const unsigned int position) {
    return dogen::generation::cpp::formattables::formattable_generator::create(position);
}

std::unordered_map<std::string, dogen::generation::cpp::formattables::formattable> create_std_unordered_map_std_string_dogen_generation_cpp_formattables_formattable(unsigned int position) {
    std::unordered_map<std::string, dogen::generation::cpp::formattables::formattable> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_generation_cpp_formattables_formattable(position + i)));
    }
    return r;
}

dogen::generation::cpp::formattables::facet_properties
create_dogen_generation_cpp_formattables_facet_properties(const unsigned int position) {
    return dogen::generation::cpp::formattables::facet_properties_generator::create(position);
}

std::unordered_map<std::string, dogen::generation::cpp::formattables::facet_properties> create_std_unordered_map_std_string_dogen_generation_cpp_formattables_facet_properties(unsigned int position) {
    std::unordered_map<std::string, dogen::generation::cpp::formattables::facet_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_generation_cpp_formattables_facet_properties(position + i)));
    }
    return r;
}

dogen::generation::cpp::formattables::cpp_standards
create_dogen_generation_cpp_formattables_cpp_standards(const unsigned int position) {
    return dogen::generation::cpp::formattables::cpp_standards_generator::create(position);
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace dogen::generation::cpp::formattables {

model_generator::model_generator() : position_(0) { }

void model_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_dogen_coding_meta_model_name(position + 0));
    v.streaming_properties(create_std_unordered_map_std_string_dogen_generation_cpp_formattables_streaming_properties(position + 1));
    v.formattables(create_std_unordered_map_std_string_dogen_generation_cpp_formattables_formattable(position + 2));
    v.facet_properties(create_std_unordered_map_std_string_dogen_generation_cpp_formattables_facet_properties(position + 3));
    v.cpp_standard(create_dogen_generation_cpp_formattables_cpp_standards(position + 4));
    v.odb_databases(create_std_list_std_string(position + 5));
    v.odb_sql_name_case(create_std_string(position + 6));
    v.project_items(create_std_list_std_string(position + 7));
}

model_generator::result_type
model_generator::create(const unsigned int position) {
    model r;
    model_generator::populate(position, r);
    return r;
}

model_generator::result_type*
model_generator::create_ptr(const unsigned int position) {
    model* p = new model();
    model_generator::populate(position, *p);
    return p;
}

model_generator::result_type
model_generator::operator()() {
    return create(position_++);
}

}
