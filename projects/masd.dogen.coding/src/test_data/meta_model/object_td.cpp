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
#include "masd.dogen.coding/test_data/meta_model/name_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/object_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/element_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/attribute_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/type_parameters_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/orm/object_properties_td.hpp"

namespace {

masd::dogen::coding::meta_model::attribute
create_masd_dogen_coding_meta_model_attribute(const unsigned int position) {
    return masd::dogen::coding::meta_model::attribute_generator::create(position);
}

std::list<masd::dogen::coding::meta_model::attribute> create_std_list_masd_dogen_coding_meta_model_attribute(unsigned int position) {
    std::list<masd::dogen::coding::meta_model::attribute> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_coding_meta_model_attribute(position + i));
    }
    return r;
}

masd::dogen::coding::meta_model::name
create_masd_dogen_coding_meta_model_name(const unsigned int position) {
    return masd::dogen::coding::meta_model::name_generator::create(position);
}

std::unordered_map<masd::dogen::coding::meta_model::name, std::list<masd::dogen::coding::meta_model::attribute> > create_std_unordered_map_masd_dogen_coding_meta_model_name_std_list_masd_dogen_coding_meta_model_attribute(unsigned int position) {
    std::unordered_map<masd::dogen::coding::meta_model::name, std::list<masd::dogen::coding::meta_model::attribute> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_masd_dogen_coding_meta_model_name(position + i), create_std_list_masd_dogen_coding_meta_model_attribute(position + i)));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

boost::optional<masd::dogen::coding::meta_model::name>
create_boost_optional_masd_dogen_coding_meta_model_name(unsigned int position) {
    boost::optional<masd::dogen::coding::meta_model::name> r(
        create_masd_dogen_coding_meta_model_name(position));
    return r;
}

std::list<masd::dogen::coding::meta_model::name> create_std_list_masd_dogen_coding_meta_model_name(unsigned int position) {
    std::list<masd::dogen::coding::meta_model::name> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_coding_meta_model_name(position + i));
    }
    return r;
}

masd::dogen::coding::meta_model::type_parameters
create_masd_dogen_coding_meta_model_type_parameters(const unsigned int position) {
    return masd::dogen::coding::meta_model::type_parameters_generator::create(position);
}

masd::dogen::coding::meta_model::orm::object_properties
create_masd_dogen_coding_meta_model_orm_object_properties(const unsigned int position) {
    return masd::dogen::coding::meta_model::orm::object_properties_generator::create(position);
}

boost::optional<masd::dogen::coding::meta_model::orm::object_properties>
create_boost_optional_masd_dogen_coding_meta_model_orm_object_properties(unsigned int position) {
    boost::optional<masd::dogen::coding::meta_model::orm::object_properties> r(
        create_masd_dogen_coding_meta_model_orm_object_properties(position));
    return r;
}

}

namespace masd::dogen::coding::meta_model {

object_generator::object_generator() : position_(0) { }

void object_generator::
populate(const unsigned int position, result_type& v) {
    masd::dogen::coding::meta_model::element_generator::populate(position, v);
    v.all_attributes(create_std_list_masd_dogen_coding_meta_model_attribute(position + 0));
    v.local_attributes(create_std_list_masd_dogen_coding_meta_model_attribute(position + 1));
    v.inherited_attributes(create_std_unordered_map_masd_dogen_coding_meta_model_name_std_list_masd_dogen_coding_meta_model_attribute(position + 2));
    v.is_immutable(create_bool(position + 3));
    v.is_fluent(create_bool(position + 4));
    v.base_visitor(create_boost_optional_masd_dogen_coding_meta_model_name(position + 5));
    v.derived_visitor(create_boost_optional_masd_dogen_coding_meta_model_name(position + 6));
    v.is_visitation_root(create_bool(position + 7));
    v.is_visitation_leaf(create_bool(position + 8));
    v.transparent_associations(create_std_list_masd_dogen_coding_meta_model_name(position + 9));
    v.opaque_associations(create_std_list_masd_dogen_coding_meta_model_name(position + 10));
    v.is_parent(create_bool(position + 11));
    v.is_child(create_bool(position + 12));
    v.is_leaf(create_bool(position + 13));
    v.is_final(create_bool(position + 14));
    v.is_abstract(create_bool(position + 15));
    v.in_inheritance_relationship(create_bool(position + 16));
    v.root_parents(create_std_list_masd_dogen_coding_meta_model_name(position + 17));
    v.parents(create_std_list_masd_dogen_coding_meta_model_name(position + 18));
    v.leaves(create_std_list_masd_dogen_coding_meta_model_name(position + 19));
    v.type_parameters(create_masd_dogen_coding_meta_model_type_parameters(position + 20));
    v.is_associative_container(create_bool(position + 21));
    v.object_templates(create_std_list_masd_dogen_coding_meta_model_name(position + 22));
    v.associative_container_keys(create_std_list_masd_dogen_coding_meta_model_name(position + 23));
    v.provides_opaqueness(create_bool(position + 24));
    v.can_be_primitive_underlier(create_bool(position + 25));
    v.orm_properties(create_boost_optional_masd_dogen_coding_meta_model_orm_object_properties(position + 26));
}

object_generator::result_type
object_generator::create(const unsigned int position) {
    object r;
    object_generator::populate(position, r);
    return r;
}

object_generator::result_type*
object_generator::create_ptr(const unsigned int position) {
    object* p = new object();
    object_generator::populate(position, *p);
    return p;
}

object_generator::result_type
object_generator::operator()() {
    return create(position_++);
}

}
