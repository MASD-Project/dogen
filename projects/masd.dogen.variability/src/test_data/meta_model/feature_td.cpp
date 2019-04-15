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
#include "masd.dogen.archetypes/test_data/location_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/value_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/element_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/feature_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/value_type_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/binding_type_td.hpp"

namespace {

masd::dogen::archetypes::location
create_masd_dogen_archetypes_location(const unsigned int position) {
    return masd::dogen::archetypes::location_generator::create(position);
}

masd::dogen::variability::meta_model::value*
create_masd_dogen_variability_meta_model_value_ptr(const unsigned int position) {
    return masd::dogen::variability::meta_model::value_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::variability::meta_model::value>
create_boost_shared_ptr_masd_dogen_variability_meta_model_value(unsigned int position) {
    boost::shared_ptr<masd::dogen::variability::meta_model::value> r(
        create_masd_dogen_variability_meta_model_value_ptr(position));
    return r;
}

masd::dogen::variability::meta_model::value_type
create_masd_dogen_variability_meta_model_value_type(const unsigned int position) {
    return masd::dogen::variability::meta_model::value_type_generator::create(position);
}

masd::dogen::variability::meta_model::binding_type
create_masd_dogen_variability_meta_model_binding_type(const unsigned int position) {
    return masd::dogen::variability::meta_model::binding_type_generator::create(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

}

namespace masd::dogen::variability::meta_model {

feature_generator::feature_generator() : position_(0) { }

void feature_generator::
populate(const unsigned int position, result_type& v) {
    masd::dogen::variability::meta_model::element_generator::populate(position, v);
    v.location(create_masd_dogen_archetypes_location(position + 0));
    v.default_value(create_boost_shared_ptr_masd_dogen_variability_meta_model_value(position + 1));
    v.value_type(create_masd_dogen_variability_meta_model_value_type(position + 2));
    v.binding_type(create_masd_dogen_variability_meta_model_binding_type(position + 3));
    v.is_partially_matchable(create_bool(position + 4));
}

feature_generator::result_type
feature_generator::create(const unsigned int position) {
    feature r;
    feature_generator::populate(position, r);
    return r;
}

feature_generator::result_type*
feature_generator::create_ptr(const unsigned int position) {
    feature* p = new feature();
    feature_generator::populate(position, *p);
    return p;
}

feature_generator::result_type
feature_generator::operator()() {
    return create(position_++);
}

}
