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
#ifndef DOGEN_ASSETS_TYPES_TRANSFORMS_VARIABILITY_FEATURE_TEMPLATE_GROUP_TRANSFORM_HPP
#define DOGEN_ASSETS_TYPES_TRANSFORMS_VARIABILITY_FEATURE_TEMPLATE_GROUP_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen.variability/types/meta_model/feature.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.variability/types/meta_model/feature_model.hpp"
#include "dogen.variability/types/meta_model/template_kind.hpp"
#include "dogen.assets/types/meta_model/model.hpp"
#include "dogen.assets/types/transforms/context_fwd.hpp"
#include "dogen.assets/types/meta_model/variability/feature_bundle.hpp"

namespace dogen::assets::transforms {

class variability_feature_bundle_transform final {
private:
    struct feature_group {
        variability::meta_model::feature binding_point;
        variability::meta_model::feature archetype_location_kernel;
        variability::meta_model::feature archetype_location_backend;
        variability::meta_model::feature archetype_location_facet;
        variability::meta_model::feature archetype_location_archetype;
        variability::meta_model::feature template_kind;
        variability::meta_model::feature qualified_name;
    };

    static feature_group make_feature_group(
        const variability::meta_model::feature_model& fm);

    static variability::meta_model::binding_point
    make_binding_point(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static std::string
    make_archetype_location_kernel(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static std::string
    make_archetype_location_backend(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static std::string
    make_archetype_location_facet(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static std::string
    make_archetype_location_archetype(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static variability::meta_model::template_kind
    make_template_kind(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static std::string make_qualified_name(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

private:
    static void update(const feature_group& fg,
        meta_model::variability::feature_template& ft);

public:
    static void apply(const context& ctx,
        const std::unordered_map<std::string, std::string>& fixed_mappings,
        meta_model::model& m);
};

}

#endif
