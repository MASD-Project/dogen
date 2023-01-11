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
#include "dogen.logical/test_data/entities/model_td.hpp"
#include "dogen.identification/test_data/entities/logical_id_td.hpp"
#include "dogen.identification/test_data/entities/model_type_td.hpp"
#include "dogen.logical/test_data/entities/aspect_properties_td.hpp"
#include "dogen.logical/test_data/entities/structural/module_td.hpp"
#include "dogen.identification/test_data/entities/logical_name_td.hpp"
#include "dogen.logical/test_data/entities/assistant_properties_td.hpp"
#include "dogen.logical/test_data/entities/orm/model_properties_td.hpp"
#include "dogen.logical/test_data/entities/streaming_properties_td.hpp"
#include "dogen.identification/test_data/entities/logical_meta_id_td.hpp"
#include "dogen.identification/test_data/entities/technical_space_td.hpp"
#include "dogen.logical/test_data/entities/orm/element_repository_td.hpp"
#include "dogen.identification/test_data/entities/codec_provenance_td.hpp"
#include "dogen.identification/test_data/entities/logical_meta_name_td.hpp"
#include "dogen.logical/test_data/entities/build/element_repository_td.hpp"
#include "dogen.logical/test_data/entities/mapping/element_repository_td.hpp"
#include "dogen.logical/test_data/entities/physical/element_repository_td.hpp"
#include "dogen.logical/test_data/entities/decoration/element_repository_td.hpp"
#include "dogen.logical/test_data/entities/structural/element_repository_td.hpp"
#include "dogen.logical/test_data/entities/templating/element_repository_td.hpp"
#include "dogen.identification/test_data/entities/technical_space_version_td.hpp"
#include "dogen.logical/test_data/entities/variability/element_repository_td.hpp"
#include "dogen.logical/test_data/entities/serialization/element_repository_td.hpp"
#include "dogen.logical/test_data/entities/visual_studio/element_repository_td.hpp"

namespace {

dogen::identification::entities::logical_name
create_dogen_identification_entities_logical_name(const unsigned int position) {
    return dogen::identification::entities::logical_name_generator::create(position);
}

dogen::identification::entities::logical_meta_name
create_dogen_identification_entities_logical_meta_name(const unsigned int position) {
    return dogen::identification::entities::logical_meta_name_generator::create(position);
}

dogen::identification::entities::codec_provenance
create_dogen_identification_entities_codec_provenance(const unsigned int position) {
    return dogen::identification::entities::codec_provenance_generator::create(position);
}

dogen::identification::entities::model_type
create_dogen_identification_entities_model_type(const unsigned int position) {
    return dogen::identification::entities::model_type_generator::create(position);
}

std::unordered_map<dogen::identification::entities::logical_name, dogen::identification::entities::model_type> create_std_unordered_map_dogen_identification_entities_logical_name_dogen_identification_entities_model_type(unsigned int position) {
    std::unordered_map<dogen::identification::entities::logical_name, dogen::identification::entities::model_type> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_identification_entities_logical_name(position + i), create_dogen_identification_entities_model_type(position + i)));
    }
    return r;
}

std::unordered_set<dogen::identification::entities::logical_name> create_std_unordered_set_dogen_identification_entities_logical_name(unsigned int position) {
    std::unordered_set<dogen::identification::entities::logical_name> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_dogen_identification_entities_logical_name(position + i));
    }
    return r;
}

dogen::logical::entities::structural::module*
create_dogen_logical_entities_structural_module_ptr(const unsigned int position) {
    return dogen::logical::entities::structural::module_generator::create_ptr(position);
}

boost::shared_ptr<dogen::logical::entities::structural::module>
create_boost_shared_ptr_dogen_logical_entities_structural_module(unsigned int position) {
    boost::shared_ptr<dogen::logical::entities::structural::module> r(
        create_dogen_logical_entities_structural_module_ptr(position));
    return r;
}

dogen::identification::entities::technical_space
create_dogen_identification_entities_technical_space(const unsigned int position) {
    return dogen::identification::entities::technical_space_generator::create(position);
}

std::list<dogen::identification::entities::technical_space> create_std_list_dogen_identification_entities_technical_space(unsigned int position) {
    std::list<dogen::identification::entities::technical_space> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_identification_entities_technical_space(position + i));
    }
    return r;
}

std::unordered_set<dogen::identification::entities::technical_space> create_std_unordered_set_dogen_identification_entities_technical_space(unsigned int position) {
    std::unordered_set<dogen::identification::entities::technical_space> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_dogen_identification_entities_technical_space(position + i));
    }
    return r;
}

dogen::logical::entities::orm::model_properties
create_dogen_logical_entities_orm_model_properties(const unsigned int position) {
    return dogen::logical::entities::orm::model_properties_generator::create(position);
}

boost::optional<dogen::logical::entities::orm::model_properties>
create_boost_optional_dogen_logical_entities_orm_model_properties(unsigned int position) {
    boost::optional<dogen::logical::entities::orm::model_properties> r(
        create_dogen_logical_entities_orm_model_properties(position));
    return r;
}

dogen::logical::entities::structural::element_repository
create_dogen_logical_entities_structural_element_repository(const unsigned int position) {
    return dogen::logical::entities::structural::element_repository_generator::create(position);
}

dogen::logical::entities::decoration::element_repository
create_dogen_logical_entities_decoration_element_repository(const unsigned int position) {
    return dogen::logical::entities::decoration::element_repository_generator::create(position);
}

dogen::logical::entities::variability::element_repository
create_dogen_logical_entities_variability_element_repository(const unsigned int position) {
    return dogen::logical::entities::variability::element_repository_generator::create(position);
}

dogen::logical::entities::mapping::element_repository
create_dogen_logical_entities_mapping_element_repository(const unsigned int position) {
    return dogen::logical::entities::mapping::element_repository_generator::create(position);
}

dogen::logical::entities::templating::element_repository
create_dogen_logical_entities_templating_element_repository(const unsigned int position) {
    return dogen::logical::entities::templating::element_repository_generator::create(position);
}

dogen::logical::entities::serialization::element_repository
create_dogen_logical_entities_serialization_element_repository(const unsigned int position) {
    return dogen::logical::entities::serialization::element_repository_generator::create(position);
}

dogen::logical::entities::visual_studio::element_repository
create_dogen_logical_entities_visual_studio_element_repository(const unsigned int position) {
    return dogen::logical::entities::visual_studio::element_repository_generator::create(position);
}

dogen::logical::entities::orm::element_repository
create_dogen_logical_entities_orm_element_repository(const unsigned int position) {
    return dogen::logical::entities::orm::element_repository_generator::create(position);
}

dogen::logical::entities::build::element_repository
create_dogen_logical_entities_build_element_repository(const unsigned int position) {
    return dogen::logical::entities::build::element_repository_generator::create(position);
}

dogen::logical::entities::physical::element_repository
create_dogen_logical_entities_physical_element_repository(const unsigned int position) {
    return dogen::logical::entities::physical::element_repository_generator::create(position);
}

dogen::identification::entities::logical_meta_id
create_dogen_identification_entities_logical_meta_id(const unsigned int position) {
    return dogen::identification::entities::logical_meta_id_generator::create(position);
}

std::unordered_map<dogen::identification::entities::logical_meta_id, dogen::identification::entities::logical_meta_name> create_std_unordered_map_dogen_identification_entities_logical_meta_id_dogen_identification_entities_logical_meta_name(unsigned int position) {
    std::unordered_map<dogen::identification::entities::logical_meta_id, dogen::identification::entities::logical_meta_name> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_identification_entities_logical_meta_id(position + i), create_dogen_identification_entities_logical_meta_name(position + i)));
    }
    return r;
}

dogen::identification::entities::logical_id
create_dogen_identification_entities_logical_id(const unsigned int position) {
    return dogen::identification::entities::logical_id_generator::create(position);
}

dogen::logical::entities::streaming_properties
create_dogen_logical_entities_streaming_properties(const unsigned int position) {
    return dogen::logical::entities::streaming_properties_generator::create(position);
}

std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::streaming_properties> create_std_unordered_map_dogen_identification_entities_logical_id_dogen_logical_entities_streaming_properties(unsigned int position) {
    std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::streaming_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_identification_entities_logical_id(position + i), create_dogen_logical_entities_streaming_properties(position + i)));
    }
    return r;
}

dogen::identification::entities::technical_space_version
create_dogen_identification_entities_technical_space_version(const unsigned int position) {
    return dogen::identification::entities::technical_space_version_generator::create(position);
}

dogen::logical::entities::aspect_properties
create_dogen_logical_entities_aspect_properties(const unsigned int position) {
    return dogen::logical::entities::aspect_properties_generator::create(position);
}

std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::aspect_properties> create_std_unordered_map_dogen_identification_entities_logical_id_dogen_logical_entities_aspect_properties(unsigned int position) {
    std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::aspect_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_identification_entities_logical_id(position + i), create_dogen_logical_entities_aspect_properties(position + i)));
    }
    return r;
}

dogen::logical::entities::assistant_properties
create_dogen_logical_entities_assistant_properties(const unsigned int position) {
    return dogen::logical::entities::assistant_properties_generator::create(position);
}

std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::assistant_properties> create_std_unordered_map_dogen_identification_entities_logical_id_dogen_logical_entities_assistant_properties(unsigned int position) {
    std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::assistant_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_identification_entities_logical_id(position + i), create_dogen_logical_entities_assistant_properties(position + i)));
    }
    return r;
}

}

namespace dogen::logical::entities {

model_generator::model_generator() : position_(0) { }

void model_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_dogen_identification_entities_logical_name(position + 0));
    v.meta_name(create_dogen_identification_entities_logical_meta_name(position + 1));
    v.provenance(create_dogen_identification_entities_codec_provenance(position + 2));
    v.references(create_std_unordered_map_dogen_identification_entities_logical_name_dogen_identification_entities_model_type(position + 3));
    v.leaves(create_std_unordered_set_dogen_identification_entities_logical_name(position + 4));
    v.root_module(create_boost_shared_ptr_dogen_logical_entities_structural_module(position + 5));
    v.input_technical_space(create_dogen_identification_entities_technical_space(position + 6));
    v.output_technical_spaces(create_std_list_dogen_identification_entities_technical_space(position + 7));
    v.all_technical_spaces(create_std_unordered_set_dogen_identification_entities_technical_space(position + 8));
    v.orm_properties(create_boost_optional_dogen_logical_entities_orm_model_properties(position + 9));
    v.structural_elements(create_dogen_logical_entities_structural_element_repository(position + 10));
    v.decoration_elements(create_dogen_logical_entities_decoration_element_repository(position + 11));
    v.variability_elements(create_dogen_logical_entities_variability_element_repository(position + 12));
    v.mapping_elements(create_dogen_logical_entities_mapping_element_repository(position + 13));
    v.templating_elements(create_dogen_logical_entities_templating_element_repository(position + 14));
    v.serialization_elements(create_dogen_logical_entities_serialization_element_repository(position + 15));
    v.visual_studio_elements(create_dogen_logical_entities_visual_studio_element_repository(position + 16));
    v.orm_elements(create_dogen_logical_entities_orm_element_repository(position + 17));
    v.build_elements(create_dogen_logical_entities_build_element_repository(position + 18));
    v.physical_elements(create_dogen_logical_entities_physical_element_repository(position + 19));
    v.meta_names(create_std_unordered_map_dogen_identification_entities_logical_meta_id_dogen_identification_entities_logical_meta_name(position + 20));
    v.streaming_properties(create_std_unordered_map_dogen_identification_entities_logical_id_dogen_logical_entities_streaming_properties(position + 21));
    v.technical_space_version(create_dogen_identification_entities_technical_space_version(position + 22));
    v.aspect_properties(create_std_unordered_map_dogen_identification_entities_logical_id_dogen_logical_entities_aspect_properties(position + 23));
    v.assistant_properties(create_std_unordered_map_dogen_identification_entities_logical_id_dogen_logical_entities_assistant_properties(position + 24));
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