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
#ifndef DOGEN_VARIABILITY_TYPES_HELPERS_ENUM_MAPPER_HPP
#define DOGEN_VARIABILITY_TYPES_HELPERS_ENUM_MAPPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen.variability/types/entities/value_type.hpp"
#include "dogen.variability/types/entities/binding_point.hpp"

namespace dogen::variability::helpers {

class enum_mapper final {
public:
    /**
     * @brief Converts a string to a value type.
     */
    static entities::value_type to_value_type(const std::string& s);

    /**
     * @brief Converts a string to a binding point.
     */
    static entities::binding_point to_binding_point(const std::string& s);

public:
    /**
     * @brief Converts a value type to a string.
     */
    static std::string from_value_type(const entities::value_type v,
        const bool qualified = true);

    /**
     * @brief Converts a binding point to a string.
     */
    static std::string from_binding_point(const entities::binding_point s);
};

}

#endif
