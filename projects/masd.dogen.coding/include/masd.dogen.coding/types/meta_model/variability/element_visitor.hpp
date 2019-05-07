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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_VARIABILITY_ELEMENT_VISITOR_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_VARIABILITY_ELEMENT_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.coding/types/meta_model/element_visitor.hpp"
#include "masd.dogen.coding/types/meta_model/variability/profile_template_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/variability/feature_template_group_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/variability/feature_template_group_registrar_fwd.hpp"

namespace masd::dogen::coding::meta_model::variability {

/**
 * @brief Visitor for element
 */
class element_visitor : public masd::dogen::coding::meta_model::element_visitor {
public:
    virtual ~element_visitor() noexcept = 0;

public:
    using masd::dogen::coding::meta_model::element_visitor::visit;

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
