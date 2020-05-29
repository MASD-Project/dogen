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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_FLATTENING_STRATEGY_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_FLATTENING_STRATEGY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen::logical::helpers {

/**
 * @brief Strategies to apply when flattening a logical name into a list.
 */
enum class flattening_strategy : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    include_simple_name = 1, ///< Includes the simple name in the final list.
    exclude_simple_name = 2, ///< Excludes the simple name.
    exclude_simple_name_conditionally = 3 ///< Excludes the simple name if its the same as the last internal module name.
};

}

#endif
