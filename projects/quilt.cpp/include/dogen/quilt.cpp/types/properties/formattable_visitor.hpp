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
#ifndef DOGEN_QUILT_CPP_TYPES_PROPERTIES_FORMATTABLE_VISITOR_HPP
#define DOGEN_QUILT_CPP_TYPES_PROPERTIES_FORMATTABLE_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/quilt.cpp/types/properties/includers_info_fwd.hpp"
#include "dogen/quilt.cpp/types/properties/registrar_info_fwd.hpp"
#include "dogen/quilt.cpp/types/properties/cmakelists_info_fwd.hpp"
#include "dogen/quilt.cpp/types/properties/odb_options_info_fwd.hpp"
#include "dogen/quilt.cpp/types/properties/forward_declarations_info_fwd.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

/**
 * @brief Visitor for formattable
 */
class formattable_visitor {
public:
    virtual ~formattable_visitor() noexcept = 0;

public:
    /**
     * @brief Accept visits for type dogen::quilt::cpp::properties::cmakelists_info
     */
    /**@{*/
    virtual void visit(const dogen::quilt::cpp::properties::cmakelists_info&) const { }
    virtual void visit(const dogen::quilt::cpp::properties::cmakelists_info&) { }
    virtual void visit(dogen::quilt::cpp::properties::cmakelists_info&) const { }
    virtual void visit(dogen::quilt::cpp::properties::cmakelists_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::quilt::cpp::properties::forward_declarations_info
     */
    /**@{*/
    virtual void visit(const dogen::quilt::cpp::properties::forward_declarations_info&) const { }
    virtual void visit(const dogen::quilt::cpp::properties::forward_declarations_info&) { }
    virtual void visit(dogen::quilt::cpp::properties::forward_declarations_info&) const { }
    virtual void visit(dogen::quilt::cpp::properties::forward_declarations_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::quilt::cpp::properties::includers_info
     */
    /**@{*/
    virtual void visit(const dogen::quilt::cpp::properties::includers_info&) const { }
    virtual void visit(const dogen::quilt::cpp::properties::includers_info&) { }
    virtual void visit(dogen::quilt::cpp::properties::includers_info&) const { }
    virtual void visit(dogen::quilt::cpp::properties::includers_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::quilt::cpp::properties::odb_options_info
     */
    /**@{*/
    virtual void visit(const dogen::quilt::cpp::properties::odb_options_info&) const { }
    virtual void visit(const dogen::quilt::cpp::properties::odb_options_info&) { }
    virtual void visit(dogen::quilt::cpp::properties::odb_options_info&) const { }
    virtual void visit(dogen::quilt::cpp::properties::odb_options_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::quilt::cpp::properties::registrar_info
     */
    /**@{*/
    virtual void visit(const dogen::quilt::cpp::properties::registrar_info&) const { }
    virtual void visit(const dogen::quilt::cpp::properties::registrar_info&) { }
    virtual void visit(dogen::quilt::cpp::properties::registrar_info&) const { }
    virtual void visit(dogen::quilt::cpp::properties::registrar_info&) { }
    /**@}*/
};

inline formattable_visitor::~formattable_visitor() noexcept { }

} } } }

#endif
