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
#include "dogen.archetypes/test_data/location_td.hpp"
#include "dogen.variability/test_data/meta_model/element_td.hpp"
#include "dogen.variability/test_data/meta_model/template_kind_td.hpp"
#include "dogen.variability/test_data/meta_model/configuration_point_template_td.hpp"

namespace {

dogen::archetypes::location
create_dogen_archetypes_location(const unsigned int position) {
    return dogen::archetypes::location_generator::create(position);
}

dogen::variability::meta_model::template_kind
create_dogen_variability_meta_model_template_kind(const unsigned int position) {
    return dogen::variability::meta_model::template_kind_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace dogen::variability::meta_model {

configuration_point_template_generator::configuration_point_template_generator() : position_(0) { }

void configuration_point_template_generator::
populate(const unsigned int position, result_type& v) {
    dogen::variability::meta_model::element_generator::populate(position, v);
    v.location(create_dogen_archetypes_location(position + 0));
    v.kind(create_dogen_variability_meta_model_template_kind(position + 1));
    v.untyped_value(create_std_list_std_string(position + 2));
}

configuration_point_template_generator::result_type
configuration_point_template_generator::create(const unsigned int position) {
    configuration_point_template r;
    configuration_point_template_generator::populate(position, r);
    return r;
}

configuration_point_template_generator::result_type*
configuration_point_template_generator::create_ptr(const unsigned int position) {
    configuration_point_template* p = new configuration_point_template();
    configuration_point_template_generator::populate(position, *p);
    return p;
}

configuration_point_template_generator::result_type
configuration_point_template_generator::operator()() {
    return create(position_++);
}

}
