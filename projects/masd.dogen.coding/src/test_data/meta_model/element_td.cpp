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
#include "masd.dogen.annotations/test_data/annotation_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/name_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/module_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/object_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/builtin_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/element_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/visitor_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/exception_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/primitive_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/enumeration_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/origin_types_td.hpp"
#include "masd.dogen.extraction/test_data/decoration_properties_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/object_template_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/static_stereotypes_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/artefact_properties_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/local_archetype_location_properties_td.hpp"

namespace {

masd::dogen::coding::meta_model::name
create_masd_dogen_coding_meta_model_name(const unsigned int position) {
    return masd::dogen::coding::meta_model::name_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

masd::dogen::annotations::annotation
create_masd_dogen_annotations_annotation(const unsigned int position) {
    return masd::dogen::annotations::annotation_generator::create(position);
}

masd::dogen::coding::meta_model::origin_types
create_masd_dogen_coding_meta_model_origin_types(const unsigned int position) {
    return masd::dogen::coding::meta_model::origin_types_generator::create(position);
}

boost::optional<masd::dogen::coding::meta_model::name>
create_boost_optional_masd_dogen_coding_meta_model_name(unsigned int position) {
    boost::optional<masd::dogen::coding::meta_model::name> r(
        create_masd_dogen_coding_meta_model_name(position));
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

masd::dogen::coding::meta_model::static_stereotypes
create_masd_dogen_coding_meta_model_static_stereotypes(const unsigned int position) {
    return masd::dogen::coding::meta_model::static_stereotypes_generator::create(position);
}

std::list<masd::dogen::coding::meta_model::static_stereotypes> create_std_list_masd_dogen_coding_meta_model_static_stereotypes(unsigned int position) {
    std::list<masd::dogen::coding::meta_model::static_stereotypes> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_coding_meta_model_static_stereotypes(position + i));
    }
    return r;
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

masd::dogen::extraction::decoration_properties
create_masd_dogen_extraction_decoration_properties(const unsigned int position) {
    return masd::dogen::extraction::decoration_properties_generator::create(position);
}

masd::dogen::coding::meta_model::artefact_properties
create_masd_dogen_coding_meta_model_artefact_properties(const unsigned int position) {
    return masd::dogen::coding::meta_model::artefact_properties_generator::create(position);
}

std::unordered_map<std::string, masd::dogen::coding::meta_model::artefact_properties> create_std_unordered_map_std_string_masd_dogen_coding_meta_model_artefact_properties(unsigned int position) {
    std::unordered_map<std::string, masd::dogen::coding::meta_model::artefact_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_masd_dogen_coding_meta_model_artefact_properties(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::local_archetype_location_properties
create_masd_dogen_coding_meta_model_local_archetype_location_properties(const unsigned int position) {
    return masd::dogen::coding::meta_model::local_archetype_location_properties_generator::create(position);
}

std::unordered_map<std::string, masd::dogen::coding::meta_model::local_archetype_location_properties> create_std_unordered_map_std_string_masd_dogen_coding_meta_model_local_archetype_location_properties(unsigned int position) {
    std::unordered_map<std::string, masd::dogen::coding::meta_model::local_archetype_location_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_masd_dogen_coding_meta_model_local_archetype_location_properties(position + i)));
    }
    return r;
}

}

namespace masd::dogen::coding::meta_model {

void element_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_masd_dogen_coding_meta_model_name(position + 0));
    v.documentation(create_std_string(position + 1));
    v.annotation(create_masd_dogen_annotations_annotation(position + 2));
    v.origin_type(create_masd_dogen_coding_meta_model_origin_types(position + 3));
    v.contained_by(create_boost_optional_masd_dogen_coding_meta_model_name(position + 4));
    v.in_global_module(create_bool(position + 5));
    v.static_stereotypes(create_std_list_masd_dogen_coding_meta_model_static_stereotypes(position + 6));
    v.dynamic_stereotypes(create_std_list_std_string(position + 7));
    v.meta_name(create_masd_dogen_coding_meta_model_name(position + 8));
    v.is_element_extension(create_bool(position + 9));
    v.decoration_properties(create_masd_dogen_extraction_decoration_properties(position + 10));
    v.artefact_properties(create_std_unordered_map_std_string_masd_dogen_coding_meta_model_artefact_properties(position + 11));
    v.archetype_location_properties(create_std_unordered_map_std_string_masd_dogen_coding_meta_model_local_archetype_location_properties(position + 12));
}

element_generator::result_type*
element_generator::create_ptr(const unsigned int position) {
    if ((position % 7) == 0)
        return masd::dogen::coding::meta_model::enumeration_generator::create_ptr(position);
    if ((position % 7) == 1)
        return masd::dogen::coding::meta_model::exception_generator::create_ptr(position);
    if ((position % 7) == 2)
        return masd::dogen::coding::meta_model::module_generator::create_ptr(position);
    if ((position % 7) == 3)
        return masd::dogen::coding::meta_model::object_generator::create_ptr(position);
    if ((position % 7) == 4)
        return masd::dogen::coding::meta_model::object_template_generator::create_ptr(position);
    if ((position % 7) == 5)
        return masd::dogen::coding::meta_model::primitive_generator::create_ptr(position);
    if ((position % 7) == 6)
        return masd::dogen::coding::meta_model::visitor_generator::create_ptr(position);
    return masd::dogen::coding::meta_model::builtin_generator::create_ptr(position);
}

}
