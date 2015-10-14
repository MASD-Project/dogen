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
#ifndef DOGEN_TACK_TYPES_RELATIONSHIP_TYPES_HPP
#define DOGEN_TACK_TYPES_RELATIONSHIP_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace tack {

/**
 * @brief Ways in which a type can be related to another for indexing purposes.
 */
enum class relationship_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    original_parents = 1, ///< Types at the root of the inheritance hierarchy.
    parents = 2, ///< Types that are direct parents of this type.
    regular_associations = 3, ///< Types that are involved in aggregation or composition relationships.
    weak_associations = 4, ///< Types that are involved in aggregation or composition relationships via a pointer.
    leaves = 5, ///< Types that are at the bottom of the inheritance tree.
    visits = 6, ///< Types that are visited by this visitor.
    visited_by = 7, ///< Types that visit current type.
    modeled_concepts = 8, ///< Concepts modeled by this type.
    hash_container_keys = 9 ///< Type is a key in a hash container.
};

} }

#endif
