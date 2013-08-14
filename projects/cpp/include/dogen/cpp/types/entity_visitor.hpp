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
#ifndef DOGEN_CPP_TYPES_ENTITY_VISITOR_HPP
#define DOGEN_CPP_TYPES_ENTITY_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/cpp/types/class_info_fwd.hpp"
#include "dogen/cpp/types/enum_info_fwd.hpp"
#include "dogen/cpp/types/exception_info_fwd.hpp"
#include "dogen/cpp/types/namespace_info_fwd.hpp"
#include "dogen/cpp/types/registrar_info_fwd.hpp"
#include "dogen/cpp/types/visitor_info_fwd.hpp"

namespace dogen {
namespace cpp {

class entity_visitor {
public:
    virtual ~entity_visitor() noexcept = 0;

public:
    /**
     * @brief Accept visits for type dogen::cpp::class_info
     */
    /**@{*/
    virtual void visit(const dogen::cpp::class_info&) const { }
    virtual void visit(const dogen::cpp::class_info&) { }
    virtual void visit(dogen::cpp::class_info&) const { }
    virtual void visit(dogen::cpp::class_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::cpp::enum_info
     */
    /**@{*/
    virtual void visit(const dogen::cpp::enum_info&) const { }
    virtual void visit(const dogen::cpp::enum_info&) { }
    virtual void visit(dogen::cpp::enum_info&) const { }
    virtual void visit(dogen::cpp::enum_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::cpp::exception_info
     */
    /**@{*/
    virtual void visit(const dogen::cpp::exception_info&) const { }
    virtual void visit(const dogen::cpp::exception_info&) { }
    virtual void visit(dogen::cpp::exception_info&) const { }
    virtual void visit(dogen::cpp::exception_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::cpp::registrar_info
     */
    /**@{*/
    virtual void visit(const dogen::cpp::registrar_info&) const { }
    virtual void visit(const dogen::cpp::registrar_info&) { }
    virtual void visit(dogen::cpp::registrar_info&) const { }
    virtual void visit(dogen::cpp::registrar_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::cpp::namespace_info
     */
    /**@{*/
    virtual void visit(const dogen::cpp::namespace_info&) const { }
    virtual void visit(const dogen::cpp::namespace_info&) { }
    virtual void visit(dogen::cpp::namespace_info&) const { }
    virtual void visit(dogen::cpp::namespace_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::cpp::visitor_info
     */
    /**@{*/
    virtual void visit(const dogen::cpp::visitor_info&) const { }
    virtual void visit(const dogen::cpp::visitor_info&) { }
    virtual void visit(dogen::cpp::visitor_info&) const { }
    virtual void visit(dogen::cpp::visitor_info&) { }
    /**@}*/
};

inline entity_visitor::~entity_visitor() noexcept { }

} }

#endif
