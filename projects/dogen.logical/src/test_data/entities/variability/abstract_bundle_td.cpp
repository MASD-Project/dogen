/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#include "dogen.logical/test_data/entities/element_td.hpp"
#include "dogen.variability/test_data/entities/binding_point_td.hpp"
#include "dogen.identification/test_data/entities/logical_name_td.hpp"
#include "dogen.logical/test_data/entities/variability/feature_bundle_td.hpp"
#include "dogen.logical/test_data/entities/variability/abstract_bundle_td.hpp"
#include "dogen.logical/test_data/entities/variability/feature_template_bundle_td.hpp"

namespace {

dogen::identification::entities::logical_name
create_dogen_identification_entities_logical_name(const unsigned int position) {
    return dogen::identification::entities::logical_name_generator::create(position);
}

std::list<dogen::identification::entities::logical_name> create_std_list_dogen_identification_entities_logical_name(unsigned int position) {
    std::list<dogen::identification::entities::logical_name> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_identification_entities_logical_name(position + i));
    }
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

dogen::variability::entities::binding_point
create_dogen_variability_entities_binding_point(const unsigned int position) {
    return dogen::variability::entities::binding_point_generator::create(position);
}

boost::optional<dogen::variability::entities::binding_point>
create_boost_optional_dogen_variability_entities_binding_point(unsigned int position) {
    boost::optional<dogen::variability::entities::binding_point> r(
        create_dogen_variability_entities_binding_point(position));
    return r;
}

}

namespace dogen::logical::entities::variability {

void abstract_bundle_generator::
populate(const unsigned int position, result_type& v) {
    dogen::logical::entities::element_generator::populate(position, v);
    v.transparent_associations(create_std_list_dogen_identification_entities_logical_name(position + 0));
    v.opaque_associations(create_std_list_dogen_identification_entities_logical_name(position + 1));
    v.associative_container_keys(create_std_list_dogen_identification_entities_logical_name(position + 2));
    v.key_prefix(create_std_string(position + 3));
    v.generate_registration(create_bool(position + 4));
    v.generate_static_configuration(create_bool(position + 5));
    v.requires_manual_default_constructor(create_bool(position + 6));
    v.default_binding_point(create_boost_optional_dogen_variability_entities_binding_point(position + 7));
}

abstract_bundle_generator::result_type*
abstract_bundle_generator::create_ptr(const unsigned int position) {
    if ((position % 1) == 0)
        return dogen::logical::entities::variability::feature_template_bundle_generator::create_ptr(position);
    return dogen::logical::entities::variability::feature_bundle_generator::create_ptr(position);
}

}
