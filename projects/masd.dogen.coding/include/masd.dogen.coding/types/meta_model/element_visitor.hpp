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

#include "masd.dogen.coding/types/meta_model/module_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/object_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/builtin_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/licence_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/visitor_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/modeline_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/exception_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/primitive_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/enumeration_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/modeline_group_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/object_template_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/generation_marker_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/variability_profile_template_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/variability_feature_template_group_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/variability_feature_template_group_registrar_fwd.hpp"

namespace masd::dogen::coding::meta_model {

/**
 * @brief Visitor for element
 */
class element_visitor {
public:
    virtual ~element_visitor() noexcept = 0;

public:
    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::builtin
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::builtin&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::builtin&) { }
    virtual void visit(masd::dogen::coding::meta_model::builtin&) const { }
    virtual void visit(masd::dogen::coding::meta_model::builtin&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::enumeration
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::enumeration&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::enumeration&) { }
    virtual void visit(masd::dogen::coding::meta_model::enumeration&) const { }
    virtual void visit(masd::dogen::coding::meta_model::enumeration&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::exception
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::exception&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::exception&) { }
    virtual void visit(masd::dogen::coding::meta_model::exception&) const { }
    virtual void visit(masd::dogen::coding::meta_model::exception&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::generation_marker
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::generation_marker&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::generation_marker&) { }
    virtual void visit(masd::dogen::coding::meta_model::generation_marker&) const { }
    virtual void visit(masd::dogen::coding::meta_model::generation_marker&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::licence
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::licence&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::licence&) { }
    virtual void visit(masd::dogen::coding::meta_model::licence&) const { }
    virtual void visit(masd::dogen::coding::meta_model::licence&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::modeline
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::modeline&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::modeline&) { }
    virtual void visit(masd::dogen::coding::meta_model::modeline&) const { }
    virtual void visit(masd::dogen::coding::meta_model::modeline&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::modeline_group
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::modeline_group&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::modeline_group&) { }
    virtual void visit(masd::dogen::coding::meta_model::modeline_group&) const { }
    virtual void visit(masd::dogen::coding::meta_model::modeline_group&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::module
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::module&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::module&) { }
    virtual void visit(masd::dogen::coding::meta_model::module&) const { }
    virtual void visit(masd::dogen::coding::meta_model::module&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::object
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::object&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::object&) { }
    virtual void visit(masd::dogen::coding::meta_model::object&) const { }
    virtual void visit(masd::dogen::coding::meta_model::object&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::object_template
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::object_template&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::object_template&) { }
    virtual void visit(masd::dogen::coding::meta_model::object_template&) const { }
    virtual void visit(masd::dogen::coding::meta_model::object_template&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::primitive
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::primitive&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::primitive&) { }
    virtual void visit(masd::dogen::coding::meta_model::primitive&) const { }
    virtual void visit(masd::dogen::coding::meta_model::primitive&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::variability_feature_template_group
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::variability_feature_template_group&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::variability_feature_template_group&) { }
    virtual void visit(masd::dogen::coding::meta_model::variability_feature_template_group&) const { }
    virtual void visit(masd::dogen::coding::meta_model::variability_feature_template_group&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::variability_feature_template_group_registrar
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::variability_feature_template_group_registrar&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::variability_feature_template_group_registrar&) { }
    virtual void visit(masd::dogen::coding::meta_model::variability_feature_template_group_registrar&) const { }
    virtual void visit(masd::dogen::coding::meta_model::variability_feature_template_group_registrar&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::variability_profile_template
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::variability_profile_template&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::variability_profile_template&) { }
    virtual void visit(masd::dogen::coding::meta_model::variability_profile_template&) const { }
    virtual void visit(masd::dogen::coding::meta_model::variability_profile_template&) { }
    /**@}*/

    /**
     * @brief Accept visits for type masd::dogen::coding::meta_model::visitor
     */
    /**@{*/
    virtual void visit(const masd::dogen::coding::meta_model::visitor&) const { }
    virtual void visit(const masd::dogen::coding::meta_model::visitor&) { }
    virtual void visit(masd::dogen::coding::meta_model::visitor&) const { }
    virtual void visit(masd::dogen::coding::meta_model::visitor&) { }
    /**@}*/
};

inline element_visitor::~element_visitor() noexcept { }

}

#endif
