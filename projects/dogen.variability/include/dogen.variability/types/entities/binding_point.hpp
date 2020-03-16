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
#ifndef DOGEN_VARIABILITY_TYPES_ENTITIES_BINDING_POINT_HPP
#define DOGEN_VARIABILITY_TYPES_ENTITIES_BINDING_POINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen::variability::entities {

/**
 * @brief Determines how a feature can be bound to a modeling element.
 */
enum class binding_point : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    any = 1, ///< Feature can be configured anywhere.
    global = 2, ///< Feature can only be configured in the root module.
    element = 3, ///< Feature can be configured in any modeling element.
    property = 4, ///< Feature can only be configured in a property of a modeling element.
    operation = 5 ///< Feature can only be configured in an operation of a modeling element.
};

}

#endif
