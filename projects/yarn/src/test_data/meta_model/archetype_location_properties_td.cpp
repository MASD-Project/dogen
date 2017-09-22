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
#include "dogen/yarn/test_data/meta_model/facet_properties_td.hpp"
#include "dogen/yarn/test_data/meta_model/kernel_properties_td.hpp"
#include "dogen/yarn/test_data/meta_model/archetype_properties_td.hpp"
#include "dogen/yarn/test_data/meta_model/archetype_location_properties_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::yarn::meta_model::facet_properties
create_dogen_yarn_meta_model_facet_properties(const unsigned int position) {
    return dogen::yarn::meta_model::facet_properties_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties> create_std_unordered_map_std_string_dogen_yarn_meta_model_facet_properties(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_meta_model_facet_properties(position + i)));
    }
    return r;
}

dogen::yarn::meta_model::archetype_properties
create_dogen_yarn_meta_model_archetype_properties(const unsigned int position) {
    return dogen::yarn::meta_model::archetype_properties_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::meta_model::archetype_properties> create_std_unordered_map_std_string_dogen_yarn_meta_model_archetype_properties(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::meta_model::archetype_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_meta_model_archetype_properties(position + i)));
    }
    return r;
}

dogen::yarn::meta_model::kernel_properties
create_dogen_yarn_meta_model_kernel_properties(const unsigned int position) {
    return dogen::yarn::meta_model::kernel_properties_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::meta_model::kernel_properties> create_std_unordered_map_std_string_dogen_yarn_meta_model_kernel_properties(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::meta_model::kernel_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_meta_model_kernel_properties(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace yarn {
namespace meta_model {

archetype_location_properties_generator::archetype_location_properties_generator() : position_(0) { }

void archetype_location_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.facet_properties(create_std_unordered_map_std_string_dogen_yarn_meta_model_facet_properties(position + 0));
    v.archetype_properties(create_std_unordered_map_std_string_dogen_yarn_meta_model_archetype_properties(position + 1));
    v.kernel_properties(create_std_unordered_map_std_string_dogen_yarn_meta_model_kernel_properties(position + 2));
}

archetype_location_properties_generator::result_type
archetype_location_properties_generator::create(const unsigned int position) {
    archetype_location_properties r;
    archetype_location_properties_generator::populate(position, r);
    return r;
}

archetype_location_properties_generator::result_type*
archetype_location_properties_generator::create_ptr(const unsigned int position) {
    archetype_location_properties* p = new archetype_location_properties();
    archetype_location_properties_generator::populate(position, *p);
    return p;
}

archetype_location_properties_generator::result_type
archetype_location_properties_generator::operator()() {
    return create(position_++);
}

} } }
