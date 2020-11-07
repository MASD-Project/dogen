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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_ELEMENT_VISITOR_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_ELEMENT_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.logical/types/entities/physical/part_fwd.hpp"
#include "dogen.logical/types/entities/physical/facet_fwd.hpp"
#include "dogen.logical/types/entities/physical/helper_fwd.hpp"
#include "dogen.logical/types/entities/build/cmakelists_fwd.hpp"
#include "dogen.logical/types/entities/physical/backend_fwd.hpp"
#include "dogen.logical/types/entities/structural/module_fwd.hpp"
#include "dogen.logical/types/entities/structural/object_fwd.hpp"
#include "dogen.logical/types/entities/decoration/licence_fwd.hpp"
#include "dogen.logical/types/entities/physical/archetype_fwd.hpp"
#include "dogen.logical/types/entities/structural/builtin_fwd.hpp"
#include "dogen.logical/types/entities/structural/visitor_fwd.hpp"
#include "dogen.logical/types/entities/decoration/modeline_fwd.hpp"
#include "dogen.logical/types/entities/variability/profile_fwd.hpp"
#include "dogen.logical/types/entities/structural/assistant_fwd.hpp"
#include "dogen.logical/types/entities/structural/exception_fwd.hpp"
#include "dogen.logical/types/entities/structural/primitive_fwd.hpp"
#include "dogen.logical/types/entities/visual_studio/project_fwd.hpp"
#include "dogen.logical/types/entities/mapping/fixed_mappable_fwd.hpp"
#include "dogen.logical/types/entities/orm/common_odb_options_fwd.hpp"
#include "dogen.logical/types/entities/structural/entry_point_fwd.hpp"
#include "dogen.logical/types/entities/structural/enumeration_fwd.hpp"
#include "dogen.logical/types/entities/visual_studio/solution_fwd.hpp"
#include "dogen.logical/types/entities/physical/archetype_kind_fwd.hpp"
#include "dogen.logical/types/entities/variability/initializer_fwd.hpp"
#include "dogen.logical/types/entities/decoration/modeline_group_fwd.hpp"
#include "dogen.logical/types/entities/structural/object_template_fwd.hpp"
#include "dogen.logical/types/entities/variability/feature_bundle_fwd.hpp"
#include "dogen.logical/types/entities/mapping/extensible_mappable_fwd.hpp"
#include "dogen.logical/types/entities/decoration/generation_marker_fwd.hpp"
#include "dogen.logical/types/entities/serialization/type_registrar_fwd.hpp"
#include "dogen.logical/types/entities/variability/profile_template_fwd.hpp"
#include "dogen.logical/types/entities/visual_studio/msbuild_targets_fwd.hpp"
#include "dogen.logical/types/entities/templating/logic_less_template_fwd.hpp"
#include "dogen.logical/types/entities/variability/feature_template_bundle_fwd.hpp"

namespace dogen::logical::entities {

/**
 * @brief Visitor for element
 */
class element_visitor {
public:
    virtual ~element_visitor() noexcept = 0;

public:
    /**
     * @brief Accept visits for type dogen::logical::entities::build::cmakelists
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::build::cmakelists&) const { }
    virtual void visit(const dogen::logical::entities::build::cmakelists&) { }
    virtual void visit(dogen::logical::entities::build::cmakelists&) const { }
    virtual void visit(dogen::logical::entities::build::cmakelists&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::decoration::generation_marker
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::decoration::generation_marker&) const { }
    virtual void visit(const dogen::logical::entities::decoration::generation_marker&) { }
    virtual void visit(dogen::logical::entities::decoration::generation_marker&) const { }
    virtual void visit(dogen::logical::entities::decoration::generation_marker&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::decoration::licence
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::decoration::licence&) const { }
    virtual void visit(const dogen::logical::entities::decoration::licence&) { }
    virtual void visit(dogen::logical::entities::decoration::licence&) const { }
    virtual void visit(dogen::logical::entities::decoration::licence&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::decoration::modeline
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::decoration::modeline&) const { }
    virtual void visit(const dogen::logical::entities::decoration::modeline&) { }
    virtual void visit(dogen::logical::entities::decoration::modeline&) const { }
    virtual void visit(dogen::logical::entities::decoration::modeline&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::decoration::modeline_group
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::decoration::modeline_group&) const { }
    virtual void visit(const dogen::logical::entities::decoration::modeline_group&) { }
    virtual void visit(dogen::logical::entities::decoration::modeline_group&) const { }
    virtual void visit(dogen::logical::entities::decoration::modeline_group&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::mapping::extensible_mappable
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::mapping::extensible_mappable&) const { }
    virtual void visit(const dogen::logical::entities::mapping::extensible_mappable&) { }
    virtual void visit(dogen::logical::entities::mapping::extensible_mappable&) const { }
    virtual void visit(dogen::logical::entities::mapping::extensible_mappable&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::mapping::fixed_mappable
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::mapping::fixed_mappable&) const { }
    virtual void visit(const dogen::logical::entities::mapping::fixed_mappable&) { }
    virtual void visit(dogen::logical::entities::mapping::fixed_mappable&) const { }
    virtual void visit(dogen::logical::entities::mapping::fixed_mappable&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::orm::common_odb_options
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::orm::common_odb_options&) const { }
    virtual void visit(const dogen::logical::entities::orm::common_odb_options&) { }
    virtual void visit(dogen::logical::entities::orm::common_odb_options&) const { }
    virtual void visit(dogen::logical::entities::orm::common_odb_options&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::physical::archetype
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::physical::archetype&) const { }
    virtual void visit(const dogen::logical::entities::physical::archetype&) { }
    virtual void visit(dogen::logical::entities::physical::archetype&) const { }
    virtual void visit(dogen::logical::entities::physical::archetype&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::physical::archetype_kind
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::physical::archetype_kind&) const { }
    virtual void visit(const dogen::logical::entities::physical::archetype_kind&) { }
    virtual void visit(dogen::logical::entities::physical::archetype_kind&) const { }
    virtual void visit(dogen::logical::entities::physical::archetype_kind&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::physical::backend
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::physical::backend&) const { }
    virtual void visit(const dogen::logical::entities::physical::backend&) { }
    virtual void visit(dogen::logical::entities::physical::backend&) const { }
    virtual void visit(dogen::logical::entities::physical::backend&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::physical::facet
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::physical::facet&) const { }
    virtual void visit(const dogen::logical::entities::physical::facet&) { }
    virtual void visit(dogen::logical::entities::physical::facet&) const { }
    virtual void visit(dogen::logical::entities::physical::facet&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::physical::helper
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::physical::helper&) const { }
    virtual void visit(const dogen::logical::entities::physical::helper&) { }
    virtual void visit(dogen::logical::entities::physical::helper&) const { }
    virtual void visit(dogen::logical::entities::physical::helper&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::physical::part
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::physical::part&) const { }
    virtual void visit(const dogen::logical::entities::physical::part&) { }
    virtual void visit(dogen::logical::entities::physical::part&) const { }
    virtual void visit(dogen::logical::entities::physical::part&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::serialization::type_registrar
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::serialization::type_registrar&) const { }
    virtual void visit(const dogen::logical::entities::serialization::type_registrar&) { }
    virtual void visit(dogen::logical::entities::serialization::type_registrar&) const { }
    virtual void visit(dogen::logical::entities::serialization::type_registrar&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::structural::assistant
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::structural::assistant&) const { }
    virtual void visit(const dogen::logical::entities::structural::assistant&) { }
    virtual void visit(dogen::logical::entities::structural::assistant&) const { }
    virtual void visit(dogen::logical::entities::structural::assistant&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::structural::builtin
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::structural::builtin&) const { }
    virtual void visit(const dogen::logical::entities::structural::builtin&) { }
    virtual void visit(dogen::logical::entities::structural::builtin&) const { }
    virtual void visit(dogen::logical::entities::structural::builtin&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::structural::entry_point
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::structural::entry_point&) const { }
    virtual void visit(const dogen::logical::entities::structural::entry_point&) { }
    virtual void visit(dogen::logical::entities::structural::entry_point&) const { }
    virtual void visit(dogen::logical::entities::structural::entry_point&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::structural::enumeration
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::structural::enumeration&) const { }
    virtual void visit(const dogen::logical::entities::structural::enumeration&) { }
    virtual void visit(dogen::logical::entities::structural::enumeration&) const { }
    virtual void visit(dogen::logical::entities::structural::enumeration&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::structural::exception
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::structural::exception&) const { }
    virtual void visit(const dogen::logical::entities::structural::exception&) { }
    virtual void visit(dogen::logical::entities::structural::exception&) const { }
    virtual void visit(dogen::logical::entities::structural::exception&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::structural::module
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::structural::module&) const { }
    virtual void visit(const dogen::logical::entities::structural::module&) { }
    virtual void visit(dogen::logical::entities::structural::module&) const { }
    virtual void visit(dogen::logical::entities::structural::module&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::structural::object
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::structural::object&) const { }
    virtual void visit(const dogen::logical::entities::structural::object&) { }
    virtual void visit(dogen::logical::entities::structural::object&) const { }
    virtual void visit(dogen::logical::entities::structural::object&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::structural::object_template
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::structural::object_template&) const { }
    virtual void visit(const dogen::logical::entities::structural::object_template&) { }
    virtual void visit(dogen::logical::entities::structural::object_template&) const { }
    virtual void visit(dogen::logical::entities::structural::object_template&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::structural::primitive
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::structural::primitive&) const { }
    virtual void visit(const dogen::logical::entities::structural::primitive&) { }
    virtual void visit(dogen::logical::entities::structural::primitive&) const { }
    virtual void visit(dogen::logical::entities::structural::primitive&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::structural::visitor
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::structural::visitor&) const { }
    virtual void visit(const dogen::logical::entities::structural::visitor&) { }
    virtual void visit(dogen::logical::entities::structural::visitor&) const { }
    virtual void visit(dogen::logical::entities::structural::visitor&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::templating::logic_less_template
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::templating::logic_less_template&) const { }
    virtual void visit(const dogen::logical::entities::templating::logic_less_template&) { }
    virtual void visit(dogen::logical::entities::templating::logic_less_template&) const { }
    virtual void visit(dogen::logical::entities::templating::logic_less_template&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::variability::feature_bundle
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::variability::feature_bundle&) const { }
    virtual void visit(const dogen::logical::entities::variability::feature_bundle&) { }
    virtual void visit(dogen::logical::entities::variability::feature_bundle&) const { }
    virtual void visit(dogen::logical::entities::variability::feature_bundle&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::variability::feature_template_bundle
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::variability::feature_template_bundle&) const { }
    virtual void visit(const dogen::logical::entities::variability::feature_template_bundle&) { }
    virtual void visit(dogen::logical::entities::variability::feature_template_bundle&) const { }
    virtual void visit(dogen::logical::entities::variability::feature_template_bundle&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::variability::initializer
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::variability::initializer&) const { }
    virtual void visit(const dogen::logical::entities::variability::initializer&) { }
    virtual void visit(dogen::logical::entities::variability::initializer&) const { }
    virtual void visit(dogen::logical::entities::variability::initializer&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::variability::profile
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::variability::profile&) const { }
    virtual void visit(const dogen::logical::entities::variability::profile&) { }
    virtual void visit(dogen::logical::entities::variability::profile&) const { }
    virtual void visit(dogen::logical::entities::variability::profile&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::variability::profile_template
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::variability::profile_template&) const { }
    virtual void visit(const dogen::logical::entities::variability::profile_template&) { }
    virtual void visit(dogen::logical::entities::variability::profile_template&) const { }
    virtual void visit(dogen::logical::entities::variability::profile_template&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::visual_studio::msbuild_targets
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::visual_studio::msbuild_targets&) const { }
    virtual void visit(const dogen::logical::entities::visual_studio::msbuild_targets&) { }
    virtual void visit(dogen::logical::entities::visual_studio::msbuild_targets&) const { }
    virtual void visit(dogen::logical::entities::visual_studio::msbuild_targets&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::visual_studio::project
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::visual_studio::project&) const { }
    virtual void visit(const dogen::logical::entities::visual_studio::project&) { }
    virtual void visit(dogen::logical::entities::visual_studio::project&) const { }
    virtual void visit(dogen::logical::entities::visual_studio::project&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::logical::entities::visual_studio::solution
     */
    /**@{*/
    virtual void visit(const dogen::logical::entities::visual_studio::solution&) const { }
    virtual void visit(const dogen::logical::entities::visual_studio::solution&) { }
    virtual void visit(dogen::logical::entities::visual_studio::solution&) const { }
    virtual void visit(dogen::logical::entities::visual_studio::solution&) { }
    /**@}*/
};

inline element_visitor::~element_visitor() noexcept { }

}

#endif
