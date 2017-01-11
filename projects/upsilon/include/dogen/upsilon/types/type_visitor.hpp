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
#ifndef DOGEN_UPSILON_TYPES_TYPE_VISITOR_HPP
#define DOGEN_UPSILON_TYPES_TYPE_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/upsilon/types/compound_fwd.hpp"
#include "dogen/upsilon/types/primitive_fwd.hpp"
#include "dogen/upsilon/types/collection_fwd.hpp"

namespace dogen {
namespace upsilon {

/**
 * @brief Visitor for type
 */
class type_visitor {
public:
    virtual ~type_visitor() noexcept = 0;

public:
    /**
     * @brief Accept visits for type dogen::upsilon::collection
     */
    /**@{*/
    virtual void visit(const dogen::upsilon::collection&) const { }
    virtual void visit(const dogen::upsilon::collection&) { }
    virtual void visit(dogen::upsilon::collection&) const { }
    virtual void visit(dogen::upsilon::collection&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::upsilon::compound
     */
    /**@{*/
    virtual void visit(const dogen::upsilon::compound&) const { }
    virtual void visit(const dogen::upsilon::compound&) { }
    virtual void visit(dogen::upsilon::compound&) const { }
    virtual void visit(dogen::upsilon::compound&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::upsilon::primitive
     */
    /**@{*/
    virtual void visit(const dogen::upsilon::primitive&) const { }
    virtual void visit(const dogen::upsilon::primitive&) { }
    virtual void visit(dogen::upsilon::primitive&) const { }
    virtual void visit(dogen::upsilon::primitive&) { }
    /**@}*/
};

inline type_visitor::~type_visitor() noexcept { }

} }

#endif
