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
#ifndef DOGEN_PHYSICAL_TYPES_TRANSFORMS_UPDATE_OUTPUTTING_PROPERTIES_TRANSFORM_HPP
#define DOGEN_PHYSICAL_TYPES_TRANSFORMS_UPDATE_OUTPUTTING_PROPERTIES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>

namespace dogen::physical::transforms {

class update_outputting_properties_transform final {
public:
    update_outputting_properties_transform() = default;
    update_outputting_properties_transform(const update_outputting_properties_transform&) = default;
    update_outputting_properties_transform(update_outputting_properties_transform&&) = default;
    ~update_outputting_properties_transform() = default;
    update_outputting_properties_transform& operator=(const update_outputting_properties_transform&) = default;

public:
    bool operator==(const update_outputting_properties_transform& rhs) const;
    bool operator!=(const update_outputting_properties_transform& rhs) const {
        return !this->operator==(rhs);
    }

};

}

#endif
