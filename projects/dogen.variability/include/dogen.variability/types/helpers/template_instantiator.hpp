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
#ifndef DOGEN_VARIABILITY_TYPES_HELPERS_TEMPLATE_INSTANTIATOR_HPP
#define DOGEN_VARIABILITY_TYPES_HELPERS_TEMPLATE_INSTANTIATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_map>
#include "dogen.variability/types/meta_model/feature.hpp"
#include "dogen.variability/types/meta_model/profile.hpp"
#include "dogen.variability/types/meta_model/feature_model.hpp"
#include "dogen.variability/types/meta_model/profile_template.hpp"
#include "dogen.variability/types/meta_model/feature_template.hpp"
#include "dogen.variability/types/meta_model/configuration_point.hpp"
#include "dogen.variability/types/meta_model/configuration_point_template.hpp"

namespace dogen::variability::helpers {

/**
 * @brief Instantiates profile templates and feature templates.
 */
class template_instantiator final {
public:
    /**
     * @brief Initialises the instantiator.
     *
     * @param compatibility_mode if true, keep processing even on
     * instantiation errors.
     */
    explicit template_instantiator(const bool compatibility_mode);

private:
    /**
     * @brief Returns true if the value type allows partial matching.
     */
    bool is_partially_mathcable(const meta_model::value_type vt) const;

private:
    /**
     * @brief Instantiates a configuration point template into a
     * configuration point.
     */
    meta_model::configuration_point to_configuration_point(
        const meta_model::feature_model& fm, const std::string& owner,
        const meta_model::configuration_point_template& cpt) const;

    /*
     * @brief Expands a feature template into a feature.
     */
    meta_model::feature to_feature(const std::string& domain,
        const meta_model::feature_template& ft) const;

private:
    std::list<meta_model::configuration_point>
    instantiate(const std::unordered_map<std::string, std::vector<std::string>>&
        template_instantiation_domains, const meta_model::feature_model& fm,
        const meta_model::configuration_point_template& cpt) const;

public:
    /**
     * @brief Instantiates the feature template across the elements of
     * the requested domain.
     */
    std::list<meta_model::feature> instantiate(
        const std::unordered_map<std::string, std::vector<std::string>>&
        template_instantiation_domains,
        const meta_model::feature_template& ft) const;

    /**
     * @brief Instantiates a profile template across the elements of
     * the requested domain.
     */
    meta_model::profile instantiate(
        const std::unordered_map<std::string, std::vector<std::string>>&
        template_instantiation_domains, const meta_model::feature_model& fm,
        const meta_model::profile_template& pt) const;

private:
    const bool compatibility_mode_;
};

}

#endif
