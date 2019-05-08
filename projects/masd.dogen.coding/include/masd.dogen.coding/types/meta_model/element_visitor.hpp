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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_ELEMENT_VISITOR_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_ELEMENT_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.coding/types/meta_model/structural/module_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/structural/object_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/decoration/licence_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/structural/builtin_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/structural/visitor_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/decoration/modeline_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/structural/exception_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/structural/primitive_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/structural/enumeration_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/decoration/modeline_group_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/structural/object_template_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/decoration/generation_marker_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/variability/profile_template_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/variability/feature_template_group_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/variability/feature_template_group_registrar_fwd.hpp"

namespace masd::dogen::coding::meta_model {

/**
 * @brief Visitor for element
 */
class element_visitor {
public:
    virtual ~element_visitor() noexcept = 0;

public:
    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::decoration::generation_marker
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::decoration::generation_marker&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::decoration::generation_marker&) { }
    virtual void visit(masd::dogen::coding::meta_model::decoration::generation_marker&) const { }
    virtual void visit(masd::dogen::coding::meta_model::decoration::generation_marker&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::decoration::licence
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::decoration::licence&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::decoration::licence&) { }
    virtual void visit(masd::dogen::coding::meta_model::decoration::licence&) const { }
    virtual void visit(masd::dogen::coding::meta_model::decoration::licence&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::decoration::modeline
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::decoration::modeline&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::decoration::modeline&) { }
    virtual void visit(masd::dogen::coding::meta_model::decoration::modeline&) const { }
    virtual void visit(masd::dogen::coding::meta_model::decoration::modeline&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::decoration::modeline_group
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::decoration::modeline_group&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::decoration::modeline_group&) { }
    virtual void visit(masd::dogen::coding::meta_model::decoration::modeline_group&) const { }
    virtual void visit(masd::dogen::coding::meta_model::decoration::modeline_group&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::structural::builtin
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::structural::builtin&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::structural::builtin&) { }
    virtual void visit(masd::dogen::coding::meta_model::structural::builtin&) const { }
    virtual void visit(masd::dogen::coding::meta_model::structural::builtin&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::structural::enumeration
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::structural::enumeration&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::structural::enumeration&) { }
    virtual void visit(masd::dogen::coding::meta_model::structural::enumeration&) const { }
    virtual void visit(masd::dogen::coding::meta_model::structural::enumeration&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::structural::exception
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::structural::exception&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::structural::exception&) { }
    virtual void visit(masd::dogen::coding::meta_model::structural::exception&) const { }
    virtual void visit(masd::dogen::coding::meta_model::structural::exception&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::structural::module
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::structural::module&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::structural::module&) { }
    virtual void visit(masd::dogen::coding::meta_model::structural::module&) const { }
    virtual void visit(masd::dogen::coding::meta_model::structural::module&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::structural::object
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::structural::object&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::structural::object&) { }
    virtual void visit(masd::dogen::coding::meta_model::structural::object&) const { }
    virtual void visit(masd::dogen::coding::meta_model::structural::object&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::structural::object_template
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::structural::object_template&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::structural::object_template&) { }
    virtual void visit(masd::dogen::coding::meta_model::structural::object_template&) const { }
    virtual void visit(masd::dogen::coding::meta_model::structural::object_template&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::structural::primitive
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::structural::primitive&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::structural::primitive&) { }
    virtual void visit(masd::dogen::coding::meta_model::structural::primitive&) const { }
    virtual void visit(masd::dogen::coding::meta_model::structural::primitive&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::structural::visitor
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::structural::visitor&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::structural::visitor&) { }
    virtual void visit(masd::dogen::coding::meta_model::structural::visitor&) const { }
    virtual void visit(masd::dogen::coding::meta_model::structural::visitor&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::variability::feature_template_group
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::variability::feature_template_group&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::variability::feature_template_group&) { }
    virtual void visit(masd::dogen::coding::meta_model::variability::feature_template_group&) const { }
    virtual void visit(masd::dogen::coding::meta_model::variability::feature_template_group&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::variability::feature_template_group_registrar
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::variability::feature_template_group_registrar&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::variability::feature_template_group_registrar&) { }
    virtual void visit(masd::dogen::coding::meta_model::variability::feature_template_group_registrar&) const { }
    virtual void visit(masd::dogen::coding::meta_model::variability::feature_template_group_registrar&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::variability::profile_template
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::variability::profile_template&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::variability::profile_template&) { }
    virtual void visit(masd::dogen::coding::meta_model::variability::profile_template&) const { }
    virtual void visit(masd::dogen::coding::meta_model::variability::profile_template&) { }
    /**@}*/
};

inline element_visitor::~element_visitor() noexcept { }

}

#endif
