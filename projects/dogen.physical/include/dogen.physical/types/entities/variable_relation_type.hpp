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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_VARIABLE_RELATION_TYPE_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_VARIABLE_RELATION_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen::physical::entities {

/**
 * @brief Lists all of the valid variable relation types.
 */
enum class variable_relation_type : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    self = 1, ///< Logical element is related to itself across different projections.
    parent = 2, ///< Parent of logical element.
    child = 3, ///< Child of logical element.
    transparent = 4, ///< The relation with another logical element requires the element's full definition.
    opaque = 5, ///< The relation with another logical element does not requires its full definition.
    associative_key = 6, ///< The associated element is used as an associative key.
    visitation = 7 ///< The associated element visits or is visited by the current element.
};

}

#endif
