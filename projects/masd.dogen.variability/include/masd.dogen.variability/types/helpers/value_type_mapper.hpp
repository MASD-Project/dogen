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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_HELPERS_VALUE_TYPE_MAPPER_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_HELPERS_VALUE_TYPE_MAPPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>

namespace masd::dogen::variability::helpers {

class value_type_mapper final {
public:
    value_type_mapper() = default;
    value_type_mapper(const value_type_mapper&) = default;
    value_type_mapper(value_type_mapper&&) = default;
    ~value_type_mapper() = default;
    value_type_mapper& operator=(const value_type_mapper&) = default;

public:
    bool operator==(const value_type_mapper& rhs) const;
    bool operator!=(const value_type_mapper& rhs) const {
        return !this->operator==(rhs);
    }

};

}

#endif
