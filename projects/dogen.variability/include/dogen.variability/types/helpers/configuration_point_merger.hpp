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
#ifndef DOGEN_VARIABILITY_TYPES_HELPERS_CONFIGURATION_POINT_MERGER_HPP
#define DOGEN_VARIABILITY_TYPES_HELPERS_CONFIGURATION_POINT_MERGER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen.variability/types/entities/configuration_point.hpp"

namespace dogen::variability::helpers {

/**
 * @brief Merges two configurations.
 *
 * Merging works by taking all configuration points in lhs and rhs and
 * making a configuration with their superset. If a key exists in
 * both, rhs takes precedence. Note that this makes merging
 * non-commutative, so the order of lhs/rhs matters.
 */
class configuration_point_merger final {
public:
    /**
     * @brief Merges the two configurations according to the merging
     * rules,
     */
    std::unordered_map<std::string, entities::configuration_point> merge(
        const std::string& lhs_name, const std::unordered_map<std::string,
        entities::configuration_point>& lhs,
        const std::string& rhs_name, const std::unordered_map<std::string,
        entities::configuration_point>& rhs) const;
};

}

#endif
