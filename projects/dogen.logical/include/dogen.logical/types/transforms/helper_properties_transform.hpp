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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_HELPER_PROPERTIES_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_HELPER_PROPERTIES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.logical/types/entities/streaming_properties.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Populates all of the helper properties from the PMM.
 */
class helper_properties_transform final {
private:
    static std::unordered_map<identification::entities::logical_id, std::string>
    make_configuration(const variability::entities::feature_model& fm,
        const entities::model& m);

private:
    std::unordered_map<std::string, std::unordered_set<std::string>>
    facets_for_family(const physical::entities::meta_model& pmm) const;

    void populate_helper_properties(const std::unordered_map<
        identification::entities::logical_id, std::string>& helper_families,
        const std::unordered_map<identification::entities::logical_id,
        logical::entities::streaming_properties>& streaming_properties,
        const physical::entities::meta_model& pmm, entities::model& m) const;

public:
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
