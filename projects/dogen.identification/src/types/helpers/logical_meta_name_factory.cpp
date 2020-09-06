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
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"

namespace {

/*
 * Prefix for the meta-names. Must match the artefact
 * configuration. This is going to be replaced by stereotypes.
*/
const std::string prefix("dogen.logical.entities.");

}

namespace dogen::identification::helpers {

using identification::entities::logical_meta_name;

logical_meta_name logical_meta_name_factory::make_name(const std::string& sn) {
    logical_meta_name r;
    r.simple(sn);
    entities::logical_meta_id id(prefix + sn);
    r.id(id);
    return r;
}

logical_meta_name logical_meta_name_factory::make_model_name() {
    static const auto r(make_name("model"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_module_name() {
    static const auto r(make_name("module"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_object_template_name() {
    static const auto r(make_name("object_template"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_builtin_name() {
    static const auto r(make_name("builtin"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_enumeration_name() {
    static const auto r(make_name("enumeration"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_primitive_name() {
    static const auto r(make_name("primitive"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_object_name() {
    static const auto r(make_name("object"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_exception_name() {
    static const auto r(make_name("exception"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_visitor_name() {
    static const auto r(make_name("visitor"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_entry_point_name() {
    static const auto r(make_name("entry_point"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_assistant_name() {
    static const auto r(make_name("assistant"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_licence_name() {
    static const auto r(make_name("licence"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_modeline_name() {
    static const auto r(make_name("modeline"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_modeline_group_name() {
    static const auto r(make_name("modeline_group"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_generation_marker_name() {
    static const auto r(make_name("generation_marker"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_variability_profile_name() {
    static const auto r(make_name("variability_profile"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_variability_profile_template_name() {
    static const auto r(make_name("variability_profile_template"));
    return r;
}

logical_meta_name logical_meta_name_factory::
make_variability_feature_template_bundle_name() {
    static const auto r(make_name("variability_feature_template_bundle"));
    return r;
}

logical_meta_name logical_meta_name_factory::
make_variability_feature_bundle_name() {
    static const auto r(make_name("variability_feature_bundle"));
    return r;
}

logical_meta_name logical_meta_name_factory::
make_variability_initializer_name() {
    static const auto r(make_name("variability_initializer"));
    return r;
}

logical_meta_name logical_meta_name_factory::
make_templating_logic_less_templates_name() {
    static const auto r(
        make_name("templating_logic_less_templates"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_serialization_type_registrar_name() {
    static const auto r(
        make_name("serialization_type_registrar"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_visual_studio_solution_name() {
    static const auto r(
        make_name("visual_studio_solution"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_visual_studio_project_name() {
    static const auto r(
        make_name("visual_studio_project"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_visual_studio_msbuild_targets_name() {
    static const auto r(
        make_name("visual_studio_msbuild_targets"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_orm_common_odb_options_name() {
    static const auto r(
        make_name("orm_common_odb_options"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_build_cmakelists_name() {
    static const auto r(
        make_name("build_cmakelists"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_physical_backend_name() {
    static const auto r(
        make_name("physical_backend"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_physical_facet_name() {
    static const auto r(
        make_name("physical_facet"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_physical_archetype_name() {
    static const auto r(
        make_name("physical_archetype"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_physical_archetype_kind_name() {
    static const auto r(
        make_name("physical_archetype_kind"));
    return r;
}

logical_meta_name logical_meta_name_factory::make_physical_part_name() {
    static const auto r(
        make_name("physical_part"));
    return r;
}

}
