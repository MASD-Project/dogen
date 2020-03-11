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
#ifndef DOGEN_ASSETS_TYPES_TRANSFORMS_VARIABILITY_PROFILES_CHAIN_HPP
#define DOGEN_ASSETS_TYPES_TRANSFORMS_VARIABILITY_PROFILES_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.variability/types/transforms/context_fwd.hpp"
#include "dogen.assets/types/features/variability_entry.hpp"
#include "dogen.assets/types/features/variability_profile.hpp"
#include "dogen.assets/types/meta_model/variability/abstract_profile.hpp"
#include "dogen.assets/types/meta_model/variability/abstract_profile_entry.hpp"
#include "dogen.assets/types/meta_model/model_set.hpp"
#include "dogen.assets/types/transforms/context_fwd.hpp"

namespace dogen::assets::transforms {

/**
 * @brief Handles the application of variability into the model set
 * currently being processed.
 *
 * The variability profiles chain has the responsibility of
 * initialising the "user-data" part of the variability
 * subsystem. This is the second phase of variability processing; it
 * presumes that the first phase was already performed - that is, the
 * injection of all of the available features into a feature model.
 *
 * Profiles provide "named configurations" defined by users that allow
 * for the packaging and sharing of configuration. The job of this
 * transform is to locate all of the meta-model types that provide
 * profile information (profiles and profile templates), convert them
 * into the corresponding variability counterparts and then execute
 * all of the required variability transforms.
 *
 */
class variability_profiles_chain final {
private:
    /**
     * @brief Reads configuration related to profiles.
     */
    static void update(const features::variability_profile::feature_group& fg,
        meta_model::variability::abstract_profile& ap);

    /**
     * @brief Reads configuration related to profile entries.
     */
    static void update(const features::variability_entry::feature_group& fg,
        meta_model::variability::abstract_profile_entry& ape);

private:
    /**
     * @brief Processes all profile templates in model.
     */
    static void process_profile_templates(
        const variability::meta_model::feature_model& fm, meta_model::model& m);

    /**
     * @brief Processes all profiles in model.
     */
    static void process_profiles(
        const variability::meta_model::feature_model& fm, meta_model::model& m);

    /**
     * @brief Processes all profile-like entities in the model set.
     */
    static void process_all_profiles(
        const variability::meta_model::feature_model& fm,
        meta_model::model_set& ms);

private:
    /**
     * @brief Converts the assets transform context into a variability
     * context.
     */
    static variability::transforms::context adapt(const context& ctx);

public:
    /**
     * @brief Applies the transform to the entire model set.
     */
    static void apply(const context& ctx, meta_model::model_set& ms);
};

}

#endif
