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
#include "masd.dogen.coding/test_data/meta_model/model_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/origin_types_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/technical_space_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/structural/module_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/structural/object_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/decoration/licence_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/structural/builtin_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/structural/visitor_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/decoration/modeline_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/orm/model_properties_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/structural/exception_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/structural/primitive_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/extraction_properties_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/structural/enumeration_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/decoration/modeline_group_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/structural/object_template_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/decoration/generation_marker_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/variability/profile_template_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/variability/feature_template_group_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/variability/feature_template_group_registrar_td.hpp"

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

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
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

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::module> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_module(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::module> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_module(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::structural::object_template*
create_masd_dogen_coding_meta_model_structural_object_template_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::structural::object_template_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::structural::object_template>
create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_object_template(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::object_template> r(
        create_masd_dogen_coding_meta_model_structural_object_template_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object_template> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_object_template(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object_template> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_object_template(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::structural::builtin*
create_masd_dogen_coding_meta_model_structural_builtin_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::structural::builtin_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::structural::builtin>
create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_builtin(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::builtin> r(
        create_masd_dogen_coding_meta_model_structural_builtin_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::builtin> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_builtin(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::builtin> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_builtin(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::structural::enumeration*
create_masd_dogen_coding_meta_model_structural_enumeration_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::structural::enumeration_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::structural::enumeration>
create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_enumeration(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::enumeration> r(
        create_masd_dogen_coding_meta_model_structural_enumeration_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::enumeration> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_enumeration(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::enumeration> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_enumeration(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::structural::primitive*
create_masd_dogen_coding_meta_model_structural_primitive_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::structural::primitive_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::structural::primitive>
create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_primitive(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::primitive> r(
        create_masd_dogen_coding_meta_model_structural_primitive_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::primitive> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_primitive(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::primitive> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_primitive(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::structural::object*
create_masd_dogen_coding_meta_model_structural_object_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::structural::object_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::structural::object>
create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_object(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::object> r(
        create_masd_dogen_coding_meta_model_structural_object_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_object(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_object(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::structural::exception*
create_masd_dogen_coding_meta_model_structural_exception_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::structural::exception_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::structural::exception>
create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_exception(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::exception> r(
        create_masd_dogen_coding_meta_model_structural_exception_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::exception> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_exception(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::exception> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_exception(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::structural::visitor*
create_masd_dogen_coding_meta_model_structural_visitor_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::structural::visitor_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::structural::visitor>
create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_visitor(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::visitor> r(
        create_masd_dogen_coding_meta_model_structural_visitor_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::visitor> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_visitor(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::visitor> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_visitor(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::decoration::modeline_group*
create_masd_dogen_coding_meta_model_decoration_modeline_group_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::decoration::modeline_group_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline_group>
create_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_modeline_group(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline_group> r(
        create_masd_dogen_coding_meta_model_decoration_modeline_group_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline_group> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_modeline_group(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline_group> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_modeline_group(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::decoration::modeline*
create_masd_dogen_coding_meta_model_decoration_modeline_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::decoration::modeline_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline>
create_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_modeline(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline> r(
        create_masd_dogen_coding_meta_model_decoration_modeline_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_modeline(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::modeline> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_modeline(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::decoration::licence*
create_masd_dogen_coding_meta_model_decoration_licence_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::decoration::licence_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::decoration::licence>
create_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_licence(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::decoration::licence> r(
        create_masd_dogen_coding_meta_model_decoration_licence_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::licence> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_licence(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::licence> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_licence(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::decoration::generation_marker*
create_masd_dogen_coding_meta_model_decoration_generation_marker_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::decoration::generation_marker_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::decoration::generation_marker>
create_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_generation_marker(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::decoration::generation_marker> r(
        create_masd_dogen_coding_meta_model_decoration_generation_marker_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::generation_marker> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_generation_marker(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::decoration::generation_marker> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_generation_marker(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::variability::profile_template*
create_masd_dogen_coding_meta_model_variability_profile_template_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::variability::profile_template_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template>
create_boost_shared_ptr_masd_dogen_coding_meta_model_variability_profile_template(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> r(
        create_masd_dogen_coding_meta_model_variability_profile_template_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_variability_profile_template(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_variability_profile_template(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::variability::feature_template_group*
create_masd_dogen_coding_meta_model_variability_feature_template_group_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::variability::feature_template_group_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group>
create_boost_shared_ptr_masd_dogen_coding_meta_model_variability_feature_template_group(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group> r(
        create_masd_dogen_coding_meta_model_variability_feature_template_group_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_variability_feature_template_group(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_variability_feature_template_group(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::variability::feature_template_group_registrar*
create_masd_dogen_coding_meta_model_variability_feature_template_group_registrar_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::variability::feature_template_group_registrar_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group_registrar>
create_boost_shared_ptr_masd_dogen_coding_meta_model_variability_feature_template_group_registrar(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_group_registrar> r(
        create_masd_dogen_coding_meta_model_variability_feature_template_group_registrar_ptr(position));
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
    v.modules(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_module(position + 5));
    v.object_templates(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_object_template(position + 6));
    v.builtins(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_builtin(position + 7));
    v.enumerations(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_enumeration(position + 8));
    v.primitives(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_primitive(position + 9));
    v.objects(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_object(position + 10));
    v.exceptions(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_exception(position + 11));
    v.visitors(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_visitor(position + 12));
    v.modeline_groups(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_modeline_group(position + 13));
    v.modelines(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_modeline(position + 14));
    v.licences(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_licence(position + 15));
    v.generation_markers(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_decoration_generation_marker(position + 16));
    v.variability_profile_templates(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_variability_profile_template(position + 17));
    v.variability_feature_template_groups(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_variability_feature_template_group(position + 18));
    v.variability_feature_template_group_registrar(create_boost_shared_ptr_masd_dogen_coding_meta_model_variability_feature_template_group_registrar(position + 19));
    v.root_module(create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_module(position + 20));
    v.input_technical_space(create_masd_dogen_coding_meta_model_technical_space(position + 21));
    v.output_technical_spaces(create_std_list_masd_dogen_coding_meta_model_technical_space(position + 22));
    v.orm_properties(create_boost_optional_masd_dogen_coding_meta_model_orm_model_properties(position + 23));
    v.extraction_properties(create_masd_dogen_coding_meta_model_extraction_properties(position + 24));
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
