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
#include "dogen.archetypes/test_data/location_td.hpp"
#include "dogen.variability/test_data/meta_model/value_td.hpp"
#include "dogen.variability/test_data/meta_model/element_td.hpp"
#include "dogen.variability/test_data/meta_model/value_type_td.hpp"
#include "dogen.variability/test_data/meta_model/binding_point_td.hpp"
#include "dogen.variability/test_data/meta_model/template_kind_td.hpp"
#include "dogen.variability/test_data/meta_model/binding_action_td.hpp"
#include "dogen.variability/test_data/meta_model/feature_template_td.hpp"

namespace {

dogen::archetypes::location
create_dogen_archetypes_location(const unsigned int position) {
    return dogen::archetypes::location_generator::create(position);
}

dogen::variability::meta_model::value*
create_dogen_variability_meta_model_value_ptr(const unsigned int position) {
    return dogen::variability::meta_model::value_generator::create_ptr(position);
}

boost::shared_ptr<dogen::variability::meta_model::value>
create_boost_shared_ptr_dogen_variability_meta_model_value(unsigned int position) {
    boost::shared_ptr<dogen::variability::meta_model::value> r(
        create_dogen_variability_meta_model_value_ptr(position));
    return r;
}

dogen::variability::meta_model::value_type
create_dogen_variability_meta_model_value_type(const unsigned int position) {
    return dogen::variability::meta_model::value_type_generator::create(position);
}

dogen::variability::meta_model::binding_point
create_dogen_variability_meta_model_binding_point(const unsigned int position) {
    return dogen::variability::meta_model::binding_point_generator::create(position);
}

dogen::variability::meta_model::binding_action
create_dogen_variability_meta_model_binding_action(const unsigned int position) {
    return dogen::variability::meta_model::binding_action_generator::create(position);
}

dogen::variability::meta_model::template_kind
create_dogen_variability_meta_model_template_kind(const unsigned int position) {
    return dogen::variability::meta_model::template_kind_generator::create(position);
}

}

namespace dogen::variability::meta_model {

feature_template_generator::feature_template_generator() : position_(0) { }

void feature_template_generator::
populate(const unsigned int position, result_type& v) {
    dogen::variability::meta_model::element_generator::populate(position, v);
    v.location(create_dogen_archetypes_location(position + 0));
    v.default_value(create_boost_shared_ptr_dogen_variability_meta_model_value(position + 1));
    v.value_type(create_dogen_variability_meta_model_value_type(position + 2));
    v.binding_point(create_dogen_variability_meta_model_binding_point(position + 3));
    v.profile_binding_action(create_dogen_variability_meta_model_binding_action(position + 4));
    v.configuration_binding_action(create_dogen_variability_meta_model_binding_action(position + 5));
    v.kind(create_dogen_variability_meta_model_template_kind(position + 6));
}

feature_template_generator::result_type
feature_template_generator::create(const unsigned int position) {
    feature_template r;
    feature_template_generator::populate(position, r);
    return r;
}

feature_template_generator::result_type*
feature_template_generator::create_ptr(const unsigned int position) {
    feature_template* p = new feature_template();
    feature_template_generator::populate(position, *p);
    return p;
}

feature_template_generator::result_type
feature_template_generator::operator()() {
    return create(position_++);
}

}
