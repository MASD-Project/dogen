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
#ifndef DOGEN_VARIABILITY_TYPES_TRANSFORMS_PROFILE_MERGING_TRANSFORM_HPP
#define DOGEN_VARIABILITY_TYPES_TRANSFORMS_PROFILE_MERGING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/profile.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.variability/types/entities/profile_repository.hpp"
#include "dogen.variability/types/transforms/context.hpp"

namespace dogen::variability::transforms {

/**
 * @brief Merges profiles according to their inheritance
 * relationships.
 *
 * This transform is really a mix of three separate transforms, but we
 * just can't figure out a good way of splitting them apart:
 *
 * - the recursive merging up the inheritance tree, which gives it its
 *   name.
 *
 * - the creation of a repository of profiles. This requires the data
 *   to be organised in a map, which is also needed for the previous
 *   step.
 *
 * - the population of the base layer profile name. This requires the
 *   data to be merged (because we want the field to populate from
 *   parent to children), but not yet in a repository (because we do
 *   not want to have to populate the copies of the profiles).
 *
 * So, to make our life easier for now we just bundled all of these
 * responsibilities into one big transform.
 */
class profile_merging_transform final {
private:
    struct feature_group {
        entities::feature profile;
    };

    static feature_group
    make_feature_group(const entities::feature_model& fm);

    static std::string obtain_profile_name(const feature_group& fg,
        const entities::configuration& cfg);

private:
    /**
     * @brief Recurses up the profile tree and merges children with
     * their parents.
     */
    static const entities::profile& walk_up_parent_tree_and_merge(
        const std::string& current,
        std::unordered_map<std::string, entities::profile>& pm);

private:
    /**
     * @brief Organises profiles into a map, by qualified name.
     */
    static std::unordered_map<std::string, entities::profile>
    create_profile_map(const std::list<entities::profile>& profiles);

    /**
     * @brief Performs a number of sanity checks on a profile.
     */
    static void validate(
        const std::unordered_map<std::string, entities::profile>& pm);

    /**
     * @brief Merges all profiles.
     */
    static void merge(std::unordered_map<std::string, entities::profile>& pm);

    /**
     * @brief Populates the base layer field.
     */
    static void populate_base_layer(
        const entities::feature_model& fm,
        std::unordered_map<std::string, entities::profile>& pm);

    /**
     * @brief Generates a profile repository.
     */
    static entities::profile_repository create_repository(
        const std::unordered_map<std::string, entities::profile>& pm);

public:
    static entities::profile_repository apply(const context& ctx,
        const entities::feature_model& fm,
        const std::list<entities::profile>& profiles);
};

}

#endif
