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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_ELEMENT_VISITOR_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_ELEMENT_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.assets/types/meta_model/build/cmakelists_fwd.hpp"
#include "dogen.assets/types/meta_model/structural/module_fwd.hpp"
#include "dogen.assets/types/meta_model/structural/object_fwd.hpp"
#include "dogen.assets/types/meta_model/decoration/licence_fwd.hpp"
#include "dogen.assets/types/meta_model/structural/builtin_fwd.hpp"
#include "dogen.assets/types/meta_model/structural/visitor_fwd.hpp"
#include "dogen.assets/types/meta_model/decoration/modeline_fwd.hpp"
#include "dogen.assets/types/meta_model/structural/assistant_fwd.hpp"
#include "dogen.assets/types/meta_model/structural/exception_fwd.hpp"
#include "dogen.assets/types/meta_model/structural/primitive_fwd.hpp"
#include "dogen.assets/types/meta_model/visual_studio/project_fwd.hpp"
#include "dogen.assets/types/meta_model/mapping/fixed_mappable_fwd.hpp"
#include "dogen.assets/types/meta_model/orm/common_odb_options_fwd.hpp"
#include "dogen.assets/types/meta_model/structural/entry_point_fwd.hpp"
#include "dogen.assets/types/meta_model/structural/enumeration_fwd.hpp"
#include "dogen.assets/types/meta_model/visual_studio/solution_fwd.hpp"
#include "dogen.assets/types/meta_model/decoration/modeline_group_fwd.hpp"
#include "dogen.assets/types/meta_model/structural/object_template_fwd.hpp"
#include "dogen.assets/types/meta_model/variability/feature_bundle_fwd.hpp"
#include "dogen.assets/types/meta_model/mapping/extensible_mappable_fwd.hpp"
#include "dogen.assets/types/meta_model/decoration/generation_marker_fwd.hpp"
#include "dogen.assets/types/meta_model/serialization/type_registrar_fwd.hpp"
#include "dogen.assets/types/meta_model/variability/profile_template_fwd.hpp"
#include "dogen.assets/types/meta_model/visual_studio/msbuild_targets_fwd.hpp"
#include "dogen.assets/types/meta_model/templating/logic_less_template_fwd.hpp"
#include "dogen.assets/types/meta_model/variability/feature_template_bundle_fwd.hpp"
#include "dogen.assets/types/meta_model/variability/feature_template_initializer_fwd.hpp"

namespace dogen::assets::meta_model {

/**
 * @brief Visitor for element
 */
class element_visitor {
public:
    virtual ~element_visitor() noexcept = 0;

public:
    /**
     * @brief Accept visits for type dogen::assets::meta_model::build::cmakelists
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::build::cmakelists&) const { }
    virtual void visit(const dogen::assets::meta_model::build::cmakelists&) { }
    virtual void visit(dogen::assets::meta_model::build::cmakelists&) const { }
    virtual void visit(dogen::assets::meta_model::build::cmakelists&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::decoration::generation_marker
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::decoration::generation_marker&) const { }
    virtual void visit(const dogen::assets::meta_model::decoration::generation_marker&) { }
    virtual void visit(dogen::assets::meta_model::decoration::generation_marker&) const { }
    virtual void visit(dogen::assets::meta_model::decoration::generation_marker&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::decoration::licence
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::decoration::licence&) const { }
    virtual void visit(const dogen::assets::meta_model::decoration::licence&) { }
    virtual void visit(dogen::assets::meta_model::decoration::licence&) const { }
    virtual void visit(dogen::assets::meta_model::decoration::licence&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::decoration::modeline
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::decoration::modeline&) const { }
    virtual void visit(const dogen::assets::meta_model::decoration::modeline&) { }
    virtual void visit(dogen::assets::meta_model::decoration::modeline&) const { }
    virtual void visit(dogen::assets::meta_model::decoration::modeline&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::decoration::modeline_group
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::decoration::modeline_group&) const { }
    virtual void visit(const dogen::assets::meta_model::decoration::modeline_group&) { }
    virtual void visit(dogen::assets::meta_model::decoration::modeline_group&) const { }
    virtual void visit(dogen::assets::meta_model::decoration::modeline_group&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::mapping::extensible_mappable
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::mapping::extensible_mappable&) const { }
    virtual void visit(const dogen::assets::meta_model::mapping::extensible_mappable&) { }
    virtual void visit(dogen::assets::meta_model::mapping::extensible_mappable&) const { }
    virtual void visit(dogen::assets::meta_model::mapping::extensible_mappable&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::mapping::fixed_mappable
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::mapping::fixed_mappable&) const { }
    virtual void visit(const dogen::assets::meta_model::mapping::fixed_mappable&) { }
    virtual void visit(dogen::assets::meta_model::mapping::fixed_mappable&) const { }
    virtual void visit(dogen::assets::meta_model::mapping::fixed_mappable&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::orm::common_odb_options
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::orm::common_odb_options&) const { }
    virtual void visit(const dogen::assets::meta_model::orm::common_odb_options&) { }
    virtual void visit(dogen::assets::meta_model::orm::common_odb_options&) const { }
    virtual void visit(dogen::assets::meta_model::orm::common_odb_options&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::serialization::type_registrar
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::serialization::type_registrar&) const { }
    virtual void visit(const dogen::assets::meta_model::serialization::type_registrar&) { }
    virtual void visit(dogen::assets::meta_model::serialization::type_registrar&) const { }
    virtual void visit(dogen::assets::meta_model::serialization::type_registrar&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::structural::assistant
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::structural::assistant&) const { }
    virtual void visit(const dogen::assets::meta_model::structural::assistant&) { }
    virtual void visit(dogen::assets::meta_model::structural::assistant&) const { }
    virtual void visit(dogen::assets::meta_model::structural::assistant&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::structural::builtin
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::structural::builtin&) const { }
    virtual void visit(const dogen::assets::meta_model::structural::builtin&) { }
    virtual void visit(dogen::assets::meta_model::structural::builtin&) const { }
    virtual void visit(dogen::assets::meta_model::structural::builtin&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::structural::entry_point
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::structural::entry_point&) const { }
    virtual void visit(const dogen::assets::meta_model::structural::entry_point&) { }
    virtual void visit(dogen::assets::meta_model::structural::entry_point&) const { }
    virtual void visit(dogen::assets::meta_model::structural::entry_point&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::structural::enumeration
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::structural::enumeration&) const { }
    virtual void visit(const dogen::assets::meta_model::structural::enumeration&) { }
    virtual void visit(dogen::assets::meta_model::structural::enumeration&) const { }
    virtual void visit(dogen::assets::meta_model::structural::enumeration&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::structural::exception
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::structural::exception&) const { }
    virtual void visit(const dogen::assets::meta_model::structural::exception&) { }
    virtual void visit(dogen::assets::meta_model::structural::exception&) const { }
    virtual void visit(dogen::assets::meta_model::structural::exception&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::structural::module
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::structural::module&) const { }
    virtual void visit(const dogen::assets::meta_model::structural::module&) { }
    virtual void visit(dogen::assets::meta_model::structural::module&) const { }
    virtual void visit(dogen::assets::meta_model::structural::module&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::structural::object
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::structural::object&) const { }
    virtual void visit(const dogen::assets::meta_model::structural::object&) { }
    virtual void visit(dogen::assets::meta_model::structural::object&) const { }
    virtual void visit(dogen::assets::meta_model::structural::object&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::structural::object_template
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::structural::object_template&) const { }
    virtual void visit(const dogen::assets::meta_model::structural::object_template&) { }
    virtual void visit(dogen::assets::meta_model::structural::object_template&) const { }
    virtual void visit(dogen::assets::meta_model::structural::object_template&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::structural::primitive
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::structural::primitive&) const { }
    virtual void visit(const dogen::assets::meta_model::structural::primitive&) { }
    virtual void visit(dogen::assets::meta_model::structural::primitive&) const { }
    virtual void visit(dogen::assets::meta_model::structural::primitive&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::structural::visitor
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::structural::visitor&) const { }
    virtual void visit(const dogen::assets::meta_model::structural::visitor&) { }
    virtual void visit(dogen::assets::meta_model::structural::visitor&) const { }
    virtual void visit(dogen::assets::meta_model::structural::visitor&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::templating::logic_less_template
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::templating::logic_less_template&) const { }
    virtual void visit(const dogen::assets::meta_model::templating::logic_less_template&) { }
    virtual void visit(dogen::assets::meta_model::templating::logic_less_template&) const { }
    virtual void visit(dogen::assets::meta_model::templating::logic_less_template&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::variability::feature_bundle
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::variability::feature_bundle&) const { }
    virtual void visit(const dogen::assets::meta_model::variability::feature_bundle&) { }
    virtual void visit(dogen::assets::meta_model::variability::feature_bundle&) const { }
    virtual void visit(dogen::assets::meta_model::variability::feature_bundle&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::variability::feature_template_bundle
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::variability::feature_template_bundle&) const { }
    virtual void visit(const dogen::assets::meta_model::variability::feature_template_bundle&) { }
    virtual void visit(dogen::assets::meta_model::variability::feature_template_bundle&) const { }
    virtual void visit(dogen::assets::meta_model::variability::feature_template_bundle&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::variability::feature_template_initializer
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::variability::feature_template_initializer&) const { }
    virtual void visit(const dogen::assets::meta_model::variability::feature_template_initializer&) { }
    virtual void visit(dogen::assets::meta_model::variability::feature_template_initializer&) const { }
    virtual void visit(dogen::assets::meta_model::variability::feature_template_initializer&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::variability::profile_template
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::variability::profile_template&) const { }
    virtual void visit(const dogen::assets::meta_model::variability::profile_template&) { }
    virtual void visit(dogen::assets::meta_model::variability::profile_template&) const { }
    virtual void visit(dogen::assets::meta_model::variability::profile_template&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::visual_studio::msbuild_targets
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::visual_studio::msbuild_targets&) const { }
    virtual void visit(const dogen::assets::meta_model::visual_studio::msbuild_targets&) { }
    virtual void visit(dogen::assets::meta_model::visual_studio::msbuild_targets&) const { }
    virtual void visit(dogen::assets::meta_model::visual_studio::msbuild_targets&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::visual_studio::project
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::visual_studio::project&) const { }
    virtual void visit(const dogen::assets::meta_model::visual_studio::project&) { }
    virtual void visit(dogen::assets::meta_model::visual_studio::project&) const { }
    virtual void visit(dogen::assets::meta_model::visual_studio::project&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::assets::meta_model::visual_studio::solution
     */
    /**@{*/
    virtual void visit(const dogen::assets::meta_model::visual_studio::solution&) const { }
    virtual void visit(const dogen::assets::meta_model::visual_studio::solution&) { }
    virtual void visit(dogen::assets::meta_model::visual_studio::solution&) const { }
    virtual void visit(dogen::assets::meta_model::visual_studio::solution&) { }
    /**@}*/
};

inline element_visitor::~element_visitor() noexcept { }

}

#endif
