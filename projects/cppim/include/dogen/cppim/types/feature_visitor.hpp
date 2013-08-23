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
#ifndef DOGEN_CPPIM_TYPES_FEATURE_VISITOR_HPP
#define DOGEN_CPPIM_TYPES_FEATURE_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/cppim/types/licence_fwd.hpp"
#include "dogen/cppim/types/preamble_fwd.hpp"

namespace dogen {
namespace cppim {

class feature_visitor {
public:
    virtual ~feature_visitor() noexcept = 0;

public:
    /**
     * @brief Accept visits for type dogen::cppim::preamble
     */
    /**@{*/
    virtual void visit(const dogen::cppim::preamble&) const { }
    virtual void visit(const dogen::cppim::preamble&) { }
    virtual void visit(dogen::cppim::preamble&) const { }
    virtual void visit(dogen::cppim::preamble&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::cppim::licence
     */
    /**@{*/
    virtual void visit(const dogen::cppim::licence&) const { }
    virtual void visit(const dogen::cppim::licence&) { }
    virtual void visit(dogen::cppim::licence&) const { }
    virtual void visit(dogen::cppim::licence&) { }
    /**@}*/
};

inline feature_visitor::~feature_visitor() noexcept { }

} }

#endif
