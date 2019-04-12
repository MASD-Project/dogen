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
#include "masd.dogen.variability/test_data/name_td.hpp"
#include "masd.dogen.variability/test_data/value_td.hpp"
#include "masd.dogen.variability/test_data/scope_types_td.hpp"
#include "masd.dogen.variability/test_data/value_types_td.hpp"
#include "masd.dogen.variability/test_data/type_template_td.hpp"
#include "masd.dogen.variability/test_data/template_kinds_td.hpp"
#include "masd.dogen.variability/test_data/archetype_location_td.hpp"

namespace {

masd::dogen::variability::name
create_masd_dogen_variability_name(const unsigned int position) {
    return masd::dogen::variability::name_generator::create(position);
}

masd::dogen::variability::value_types
create_masd_dogen_variability_value_types(const unsigned int position) {
    return masd::dogen::variability::value_types_generator::create(position);
}

masd::dogen::variability::scope_types
create_masd_dogen_variability_scope_types(const unsigned int position) {
    return masd::dogen::variability::scope_types_generator::create(position);
}

masd::dogen::variability::archetype_location
create_masd_dogen_variability_archetype_location(const unsigned int position) {
    return masd::dogen::variability::archetype_location_generator::create(position);
}

masd::dogen::variability::value*
create_masd_dogen_variability_value_ptr(const unsigned int position) {
    return masd::dogen::variability::value_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::variability::value>
create_boost_shared_ptr_masd_dogen_variability_value(unsigned int position) {
    boost::shared_ptr<masd::dogen::variability::value> r(
        create_masd_dogen_variability_value_ptr(position));
    return r;
}

masd::dogen::variability::template_kinds
create_masd_dogen_variability_template_kinds(const unsigned int position) {
    return masd::dogen::variability::template_kinds_generator::create(position);
}

}

namespace masd::dogen::variability {

type_template_generator::type_template_generator() : position_(0) { }

void type_template_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_masd_dogen_variability_name(position + 0));
    v.value_type(create_masd_dogen_variability_value_types(position + 1));
    v.scope(create_masd_dogen_variability_scope_types(position + 2));
    v.archetype_location(create_masd_dogen_variability_archetype_location(position + 3));
    v.default_value(create_boost_shared_ptr_masd_dogen_variability_value(position + 4));
    v.kind(create_masd_dogen_variability_template_kinds(position + 5));
}

type_template_generator::result_type
type_template_generator::create(const unsigned int position) {
    type_template r;
    type_template_generator::populate(position, r);
    return r;
}

type_template_generator::result_type*
type_template_generator::create_ptr(const unsigned int position) {
    type_template* p = new type_template();
    type_template_generator::populate(position, *p);
    return p;
}

type_template_generator::result_type
type_template_generator::operator()() {
    return create(position_++);
}

}
