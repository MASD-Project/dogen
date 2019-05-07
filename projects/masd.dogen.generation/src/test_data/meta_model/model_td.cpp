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
#include "masd.dogen.coding/test_data/meta_model/name_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/module_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/element_td.hpp"
#include "masd.dogen.generation/test_data/meta_model/model_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/origin_types_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/technical_space_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/orm/model_properties_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/extraction_properties_td.hpp"
#include "masd.dogen.generation/test_data/meta_model/element_archetype_td.hpp"
#include "masd.dogen.generation/test_data/meta_model/locator_properties_td.hpp"
#include "masd.dogen.generation/test_data/meta_model/global_archetype_location_properties_td.hpp"

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

masd::dogen::coding::meta_model::element*
create_masd_dogen_coding_meta_model_element_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::element_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::element>
create_boost_shared_ptr_masd_dogen_coding_meta_model_element(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::element> r(
        create_masd_dogen_coding_meta_model_element_ptr(position));
    return r;
}

std::vector<boost::shared_ptr<masd::dogen::coding::meta_model::element> > create_std_vector_boost_shared_ptr_masd_dogen_coding_meta_model_element(unsigned int position) {
    std::vector<boost::shared_ptr<masd::dogen::coding::meta_model::element> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_shared_ptr_masd_dogen_coding_meta_model_element(position + i));
    }
    return r;
}

masd::dogen::coding::meta_model::module*
create_masd_dogen_coding_meta_model_module_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::module_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::module>
create_boost_shared_ptr_masd_dogen_coding_meta_model_module(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::module> r(
        create_masd_dogen_coding_meta_model_module_ptr(position));
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::unordered_set<std::string> create_std_unordered_set_std_string(unsigned int position) {
    std::unordered_set<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_std_string(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

masd::dogen::coding::meta_model::technical_space
create_masd_dogen_coding_meta_model_technical_space(const unsigned int position) {
    return masd::dogen::coding::meta_model::technical_space_generator::create(position);
}

std::unordered_set<masd::dogen::coding::meta_model::technical_space> create_std_unordered_set_masd_dogen_coding_meta_model_technical_space(unsigned int position) {
    std::unordered_set<masd::dogen::coding::meta_model::technical_space> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_masd_dogen_coding_meta_model_technical_space(position + i));
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

masd::dogen::generation::meta_model::element_archetype
create_masd_dogen_generation_meta_model_element_archetype(const unsigned int position) {
    return masd::dogen::generation::meta_model::element_archetype_generator::create(position);
}

std::unordered_set<masd::dogen::generation::meta_model::element_archetype> create_std_unordered_set_masd_dogen_generation_meta_model_element_archetype(unsigned int position) {
    std::unordered_set<masd::dogen::generation::meta_model::element_archetype> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_masd_dogen_generation_meta_model_element_archetype(position + i));
    }
    return r;
}

masd::dogen::generation::meta_model::locator_properties
create_masd_dogen_generation_meta_model_locator_properties(const unsigned int position) {
    return masd::dogen::generation::meta_model::locator_properties_generator::create(position);
}

masd::dogen::generation::meta_model::global_archetype_location_properties
create_masd_dogen_generation_meta_model_global_archetype_location_properties(const unsigned int position) {
    return masd::dogen::generation::meta_model::global_archetype_location_properties_generator::create(position);
}

masd::dogen::coding::meta_model::extraction_properties
create_masd_dogen_coding_meta_model_extraction_properties(const unsigned int position) {
    return masd::dogen::coding::meta_model::extraction_properties_generator::create(position);
}

}

namespace masd::dogen::generation::meta_model {

model_generator::model_generator() : position_(0) { }

void model_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_masd_dogen_coding_meta_model_name(position + 0));
    v.meta_name(create_masd_dogen_coding_meta_model_name(position + 1));
    v.references(create_std_unordered_map_masd_dogen_coding_meta_model_name_masd_dogen_coding_meta_model_origin_types(position + 2));
    v.leaves(create_std_unordered_set_masd_dogen_coding_meta_model_name(position + 3));
    v.elements(create_std_vector_boost_shared_ptr_masd_dogen_coding_meta_model_element(position + 4));
    v.root_module(create_boost_shared_ptr_masd_dogen_coding_meta_model_module(position + 5));
    v.module_ids(create_std_unordered_set_std_string(position + 6));
    v.has_generatable_types(create_bool(position + 7));
    v.input_technical_space(create_masd_dogen_coding_meta_model_technical_space(position + 8));
    v.output_technical_space(create_masd_dogen_coding_meta_model_technical_space(position + 9));
    v.all_technical_spaces(create_std_unordered_set_masd_dogen_coding_meta_model_technical_space(position + 10));
    v.orm_properties(create_boost_optional_masd_dogen_coding_meta_model_orm_model_properties(position + 11));
    v.enabled_archetype_for_element(create_std_unordered_set_masd_dogen_generation_meta_model_element_archetype(position + 12));
    v.locator_properties(create_masd_dogen_generation_meta_model_locator_properties(position + 13));
    v.global_archetype_location_properties(create_masd_dogen_generation_meta_model_global_archetype_location_properties(position + 14));
    v.extraction_properties(create_masd_dogen_coding_meta_model_extraction_properties(position + 15));
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
