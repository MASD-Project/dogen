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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_VARIABILITY_PROFILES_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_VARIABILITY_PROFILES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.logical/types/features/variability_entry.hpp"
#include "dogen.logical/types/features/variability_profile.hpp"
#include "dogen.logical/types/entities/model_set.hpp"
#include "dogen.logical/types/transforms/context_fwd.hpp"
#include "dogen.logical/types/entities/variability/abstract_profile.hpp"
#include "dogen.logical/types/entities/variability/abstract_profile_entry.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Updates the meta-elements in the logical model that are
 * model variability profiles and profile templates.
 */
class variability_profiles_transform final {
private:
    /**
     * @brief Computes the key for a profile entry.
     */
    static std::string compute_key(const std::string& key_prefix,
        const std::string& original_key);

private:
    /**
     * @brief Reads configuration related to profiles.
     */
    static void update(const features::variability_profile::feature_group& fg,
        entities::variability::abstract_profile& ap);

    /**
     * @brief Reads configuration related to profile entries.
     */
    static void update(const features::variability_entry::feature_group& fg,
        entities::variability::abstract_profile_entry& ape);

private:
    /**
     * @brief Processes all profile templates in model.
     */
    static void process_profile_templates(
        const variability::entities::feature_model& fm, entities::model& m);

    /**
     * @brief Processes all profiles in model.
     */
    static void process_profiles(
        const variability::entities::feature_model& fm, entities::model& m);

public:
    /**
     * @brief Applies the transform to the entire model set.
     */
    static void apply(const context& ctx, entities::model_set& ms);
};

}

#endif
