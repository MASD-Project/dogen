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
#ifndef DOGEN_VARIABILITY_TYPES_HELPERS_CONFIGURATION_FACTORY_HPP
#define DOGEN_VARIABILITY_TYPES_HELPERS_CONFIGURATION_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.identification/types/entities/tagged_value.hpp"
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/binding_point.hpp"
#include "dogen.variability/types/helpers/configuration_points_factory.hpp"

namespace dogen::variability::helpers {

/**
 * @brief Produces a configuration object from raw data.
 */
class configuration_factory final {
public:
    /**
     * @brief Initialise the configuration factory.
     *
     * @param fm the feature model.
     * @param compatibility_mode if true, try to ignore some
     * resolution errors.
     */
    configuration_factory(const entities::feature_model& fm,
        const bool compatibility_mode);

private:
    /**
     * @brief Given a binding type, returns the well-known name of its
     * the default configuration.
     */
    std::string get_default_configuration_name_for_binding_point(
        const entities::binding_point bp) const;

private:
    /**
     * @brief Aggregate entry data by key.
     */
    std::unordered_map<std::string, std::list<std::string>>
    aggregate_entries(const std::list<identification::entities::tagged_value>&
        entries) const;

public:
    /**
     * @brief Create a configuration.
     */
    entities::configuration
    make(const std::list<identification::entities::tagged_value>& entries,
        const std::list<identification::entities::tagged_value>&
        override_entries, const entities::binding_point bp) const;

    /**
     * @brief Create a configuration as a shared pointer.
     */
    boost::shared_ptr<entities::configuration>
    make_shared_ptr(
        const std::list<identification::entities::tagged_value>& tagged_values,
        const std::list<identification::entities::tagged_value>&
        tagged_values_overrides, const entities::binding_point bp) const;

private:
    const configuration_points_factory configuration_points_factory_;
};

}

#endif
