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
#include "dogen.modeling/test_data/meta_model/facet_properties_td.hpp"
#include "dogen.modeling/test_data/meta_model/backend_properties_td.hpp"
#include "dogen.modeling/test_data/meta_model/archetype_properties_td.hpp"
#include "dogen.modeling/test_data/meta_model/denormalised_archetype_properties_td.hpp"
#include "dogen.modeling/test_data/meta_model/global_archetype_location_properties_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::modeling::meta_model::backend_properties
create_dogen_modeling_meta_model_backend_properties(const unsigned int position) {
    return dogen::modeling::meta_model::backend_properties_generator::create(position);
}

std::unordered_map<std::string, dogen::modeling::meta_model::backend_properties> create_std_unordered_map_std_string_dogen_modeling_meta_model_backend_properties(unsigned int position) {
    std::unordered_map<std::string, dogen::modeling::meta_model::backend_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_modeling_meta_model_backend_properties(position + i)));
    }
    return r;
}

dogen::modeling::meta_model::facet_properties
create_dogen_modeling_meta_model_facet_properties(const unsigned int position) {
    return dogen::modeling::meta_model::facet_properties_generator::create(position);
}

std::unordered_map<std::string, dogen::modeling::meta_model::facet_properties> create_std_unordered_map_std_string_dogen_modeling_meta_model_facet_properties(unsigned int position) {
    std::unordered_map<std::string, dogen::modeling::meta_model::facet_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_modeling_meta_model_facet_properties(position + i)));
    }
    return r;
}

dogen::modeling::meta_model::archetype_properties
create_dogen_modeling_meta_model_archetype_properties(const unsigned int position) {
    return dogen::modeling::meta_model::archetype_properties_generator::create(position);
}

std::unordered_map<std::string, dogen::modeling::meta_model::archetype_properties> create_std_unordered_map_std_string_dogen_modeling_meta_model_archetype_properties(unsigned int position) {
    std::unordered_map<std::string, dogen::modeling::meta_model::archetype_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_modeling_meta_model_archetype_properties(position + i)));
    }
    return r;
}

dogen::modeling::meta_model::denormalised_archetype_properties
create_dogen_modeling_meta_model_denormalised_archetype_properties(const unsigned int position) {
    return dogen::modeling::meta_model::denormalised_archetype_properties_generator::create(position);
}

std::unordered_map<std::string, dogen::modeling::meta_model::denormalised_archetype_properties> create_std_unordered_map_std_string_dogen_modeling_meta_model_denormalised_archetype_properties(unsigned int position) {
    std::unordered_map<std::string, dogen::modeling::meta_model::denormalised_archetype_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_modeling_meta_model_denormalised_archetype_properties(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace modeling {
namespace meta_model {

global_archetype_location_properties_generator::global_archetype_location_properties_generator() : position_(0) { }

void global_archetype_location_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.backend_properties(create_std_unordered_map_std_string_dogen_modeling_meta_model_backend_properties(position + 0));
    v.facet_properties(create_std_unordered_map_std_string_dogen_modeling_meta_model_facet_properties(position + 1));
    v.archetype_properties(create_std_unordered_map_std_string_dogen_modeling_meta_model_archetype_properties(position + 2));
    v.denormalised_archetype_properties(create_std_unordered_map_std_string_dogen_modeling_meta_model_denormalised_archetype_properties(position + 3));
}

global_archetype_location_properties_generator::result_type
global_archetype_location_properties_generator::create(const unsigned int position) {
    global_archetype_location_properties r;
    global_archetype_location_properties_generator::populate(position, r);
    return r;
}

global_archetype_location_properties_generator::result_type*
global_archetype_location_properties_generator::create_ptr(const unsigned int position) {
    global_archetype_location_properties* p = new global_archetype_location_properties();
    global_archetype_location_properties_generator::populate(position, *p);
    return p;
}

global_archetype_location_properties_generator::result_type
global_archetype_location_properties_generator::operator()() {
    return create(position_++);
}

} } }
