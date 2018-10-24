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
#ifndef MASD_DOGEN_ANNOTATIONS_TYPES_TEMPLATE_KINDS_HPP
#define MASD_DOGEN_ANNOTATIONS_TYPES_TEMPLATE_KINDS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace masd::dogen::annotations {

enum class template_kinds : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    instance = 1,
    recursive_template = 2, ///< This field applies recursively, from the current level to all below.///<///< The starting point of the recursion is the level supplied by an archetype location.
    backend_template = 3, ///< This field applies to all backends.
    facet_template = 4, ///< This field applies to all facets.
    archetype_template = 5 ///< This field applies to all archetypes.
};

}

#endif
