/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_DYNAMIC_SCHEMA_TYPES_VALUE_VISITOR_HPP
#define DOGEN_DYNAMIC_SCHEMA_TYPES_VALUE_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/dynamic/schema/types/text_fwd.hpp"
#include "dogen/dynamic/schema/types/boolean_fwd.hpp"
#include "dogen/dynamic/schema/types/text_collection_fwd.hpp"

namespace dogen {
namespace dynamic {
namespace schema {

class value_visitor {
public:
    virtual ~value_visitor() noexcept = 0;

public:
    /**
     * @brief Accept visits for type dogen::dynamic::schema::boolean
     */
    /**@{*/
    virtual void visit(const dogen::dynamic::schema::boolean&) const { }
    virtual void visit(const dogen::dynamic::schema::boolean&) { }
    virtual void visit(dogen::dynamic::schema::boolean&) const { }
    virtual void visit(dogen::dynamic::schema::boolean&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::dynamic::schema::text
     */
    /**@{*/
    virtual void visit(const dogen::dynamic::schema::text&) const { }
    virtual void visit(const dogen::dynamic::schema::text&) { }
    virtual void visit(dogen::dynamic::schema::text&) const { }
    virtual void visit(dogen::dynamic::schema::text&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::dynamic::schema::text_collection
     */
    /**@{*/
    virtual void visit(const dogen::dynamic::schema::text_collection&) const { }
    virtual void visit(const dogen::dynamic::schema::text_collection&) { }
    virtual void visit(dogen::dynamic::schema::text_collection&) const { }
    virtual void visit(dogen::dynamic::schema::text_collection&) { }
    /**@}*/
};

inline value_visitor::~value_visitor() noexcept { }

} } }

#endif
