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
#include "masd.dogen.coding/test_data/meta_model/object_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/builtin_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/element_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/visitor_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/exception_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/primitive_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/enumeration_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/origin_types_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/object_template_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/technical_space_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/decoration/licence_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/static_stereotypes_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/configuration_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/artefact_properties_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/decoration/modeline_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/decoration/modeline_group_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/decoration/generation_marker_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/variability_profile_template_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/decoration/element_properties_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/variability/profile_template_new_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/variability_feature_template_group_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/local_archetype_location_properties_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/variability/feature_template_group_new_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/variability_feature_template_group_registrar_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/variability/feature_template_group_registrar_new_td.hpp"

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

masd::dogen::coding::meta_model::origin_types
create_masd_dogen_coding_meta_model_origin_types(const unsigned int position) {
    return masd::dogen::coding::meta_model::origin_types_generator::create(position);
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

masd::dogen::coding::meta_model::technical_space
create_masd_dogen_coding_meta_model_technical_space(const unsigned int position) {
    return masd::dogen::coding::meta_model::technical_space_generator::create(position);
}

masd::dogen::variability::meta_model::configuration*
create_masd_dogen_variability_meta_model_configuration_ptr(const unsigned int position) {
    return masd::dogen::variability::meta_model::configuration_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::variability::meta_model::configuration>
create_boost_shared_ptr_masd_dogen_variability_meta_model_configuration(unsigned int position) {
    boost::shared_ptr<masd::dogen::variability::meta_model::configuration> r(
        create_masd_dogen_variability_meta_model_configuration_ptr(position));
    return r;
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

masd::dogen::coding::meta_model::decoration::element_properties
create_masd_dogen_coding_meta_model_decoration_element_properties(const unsigned int position) {
    return masd::dogen::coding::meta_model::decoration::element_properties_generator::create(position);
}

boost::optional<masd::dogen::coding::meta_model::decoration::element_properties>
create_boost_optional_masd_dogen_coding_meta_model_decoration_element_properties(unsigned int position) {
    boost::optional<masd::dogen::coding::meta_model::decoration::element_properties> r(
        create_masd_dogen_coding_meta_model_decoration_element_properties(position));
    return r;
}

}

namespace masd::dogen::coding::meta_model {

void element_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_masd_dogen_coding_meta_model_name(position + 0));
    v.documentation(create_std_string(position + 1));
    v.origin_type(create_masd_dogen_coding_meta_model_origin_types(position + 2));
    v.contained_by(create_std_string(position + 3));
    v.in_global_module(create_bool(position + 4));
    v.static_stereotypes(create_std_list_masd_dogen_coding_meta_model_static_stereotypes(position + 5));
    v.dynamic_stereotypes(create_std_list_std_string(position + 6));
    v.meta_name(create_masd_dogen_coding_meta_model_name(position + 7));
    v.intrinsic_technical_space(create_masd_dogen_coding_meta_model_technical_space(position + 8));
    v.configuration(create_boost_shared_ptr_masd_dogen_variability_meta_model_configuration(position + 9));
    v.is_element_extension(create_bool(position + 10));
    v.artefact_properties(create_std_unordered_map_std_string_masd_dogen_coding_meta_model_artefact_properties(position + 11));
    v.archetype_location_properties(create_std_unordered_map_std_string_masd_dogen_coding_meta_model_local_archetype_location_properties(position + 12));
    v.decoration(create_boost_optional_masd_dogen_coding_meta_model_decoration_element_properties(position + 13));
}

element_generator::result_type*
element_generator::create_ptr(const unsigned int position) {
    if ((position % 17) == 0)
        return masd::dogen::coding::meta_model::decoration::generation_marker_generator::create_ptr(position);
    if ((position % 17) == 1)
        return masd::dogen::coding::meta_model::decoration::licence_generator::create_ptr(position);
    if ((position % 17) == 2)
        return masd::dogen::coding::meta_model::decoration::modeline_generator::create_ptr(position);
    if ((position % 17) == 3)
        return masd::dogen::coding::meta_model::decoration::modeline_group_generator::create_ptr(position);
    if ((position % 17) == 4)
        return masd::dogen::coding::meta_model::enumeration_generator::create_ptr(position);
    if ((position % 17) == 5)
        return masd::dogen::coding::meta_model::exception_generator::create_ptr(position);
    if ((position % 17) == 6)
        return masd::dogen::coding::meta_model::module_generator::create_ptr(position);
    if ((position % 17) == 7)
        return masd::dogen::coding::meta_model::object_generator::create_ptr(position);
    if ((position % 17) == 8)
        return masd::dogen::coding::meta_model::object_template_generator::create_ptr(position);
    if ((position % 17) == 9)
        return masd::dogen::coding::meta_model::primitive_generator::create_ptr(position);
    if ((position % 17) == 10)
        return masd::dogen::coding::meta_model::variability::feature_template_group_new_generator::create_ptr(position);
    if ((position % 17) == 11)
        return masd::dogen::coding::meta_model::variability::feature_template_group_registrar_new_generator::create_ptr(position);
    if ((position % 17) == 12)
        return masd::dogen::coding::meta_model::variability::profile_template_new_generator::create_ptr(position);
    if ((position % 17) == 13)
        return masd::dogen::coding::meta_model::variability_feature_template_group_generator::create_ptr(position);
    if ((position % 17) == 14)
        return masd::dogen::coding::meta_model::variability_feature_template_group_registrar_generator::create_ptr(position);
    if ((position % 17) == 15)
        return masd::dogen::coding::meta_model::variability_profile_template_generator::create_ptr(position);
    if ((position % 17) == 16)
        return masd::dogen::coding::meta_model::visitor_generator::create_ptr(position);
    return masd::dogen::coding::meta_model::builtin_generator::create_ptr(position);
}

}
