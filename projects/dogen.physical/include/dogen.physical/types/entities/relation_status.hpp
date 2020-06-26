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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_RELATION_STATUS_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_RELATION_STATUS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen::physical::entities {

/**
 * @brief Status of a given archetype with regards to being related to other archetypes.
 */
enum class relation_status : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    not_relatable = 1, ///< Archertype cannot be legally related to other archetypes.
    relatable = 2, ///< Archetype can be related to archetypes.
    facet_default = 3 ///< FIXME: hack for now
};

}

#endif
