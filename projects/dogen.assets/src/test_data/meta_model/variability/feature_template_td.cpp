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
#include "dogen.assets/test_data/meta_model/name_td.hpp"
#include "dogen.assets/test_data/meta_model/name_tree_td.hpp"
#include "dogen.variability/test_data/meta_model/value_type_td.hpp"
#include "dogen.variability/test_data/meta_model/binding_point_td.hpp"
#include "dogen.variability/test_data/meta_model/configuration_td.hpp"
#include "dogen.assets/test_data/meta_model/variability/feature_template_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::variability::meta_model::configuration*
create_dogen_variability_meta_model_configuration_ptr(const unsigned int position) {
    return dogen::variability::meta_model::configuration_generator::create_ptr(position);
}

boost::shared_ptr<dogen::variability::meta_model::configuration>
create_boost_shared_ptr_dogen_variability_meta_model_configuration(unsigned int position) {
    boost::shared_ptr<dogen::variability::meta_model::configuration> r(
        create_dogen_variability_meta_model_configuration_ptr(position));
    return r;
}

dogen::assets::meta_model::name
create_dogen_assets_meta_model_name(const unsigned int position) {
    return dogen::assets::meta_model::name_generator::create(position);
}

dogen::assets::meta_model::name_tree
create_dogen_assets_meta_model_name_tree(const unsigned int position) {
    return dogen::assets::meta_model::name_tree_generator::create(position);
}

dogen::variability::meta_model::value_type
create_dogen_variability_meta_model_value_type(const unsigned int position) {
    return dogen::variability::meta_model::value_type_generator::create(position);
}

dogen::variability::meta_model::binding_point
create_dogen_variability_meta_model_binding_point(const unsigned int position) {
    return dogen::variability::meta_model::binding_point_generator::create(position);
}

boost::optional<dogen::variability::meta_model::binding_point>
create_boost_optional_dogen_variability_meta_model_binding_point(unsigned int position) {
    boost::optional<dogen::variability::meta_model::binding_point> r(
        create_dogen_variability_meta_model_binding_point(position));
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

}

namespace dogen::assets::meta_model::variability {

feature_template_generator::feature_template_generator() : position_(0) { }

void feature_template_generator::
populate(const unsigned int position, result_type& v) {
    v.documentation(create_std_string(position + 0));
    v.configuration(create_boost_shared_ptr_dogen_variability_meta_model_configuration(position + 1));
    v.name(create_dogen_assets_meta_model_name(position + 2));
    v.key(create_std_string(position + 3));
    v.identifiable_key(create_std_string(position + 4));
    v.unparsed_type(create_std_string(position + 5));
    v.mapped_type(create_std_string(position + 6));
    v.parsed_type(create_dogen_assets_meta_model_name_tree(position + 7));
    v.value(create_std_string(position + 8));
    v.value_type(create_dogen_variability_meta_model_value_type(position + 9));
    v.binding_point(create_boost_optional_dogen_variability_meta_model_binding_point(position + 10));
    v.is_optional(create_bool(position + 11));
    v.requires_optionality(create_bool(position + 12));
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
