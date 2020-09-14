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
#ifndef DOGEN_PHYSICAL_TYPES_TRANSFORMS_META_MODEL_PROPERTIES_TRANSFORM_HPP
#define DOGEN_PHYSICAL_TYPES_TRANSFORMS_META_MODEL_PROPERTIES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/optional.hpp>
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.identification/types/entities/physical_meta_name_indices.hpp"
#include "dogen.physical/types/entities/backend_properties.hpp"
#include "dogen.physical/types/entities/facet_properties.hpp"
#include "dogen.physical/types/entities/archetype_properties.hpp"
#include "dogen.physical/types/entities/artefact_repository.hpp"
#include "dogen.physical/types/entities/enablement_properties.hpp"
#include "dogen.physical/types/transforms/context.hpp"

namespace dogen::physical::transforms {

/**
 * @brief Populates the meta-model properties.
 */
class meta_model_properties_transform final {
private:
    /**
     * @brief Features associated with a backend.
     */
    struct backend_feature_group {
        variability::entities::feature enabled;
    };

    /**
     * @brief Features associated with a facet.
     */
    struct facet_feature_group {
        variability::entities::feature enabled;
        variability::entities::feature overwrite;
    };

    /**
     * @brief Features associated with an archetype.
     */
    struct archetype_feature_group {
        variability::entities::feature enabled;
        variability::entities::feature overwrite;
    };

private:
    /**
     * @brief Creates the feature group for the backend features.
     */
    static std::unordered_map<identification::entities::physical_meta_id,
                              backend_feature_group>
    make_backend_feature_group(const variability::entities::feature_model& fm,
        const identification::entities::physical_meta_name_indices& idx);

    /**
     * @brief Creates the feature group for the facet features.
     */
    static std::unordered_map<identification::entities::physical_meta_id,
                              facet_feature_group>
    make_facet_feature_group(const variability::entities::feature_model& fm,
        const identification::entities::physical_meta_name_indices& idx);

    /**
     * @brief Creates the feature group for the archetype features.
     */
    static std::unordered_map<identification::entities::physical_meta_id,
                              archetype_feature_group>
    make_archetype_feature_group(const variability::entities::feature_model& fm,
        const identification::entities::physical_meta_name_indices& idx);

private:
    /**
     * @brief Reads the backend configuration.
     */
    static std::unordered_map<identification::entities::physical_meta_id,
                              entities::backend_properties>
    obtain_backend_properties(const std::unordered_map<
        identification::entities::physical_meta_id, backend_feature_group>& fgs,
        const variability::entities::configuration& cfg);

    /**
     * @brief Reads the facet configuration.
     */
    static std::unordered_map<identification::entities::physical_meta_id,
                              entities::facet_properties>
    obtain_facet_properties(const std::unordered_map<
        identification::entities::physical_meta_id, facet_feature_group>& fgs,
        const variability::entities::configuration& cfg);

    /**
     * @brief Reads the archetype configuration.
     */
    static std::unordered_map<identification::entities::physical_meta_id,
                              entities::archetype_properties>
    obtain_archetype_properties(
        const std::unordered_map<identification::entities::physical_meta_id,
        archetype_feature_group>& fgs,
        const variability::entities::configuration& cfg);

    /**
     * @brief Reads the de-normalised archetype properties.
     */
    static std::unordered_map<identification::entities::physical_meta_id,
                       entities::denormalised_archetype_properties>
    obtain_denormalised_archetype_properties(
        const identification::entities::physical_meta_name_indices& idx,
        const entities::meta_model_properties& mmp);

public:
    static void apply(const context& ctx, entities::artefact_repository& arp);
};

}

#endif
