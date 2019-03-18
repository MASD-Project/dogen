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
#include "masd.dogen.coding/test_data/meta_model/name_td.hpp"
#include "masd.dogen.generation.csharp/test_data/formattables/model_td.hpp"
#include "masd.dogen.generation.csharp/test_data/formattables/formattable_td.hpp"
#include "masd.dogen.generation.csharp/test_data/formattables/aspect_properties_td.hpp"
#include "masd.dogen.generation.csharp/test_data/formattables/assistant_properties_td.hpp"

namespace {

masd::dogen::coding::meta_model::name
create_masd_dogen_coding_meta_model_name(const unsigned int position) {
    return masd::dogen::coding::meta_model::name_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

masd::dogen::generation::csharp::formattables::formattable
create_masd_dogen_generation_csharp_formattables_formattable(const unsigned int position) {
    return masd::dogen::generation::csharp::formattables::formattable_generator::create(position);
}

std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::formattable> create_std_unordered_map_std_string_masd_dogen_generation_csharp_formattables_formattable(unsigned int position) {
    std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::formattable> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_masd_dogen_generation_csharp_formattables_formattable(position + i)));
    }
    return r;
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

masd::dogen::generation::csharp::formattables::aspect_properties
create_masd_dogen_generation_csharp_formattables_aspect_properties(const unsigned int position) {
    return masd::dogen::generation::csharp::formattables::aspect_properties_generator::create(position);
}

std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::aspect_properties> create_std_unordered_map_std_string_masd_dogen_generation_csharp_formattables_aspect_properties(unsigned int position) {
    std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::aspect_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_masd_dogen_generation_csharp_formattables_aspect_properties(position + i)));
    }
    return r;
}

masd::dogen::generation::csharp::formattables::assistant_properties
create_masd_dogen_generation_csharp_formattables_assistant_properties(const unsigned int position) {
    return masd::dogen::generation::csharp::formattables::assistant_properties_generator::create(position);
}

std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::assistant_properties> create_std_unordered_map_std_string_masd_dogen_generation_csharp_formattables_assistant_properties(unsigned int position) {
    std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::assistant_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_masd_dogen_generation_csharp_formattables_assistant_properties(position + i)));
    }
    return r;
}

}

namespace masd::dogen::generation::csharp::formattables {

model_generator::model_generator() : position_(0) { }

void model_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_masd_dogen_coding_meta_model_name(position + 0));
    v.formattables(create_std_unordered_map_std_string_masd_dogen_generation_csharp_formattables_formattable(position + 1));
    v.project_items(create_std_list_std_string(position + 2));
    v.aspect_properties(create_std_unordered_map_std_string_masd_dogen_generation_csharp_formattables_aspect_properties(position + 3));
    v.assistant_properties(create_std_unordered_map_std_string_masd_dogen_generation_csharp_formattables_assistant_properties(position + 4));
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
