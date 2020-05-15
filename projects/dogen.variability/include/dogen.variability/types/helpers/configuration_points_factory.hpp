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
#ifndef DOGEN_VARIABILITY_TYPES_HELPERS_CONFIGURATION_POINTS_FACTORY_HPP
#define DOGEN_VARIABILITY_TYPES_HELPERS_CONFIGURATION_POINTS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.variability/types/entities/binding_point.hpp"
#include "dogen.variability/types/entities/configuration_point.hpp"

namespace dogen::variability::helpers {

/**
 * @brief Makes configuration points.
 */
class configuration_points_factory final {
public:
    /**
     * @brief Initialise the configuration points factory.
     *
     * @param fm the feature model.
     * @param compatibility_mode if true, try to ignore some
     * resolution errors.
     */
    configuration_points_factory(const entities::feature_model& fm,
        const bool compatibility_mode);

    /**
     * @brief Ensures the feature can be bound to the supplied binding
     * type.
     */
    void validate_binding(const entities::feature& f,
        const entities::binding_point bp) const;

private:
    /**
     * @brief Returns the feature for the given qualified name.
     *
     * If the feature could not be found and compatibility mode was
     * requested, returns null. If compatibility mode was not
     * requested throws.
     */
    boost::optional<entities::feature>
    try_obtain_feature(const std::string& qn) const;

public:
    std::unordered_map<std::string, entities::configuration_point>
    make(const entities::binding_point bp,
        const std::list<std::pair<std::string, std::string>>& entries,
        const std::unordered_map<std::string, std::list<std::string>>&
        aggregated_override_entries) const;

    std::unordered_map<std::string, entities::configuration_point>
    make(const std::list<std::pair<std::string, std::string>>& entries) const;

private:
    const entities::feature_model& feature_model_;
    const bool compatibility_mode_;
};

}

#endif
