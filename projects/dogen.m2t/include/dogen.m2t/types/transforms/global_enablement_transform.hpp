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
#ifndef DOGEN_M2T_TYPES_TRANSFORMS_GLOBAL_ENABLEMENT_TRANSFORM_HPP
#define DOGEN_M2T_TYPES_TRANSFORMS_GLOBAL_ENABLEMENT_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/optional.hpp>
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.physical/types/entities/name_repository.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.m2t/types/entities/element_archetype.hpp"
#include "dogen.m2t/types/entities/backend_properties.hpp"
#include "dogen.m2t/types/entities/facet_properties.hpp"
#include "dogen.m2t/types/entities/archetype_properties.hpp"
#include "dogen.m2t/types/transforms/context.hpp"
#include "dogen.m2t/types/entities/model.hpp"


namespace dogen::m2t::transforms {

class global_enablement_transform final {
private:
    struct backend_feature_group {
        variability::entities::feature enabled;
    };

    struct facet_feature_group {
        variability::entities::feature enabled;
        variability::entities::feature overwrite;
    };

    struct global_archetype_feature_group {
        variability::entities::feature enabled;
        variability::entities::feature overwrite;
    };

    struct local_archetype_feature_group {
        variability::entities::feature facet_enabled;
        variability::entities::feature archetype_enabled;
        variability::entities::feature facet_overwrite;
        variability::entities::feature archetype_overwrite;
    };

private:
    static std::unordered_map<std::string, backend_feature_group>
    make_backend_feature_group(const variability::entities::feature_model& fm,
        const physical::entities::name_repository& alrp);

    static std::unordered_map<std::string, facet_feature_group>
    make_facet_feature_group(const variability::entities::feature_model& fm,
        const physical::entities::name_repository& alrp);

    static std::unordered_map<std::string, global_archetype_feature_group>
    make_global_archetype_feature_group(
        const variability::entities::feature_model& fm,
        const physical::entities::name_repository& alrp);

    static std::unordered_map<std::string, local_archetype_feature_group>
    make_local_archetype_feature_group(
        const variability::entities::feature_model& fm,
        const physical::entities::name_repository& alrp);

private:
    static std::unordered_map<std::string, entities::backend_properties>
    obtain_backend_properties(
        const std::unordered_map<std::string, backend_feature_group>& fgs,
        const variability::entities::configuration& cfg);

    static std::unordered_map<std::string, entities::facet_properties>
    obtain_facet_properties(
        const std::unordered_map<std::string, facet_feature_group>& fgs,
        const variability::entities::configuration& cfg);

    static std::unordered_map<std::string, entities::archetype_properties>
    obtain_archetype_properties(
        const std::unordered_map<std::string,
        global_archetype_feature_group>& fgs,
        const variability::entities::configuration& cfg);

    static void populate_global_archetype_location_properties(
        const variability::entities::feature_model& fm,
        const physical::entities::name_repository& alrp,
        entities::model& m);

    static std::unordered_map<
        std::string,
        logical::entities::enablement_properties>
    obtain_local_archetype_location_properties(
        const std::unordered_map<std::string,
        local_archetype_feature_group>& fgs,
        const std::list<physical::entities::location>& als,
        const variability::entities::configuration& cfg);

    static void populate_local_archetype_location_properties(
        const variability::entities::feature_model& fm,
        const physical::entities::name_repository& alrp,
        entities::model& m);

public:
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
