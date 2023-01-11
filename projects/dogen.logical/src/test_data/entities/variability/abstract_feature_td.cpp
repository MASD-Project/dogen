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
#include "dogen.variability/test_data/entities/value_type_td.hpp"
#include "dogen.variability/test_data/entities/binding_point_td.hpp"
#include "dogen.variability/test_data/entities/configuration_td.hpp"
#include "dogen.identification/test_data/entities/logical_name_td.hpp"
#include "dogen.logical/test_data/entities/variability/feature_td.hpp"
#include "dogen.identification/test_data/entities/logical_name_tree_td.hpp"
#include "dogen.logical/test_data/entities/variability/abstract_feature_td.hpp"
#include "dogen.logical/test_data/entities/variability/feature_template_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::variability::entities::configuration*
create_dogen_variability_entities_configuration_ptr(const unsigned int position) {
    return dogen::variability::entities::configuration_generator::create_ptr(position);
}

boost::shared_ptr<dogen::variability::entities::configuration>
create_boost_shared_ptr_dogen_variability_entities_configuration(unsigned int position) {
    boost::shared_ptr<dogen::variability::entities::configuration> r(
        create_dogen_variability_entities_configuration_ptr(position));
    return r;
}

dogen::identification::entities::logical_name
create_dogen_identification_entities_logical_name(const unsigned int position) {
    return dogen::identification::entities::logical_name_generator::create(position);
}

dogen::identification::entities::logical_name_tree
create_dogen_identification_entities_logical_name_tree(const unsigned int position) {
    return dogen::identification::entities::logical_name_tree_generator::create(position);
}

dogen::variability::entities::value_type
create_dogen_variability_entities_value_type(const unsigned int position) {
    return dogen::variability::entities::value_type_generator::create(position);
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

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

}

namespace dogen::logical::entities::variability {

void abstract_feature_generator::
populate(const unsigned int position, result_type& v) {
    v.documentation(create_std_string(position + 0));
    v.configuration(create_boost_shared_ptr_dogen_variability_entities_configuration(position + 1));
    v.name(create_dogen_identification_entities_logical_name(position + 2));
    v.original_key(create_std_string(position + 3));
    v.key(create_std_string(position + 4));
    v.identifiable_key(create_std_string(position + 5));
    v.unparsed_type(create_std_string(position + 6));
    v.mapped_type(create_std_string(position + 7));
    v.parsed_type(create_dogen_identification_entities_logical_name_tree(position + 8));
    v.default_value(create_std_string(position + 9));
    v.value_type(create_dogen_variability_entities_value_type(position + 10));
    v.binding_point(create_boost_optional_dogen_variability_entities_binding_point(position + 11));
    v.is_optional(create_bool(position + 12));
    v.requires_optionality(create_bool(position + 13));
}

abstract_feature_generator::result_type*
abstract_feature_generator::create_ptr(const unsigned int position) {
    if ((position % 1) == 0)
        return dogen::logical::entities::variability::feature_template_generator::create_ptr(position);
    return dogen::logical::entities::variability::feature_generator::create_ptr(position);
}

}
