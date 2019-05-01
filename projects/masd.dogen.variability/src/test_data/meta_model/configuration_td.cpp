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
#include "masd.dogen.variability/test_data/meta_model/element_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/binding_point_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/configuration_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/potential_binding_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/configuration_point_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

masd::dogen::variability::meta_model::configuration_point
create_masd_dogen_variability_meta_model_configuration_point(const unsigned int position) {
    return masd::dogen::variability::meta_model::configuration_point_generator::create(position);
}

std::unordered_map<std::string, masd::dogen::variability::meta_model::configuration_point> create_std_unordered_map_std_string_masd_dogen_variability_meta_model_configuration_point(unsigned int position) {
    std::unordered_map<std::string, masd::dogen::variability::meta_model::configuration_point> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_masd_dogen_variability_meta_model_configuration_point(position + i)));
    }
    return r;
}

masd::dogen::variability::meta_model::potential_binding
create_masd_dogen_variability_meta_model_potential_binding(const unsigned int position) {
    return masd::dogen::variability::meta_model::potential_binding_generator::create(position);
}

std::list<masd::dogen::variability::meta_model::potential_binding> create_std_list_masd_dogen_variability_meta_model_potential_binding(unsigned int position) {
    std::list<masd::dogen::variability::meta_model::potential_binding> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_variability_meta_model_potential_binding(position + i));
    }
    return r;
}

masd::dogen::variability::meta_model::binding_point
create_masd_dogen_variability_meta_model_binding_point(const unsigned int position) {
    return masd::dogen::variability::meta_model::binding_point_generator::create(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

}

namespace masd::dogen::variability::meta_model {

configuration_generator::configuration_generator() : position_(0) { }

void configuration_generator::
populate(const unsigned int position, result_type& v) {
    masd::dogen::variability::meta_model::element_generator::populate(position, v);
    v.configuration_points(create_std_unordered_map_std_string_masd_dogen_variability_meta_model_configuration_point(position + 0));
    v.profile_bindings(create_std_list_masd_dogen_variability_meta_model_potential_binding(position + 1));
    v.configuration_bindings(create_std_list_masd_dogen_variability_meta_model_potential_binding(position + 2));
    v.source_binding_point(create_masd_dogen_variability_meta_model_binding_point(position + 3));
    v.from_target(create_bool(position + 4));
}

configuration_generator::result_type
configuration_generator::create(const unsigned int position) {
    configuration r;
    configuration_generator::populate(position, r);
    return r;
}

configuration_generator::result_type*
configuration_generator::create_ptr(const unsigned int position) {
    configuration* p = new configuration();
    configuration_generator::populate(position, *p);
    return p;
}

configuration_generator::result_type
configuration_generator::operator()() {
    return create(position_++);
}

}
