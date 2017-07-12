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
#ifndef DOGEN_YARN_TYPES_META_MODEL_ELEMENT_VISITOR_HPP
#define DOGEN_YARN_TYPES_META_MODEL_ELEMENT_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/yarn/types/meta_model/module_fwd.hpp"
#include "dogen/yarn/types/meta_model/object_fwd.hpp"
#include "dogen/yarn/types/meta_model/builtin_fwd.hpp"
#include "dogen/yarn/types/meta_model/concept_fwd.hpp"
#include "dogen/yarn/types/meta_model/visitor_fwd.hpp"
#include "dogen/yarn/types/meta_model/exception_fwd.hpp"
#include "dogen/yarn/types/meta_model/primitive_fwd.hpp"
#include "dogen/yarn/types/meta_model/enumeration_fwd.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

/**
 * @brief Visitor for element
 */
class element_visitor {
public:
    virtual ~element_visitor() noexcept = 0;

public:
    /**
     * @brief Accept visits for type dogen::yarn::meta_model::builtin
     */
    /**@{*/
    virtual void visit(const dogen::yarn::meta_model::builtin&) const { }
    virtual void visit(const dogen::yarn::meta_model::builtin&) { }
    virtual void visit(dogen::yarn::meta_model::builtin&) const { }
    virtual void visit(dogen::yarn::meta_model::builtin&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::yarn::meta_model::concept
     */
    /**@{*/
    virtual void visit(const dogen::yarn::meta_model::concept&) const { }
    virtual void visit(const dogen::yarn::meta_model::concept&) { }
    virtual void visit(dogen::yarn::meta_model::concept&) const { }
    virtual void visit(dogen::yarn::meta_model::concept&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::yarn::meta_model::enumeration
     */
    /**@{*/
    virtual void visit(const dogen::yarn::meta_model::enumeration&) const { }
    virtual void visit(const dogen::yarn::meta_model::enumeration&) { }
    virtual void visit(dogen::yarn::meta_model::enumeration&) const { }
    virtual void visit(dogen::yarn::meta_model::enumeration&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::yarn::meta_model::exception
     */
    /**@{*/
    virtual void visit(const dogen::yarn::meta_model::exception&) const { }
    virtual void visit(const dogen::yarn::meta_model::exception&) { }
    virtual void visit(dogen::yarn::meta_model::exception&) const { }
    virtual void visit(dogen::yarn::meta_model::exception&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::yarn::meta_model::module
     */
    /**@{*/
    virtual void visit(const dogen::yarn::meta_model::module&) const { }
    virtual void visit(const dogen::yarn::meta_model::module&) { }
    virtual void visit(dogen::yarn::meta_model::module&) const { }
    virtual void visit(dogen::yarn::meta_model::module&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::yarn::meta_model::object
     */
    /**@{*/
    virtual void visit(const dogen::yarn::meta_model::object&) const { }
    virtual void visit(const dogen::yarn::meta_model::object&) { }
    virtual void visit(dogen::yarn::meta_model::object&) const { }
    virtual void visit(dogen::yarn::meta_model::object&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::yarn::meta_model::primitive
     */
    /**@{*/
    virtual void visit(const dogen::yarn::meta_model::primitive&) const { }
    virtual void visit(const dogen::yarn::meta_model::primitive&) { }
    virtual void visit(dogen::yarn::meta_model::primitive&) const { }
    virtual void visit(dogen::yarn::meta_model::primitive&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::yarn::meta_model::visitor
     */
    /**@{*/
    virtual void visit(const dogen::yarn::meta_model::visitor&) const { }
    virtual void visit(const dogen::yarn::meta_model::visitor&) { }
    virtual void visit(dogen::yarn::meta_model::visitor&) const { }
    virtual void visit(dogen::yarn::meta_model::visitor&) { }
    /**@}*/
};

inline element_visitor::~element_visitor() noexcept { }

} } }

#endif
