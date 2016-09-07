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
#ifndef DOGEN_YARN_TYPES_VISITATION_TYPES_HPP
#define DOGEN_YARN_TYPES_VISITATION_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace yarn {

enum class visitation_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    not_visitable = 1, ///< Element is not part of a visitation relationship.
    visitation_root = 2, ///< Element is the top-most element in a generalisation relationship and is visitable.
    visitation_child_parent_visitor = 3, ///< Element is not the top-most element in a generalisation relationship, where the///< root is visitable.
    visitation_child_descendant_visitor = 4 ///< Element is not the top-most element in a generalisation relationship, where the///< root is visitable and the visitor uses inheritance.
};

} }

#endif
