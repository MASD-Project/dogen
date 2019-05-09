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
#include "masd.dogen.coding/test_data/meta_model/model_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/origin_types_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/technical_space_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/structural/module_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/orm/model_properties_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/extraction_properties_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/decoration/element_repository_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/structural/element_repository_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/variability/element_repository_td.hpp"

namespace {

masd::dogen::coding::meta_model::name
create_masd_dogen_coding_meta_model_name(const unsigned int position) {
    return masd::dogen::coding::meta_model::name_generator::create(position);
}

masd::dogen::coding::meta_model::origin_types
create_masd_dogen_coding_meta_model_origin_types(const unsigned int position) {
    return masd::dogen::coding::meta_model::origin_types_generator::create(position);
}

std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types> create_std_unordered_map_masd_dogen_coding_meta_model_name_masd_dogen_coding_meta_model_origin_types(unsigned int position) {
    std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_masd_dogen_coding_meta_model_name(position + i), create_masd_dogen_coding_meta_model_origin_types(position + i)));
    }
    return r;
}

std::unordered_set<masd::dogen::coding::meta_model::name> create_std_unordered_set_masd_dogen_coding_meta_model_name(unsigned int position) {
    std::unordered_set<masd::dogen::coding::meta_model::name> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_masd_dogen_coding_meta_model_name(position + i));
    }
    return r;
}

masd::dogen::coding::meta_model::structural::module*
create_masd_dogen_coding_meta_model_structural_module_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::structural::module_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::structural::module>
create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_module(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::module> r(
        create_masd_dogen_coding_meta_model_structural_module_ptr(position));
    return r;
}

masd::dogen::coding::meta_model::technical_space
create_masd_dogen_coding_meta_model_technical_space(const unsigned int position) {
    return masd::dogen::coding::meta_model::technical_space_generator::create(position);
}

std::list<masd::dogen::coding::meta_model::technical_space> create_std_list_masd_dogen_coding_meta_model_technical_space(unsigned int position) {
    std::list<masd::dogen::coding::meta_model::technical_space> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_coding_meta_model_technical_space(position + i));
    }
    return r;
}

masd::dogen::coding::meta_model::orm::model_properties
create_masd_dogen_coding_meta_model_orm_model_properties(const unsigned int position) {
    return masd::dogen::coding::meta_model::orm::model_properties_generator::create(position);
}

boost::optional<masd::dogen::coding::meta_model::orm::model_properties>
create_boost_optional_masd_dogen_coding_meta_model_orm_model_properties(unsigned int position) {
    boost::optional<masd::dogen::coding::meta_model::orm::model_properties> r(
        create_masd_dogen_coding_meta_model_orm_model_properties(position));
    return r;
}

masd::dogen::coding::meta_model::extraction_properties
create_masd_dogen_coding_meta_model_extraction_properties(const unsigned int position) {
    return masd::dogen::coding::meta_model::extraction_properties_generator::create(position);
}

masd::dogen::coding::meta_model::structural::element_repository
create_masd_dogen_coding_meta_model_structural_element_repository(const unsigned int position) {
    return masd::dogen::coding::meta_model::structural::element_repository_generator::create(position);
}

masd::dogen::coding::meta_model::decoration::element_repository
create_masd_dogen_coding_meta_model_decoration_element_repository(const unsigned int position) {
    return masd::dogen::coding::meta_model::decoration::element_repository_generator::create(position);
}

masd::dogen::coding::meta_model::variability::element_repository
create_masd_dogen_coding_meta_model_variability_element_repository(const unsigned int position) {
    return masd::dogen::coding::meta_model::variability::element_repository_generator::create(position);
}

}

namespace masd::dogen::coding::meta_model {

model_generator::model_generator() : position_(0) { }

void model_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_masd_dogen_coding_meta_model_name(position + 0));
    v.meta_name(create_masd_dogen_coding_meta_model_name(position + 1));
    v.origin_type(create_masd_dogen_coding_meta_model_origin_types(position + 2));
    v.references(create_std_unordered_map_masd_dogen_coding_meta_model_name_masd_dogen_coding_meta_model_origin_types(position + 3));
    v.leaves(create_std_unordered_set_masd_dogen_coding_meta_model_name(position + 4));
    v.root_module(create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_module(position + 5));
    v.input_technical_space(create_masd_dogen_coding_meta_model_technical_space(position + 6));
    v.output_technical_spaces(create_std_list_masd_dogen_coding_meta_model_technical_space(position + 7));
    v.orm_properties(create_boost_optional_masd_dogen_coding_meta_model_orm_model_properties(position + 8));
    v.extraction_properties(create_masd_dogen_coding_meta_model_extraction_properties(position + 9));
    v.structural_elements(create_masd_dogen_coding_meta_model_structural_element_repository(position + 10));
    v.decoration_elements(create_masd_dogen_coding_meta_model_decoration_element_repository(position + 11));
    v.variability_elements(create_masd_dogen_coding_meta_model_variability_element_repository(position + 12));
}

model_generator::result_type
model_generator::create(const unsigned int position) {
    model r;
    model_generator::populate(position, r);
    return r;
}

model_generator::result_type*
model_generator::create_ptr(const unsigned int position) {
    model* p = new model();
    model_generator::populate(position, *p);
    return p;
}

model_generator::result_type
model_generator::operator()() {
    return create(position_++);
}

}
