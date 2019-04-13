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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_TRANSFORMS_CONFIGURATION_TEMPLATE_INSTANTIATION_TRANSFORM_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_TRANSFORMS_CONFIGURATION_TEMPLATE_INSTANTIATION_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>

namespace masd::dogen::variability::transforms {

class configuration_template_instantiation_transform final {
public:
    configuration_template_instantiation_transform() = default;
    configuration_template_instantiation_transform(const configuration_template_instantiation_transform&) = default;
    configuration_template_instantiation_transform(configuration_template_instantiation_transform&&) = default;
    ~configuration_template_instantiation_transform() = default;
    configuration_template_instantiation_transform& operator=(const configuration_template_instantiation_transform&) = default;

public:
    bool operator==(const configuration_template_instantiation_transform& rhs) const;
    bool operator!=(const configuration_template_instantiation_transform& rhs) const {
        return !this->operator==(rhs);
    }

};

}

#endif
