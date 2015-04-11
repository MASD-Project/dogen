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
#ifndef DOGEN_STITCH_TYPES_BLOCK_VISITOR_HPP
#define DOGEN_STITCH_TYPES_BLOCK_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/stitch/types/text_block_fwd.hpp"
#include "dogen/stitch/types/scriptlet_block_fwd.hpp"
#include "dogen/stitch/types/mixed_content_block_fwd.hpp"

namespace dogen {
namespace stitch {

class block_visitor {
public:
    virtual ~block_visitor() noexcept = 0;

public:
    /**
     * @brief Accept visits for type dogen::stitch::mixed_content_block
     */
    /**@{*/
    virtual void visit(const dogen::stitch::mixed_content_block&) const { }
    virtual void visit(const dogen::stitch::mixed_content_block&) { }
    virtual void visit(dogen::stitch::mixed_content_block&) const { }
    virtual void visit(dogen::stitch::mixed_content_block&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::stitch::scriptlet_block
     */
    /**@{*/
    virtual void visit(const dogen::stitch::scriptlet_block&) const { }
    virtual void visit(const dogen::stitch::scriptlet_block&) { }
    virtual void visit(dogen::stitch::scriptlet_block&) const { }
    virtual void visit(dogen::stitch::scriptlet_block&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::stitch::text_block
     */
    /**@{*/
    virtual void visit(const dogen::stitch::text_block&) const { }
    virtual void visit(const dogen::stitch::text_block&) { }
    virtual void visit(dogen::stitch::text_block&) const { }
    virtual void visit(dogen::stitch::text_block&) { }
    /**@}*/
};

inline block_visitor::~block_visitor() noexcept { }

} }

#endif
