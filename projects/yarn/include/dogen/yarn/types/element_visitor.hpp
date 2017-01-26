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
#ifndef DOGEN_YARN_TYPES_ELEMENT_VISITOR_HPP
#define DOGEN_YARN_TYPES_ELEMENT_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/yarn/types/module_fwd.hpp"
#include "dogen/yarn/types/object_fwd.hpp"
#include "dogen/yarn/types/builtin_fwd.hpp"
#include "dogen/yarn/types/concept_fwd.hpp"
#include "dogen/yarn/types/visitor_fwd.hpp"
#include "dogen/yarn/types/exception_fwd.hpp"
#include "dogen/yarn/types/primitive_fwd.hpp"
#include "dogen/yarn/types/enumeration_fwd.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Visitor for element
 */
class element_visitor {
public:
    virtual ~element_visitor() noexcept = 0;

public:
    /**
     * @brief Accept visits for type dogen::yarn::builtin
     */
    /**@{*/
    virtual void visit(const dogen::yarn::builtin&) const { }
    virtual void visit(const dogen::yarn::builtin&) { }
    virtual void visit(dogen::yarn::builtin&) const { }
    virtual void visit(dogen::yarn::builtin&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::yarn::concept
     */
    /**@{*/
    virtual void visit(const dogen::yarn::concept&) const { }
    virtual void visit(const dogen::yarn::concept&) { }
    virtual void visit(dogen::yarn::concept&) const { }
    virtual void visit(dogen::yarn::concept&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::yarn::enumeration
     */
    /**@{*/
    virtual void visit(const dogen::yarn::enumeration&) const { }
    virtual void visit(const dogen::yarn::enumeration&) { }
    virtual void visit(dogen::yarn::enumeration&) const { }
    virtual void visit(dogen::yarn::enumeration&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::yarn::exception
     */
    /**@{*/
    virtual void visit(const dogen::yarn::exception&) const { }
    virtual void visit(const dogen::yarn::exception&) { }
    virtual void visit(dogen::yarn::exception&) const { }
    virtual void visit(dogen::yarn::exception&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::yarn::module
     */
    /**@{*/
    virtual void visit(const dogen::yarn::module&) const { }
    virtual void visit(const dogen::yarn::module&) { }
    virtual void visit(dogen::yarn::module&) const { }
    virtual void visit(dogen::yarn::module&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::yarn::object
     */
    /**@{*/
    virtual void visit(const dogen::yarn::object&) const { }
    virtual void visit(const dogen::yarn::object&) { }
    virtual void visit(dogen::yarn::object&) const { }
    virtual void visit(dogen::yarn::object&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::yarn::primitive
     */
    /**@{*/
    virtual void visit(const dogen::yarn::primitive&) const { }
    virtual void visit(const dogen::yarn::primitive&) { }
    virtual void visit(dogen::yarn::primitive&) const { }
    virtual void visit(dogen::yarn::primitive&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::yarn::visitor
     */
    /**@{*/
    virtual void visit(const dogen::yarn::visitor&) const { }
    virtual void visit(const dogen::yarn::visitor&) { }
    virtual void visit(dogen::yarn::visitor&) const { }
    virtual void visit(dogen::yarn::visitor&) { }
    /**@}*/
};

inline element_visitor::~element_visitor() noexcept { }

} }

#endif
