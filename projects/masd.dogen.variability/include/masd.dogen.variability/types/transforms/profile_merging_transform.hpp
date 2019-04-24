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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_TRANSFORMS_PROFILE_MERGING_TRANSFORM_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_TRANSFORMS_PROFILE_MERGING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.variability/types/meta_model/profile.hpp"
#include "masd.dogen.variability/types/meta_model/profile_repository.hpp"
#include "masd.dogen.variability/types/transforms/context.hpp"

namespace masd::dogen::variability::transforms {

/**
 * @brief Merges profiles according to their inheritance
 * relationships.
 */
class profile_merging_transform final {
private:
    /**
     * @brief Recurses up the profile tree and merges children with
     * their parents.
     */
    const meta_model::profile& walk_up_parent_tree_and_merge(
        const std::string& current,
        std::unordered_map<std::string, meta_model::profile>& pm) const;

private:
    /**
     * @brief Organises profiles into a map, by qualified name.
     */
    std::unordered_map<std::string, meta_model::profile>
    create_profile_map(const std::list<meta_model::profile>& profiles) const;

    /**
     * @brief Performs a number of sanity checks on a profile.
     */
    void validate(
        const std::unordered_map<std::string, meta_model::profile>& pm) const;

    /**
     * @brief Merges all profiles.
     */
    void merge(std::unordered_map<std::string, meta_model::profile>& pm) const;

    /**
     * @brief Generates a profile repository.
     */
    meta_model::profile_repository create_repository(
        const std::unordered_map<std::string, meta_model::profile>& pm);

public:
    meta_model::profile_repository apply(const context& ctx,
        const std::list<meta_model::profile>& profiles);
};

}

#endif
