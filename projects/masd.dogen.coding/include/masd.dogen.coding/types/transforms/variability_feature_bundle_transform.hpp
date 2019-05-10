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
#ifndef MASD_DOGEN_CODING_TYPES_TRANSFORMS_VARIABILITY_FEATURE_TEMPLATE_GROUP_TRANSFORM_HPP
#define MASD_DOGEN_CODING_TYPES_TRANSFORMS_VARIABILITY_FEATURE_TEMPLATE_GROUP_TRANSFORM_HPP

#include "masd.dogen.coding/types/meta_model/variability/feature_bundle.hpp"
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.variability/types/meta_model/feature.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model.hpp"
#include "masd.dogen.variability/types/meta_model/template_kind.hpp"
#include "masd.dogen.coding/types/meta_model/model.hpp"
#include "masd.dogen.coding/types/transforms/context_fwd.hpp"

namespace masd::dogen::coding::transforms {

class variability_feature_bundle_transform final {
private:
    struct feature_group {
        variability::meta_model::feature binding_point;
        variability::meta_model::feature archetype_location_kernel;
        variability::meta_model::feature archetype_location_backend;
        variability::meta_model::feature archetype_location_facet;
        variability::meta_model::feature archetype_location_archetype;
        variability::meta_model::feature template_kind;
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

private:
    static void update(const feature_group& fg,
        meta_model::variability::feature_template& ft);

public:
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
