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
#ifndef MASD_DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_PROFILE_TEMPLATE_ADAPTION_TRANSFORM_HPP
#define MASD_DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_PROFILE_TEMPLATE_ADAPTION_TRANSFORM_HPP

#include "masd.dogen.coding/types/meta_model/variability_profile_template.hpp"
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include <boost/optional.hpp>
#include "masd.dogen.variability/types/meta_model/feature.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model.hpp"
#include "masd.dogen.variability/types/meta_model/profile_template.hpp"
#include "masd.dogen.coding/types/meta_model/model_set.hpp"
#include "masd.dogen.orchestration/types/transforms/context_fwd.hpp"

namespace masd::dogen::orchestration::transforms {

class profile_template_adaption_transform final {
private:
    struct feature_group {
        variability::meta_model::feature binding_point;
        variability::meta_model::feature labels;
        variability::meta_model::feature archetype_location_kernel;
        variability::meta_model::feature archetype_location_backend;
        variability::meta_model::feature archetype_location_facet;
        variability::meta_model::feature archetype_location_archetype;
        variability::meta_model::feature template_kind;
        variability::meta_model::feature untyped_value;
    };

    static feature_group make_feature_group(
        const variability::meta_model::feature_model& fm);

    static variability::meta_model::binding_point
    make_binding_point(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static std::unordered_set<std::string>
    make_labels(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static std::string
    make_archetype_location_kernel(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static std::string
    archetype_location_backend(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static std::string
    archetype_location_facet(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static std::string
    archetype_location_archetype(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static variability::meta_model::template_kind
    make_template_kind(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

    static std::list<std::string>
    make_untyped_value(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

private:
    static variability::meta_model::profile_template
    adapt(const feature_group& fg,
        const coding::meta_model::variability_profile_template& vpt);

public:
    static std::list<variability::meta_model::profile_template>
    apply(const context& ctx, const coding::meta_model::model_set& ms);
};

}

#endif
