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
#include <forward_list>
#include <unordered_set>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.archetypes/types/location_repository.hpp"
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
     * @param alrp Archetype location repository.
     */
    template_instantiator(const archetypes::location_repository& alrp,
        const bool compatibility_mode);

private:
    /**
     * @brief Returns true if the kind of template can be
     * instantiated, false otherwise.
     */
    bool is_instantiable(const meta_model::template_kind tk) const;

    /**
     * @brief Returns true if the value type allows partial matching.
     */
    bool is_partially_mathcable(const meta_model::value_type vt) const;

    /**
     * @brief Returns true if there is a match between lhs and rhs,
     * according to the matching rules.
     */
    bool is_match(const std::string& lhs, const std::string& rhs) const;

private:
    /**
     * @brief Ensures the supplied parameters result in a valid
     * instantiation.
     */
    void validate(const archetypes::location& al, const meta_model::name& n,
        const meta_model::template_kind tk) const;

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
    meta_model::feature to_feature(const meta_model::feature_template& ft) const;

private:
    /**
     * @brief Instantiates a configuration point template that is
     * recursive across archetype space.
     */
    std::list<meta_model::configuration_point>
    instantiate_recursive_template(const meta_model::feature_model& fm,
        const meta_model::configuration_point_template& cpt) const;

    /**
     * @brief Instantiates the configuration point template for all
     * available facets in archetype space.
     */
    std::list<meta_model::configuration_point>
    instantiate_facet_template(const meta_model::feature_model& fm,
        const meta_model::configuration_point_template& cpt) const;

    /**
     * @brief Instantiates the configuration point template for all
     * archetypes.
     */
    std::list<meta_model::configuration_point>
    instantiate_archetype_template(const meta_model::feature_model& fm,
        const meta_model::configuration_point_template& cpt) const;

    /**
     * @brief Instantiates a configuration point template into a set
     * of configuration points.
     */
    std::list<meta_model::configuration_point>
    instantiate(const meta_model::feature_model& fm,
        const meta_model::configuration_point_template& cpt) const;
    std::list<meta_model::configuration_point>
    instantiate_new(
        const std::unordered_map<std::string, std::vector<std::string>>&
        template_instantiation_domains, const meta_model::feature_model& fm,
        const meta_model::configuration_point_template& cpt) const;

public:
    /**
     * @brief Instantiates the feature template across archetype
     * space.
     */
    std::list<meta_model::feature> instantiate(
        const std::unordered_map<std::string, std::vector<std::string>>&
        template_instantiation_domains,
        const meta_model::feature_template& ft) const;

    /**
     * @brief Instantiates a profile template across archetype space.
     */
    meta_model::profile instantiate(const meta_model::feature_model& fm,
        const meta_model::profile_template& pt) const;
    meta_model::profile instantiate_new(
        const std::unordered_map<std::string, std::vector<std::string>>&
        template_instantiation_domains, const meta_model::feature_model& fm,
        const meta_model::profile_template& pt) const;

private:
    const archetypes::location_repository& repository_;
    const bool compatibility_mode_;
};

}

#endif
