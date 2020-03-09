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
#include "dogen.assets/types/meta_model/model.hpp"
#include "dogen.assets/types/features/variability_templates.hpp"
#include "dogen.assets/types/features/variability_bundle.hpp"
#include "dogen.assets/types/transforms/context_fwd.hpp"
#include "dogen.assets/types/meta_model/variability/feature_bundle.hpp"
#include "dogen.assets/types/meta_model/variability/feature_template_bundle.hpp"

namespace dogen::assets::transforms {

class variability_entities_transform final {
private:
    static void update(const features::variability_templates::feature_group& fg,
        meta_model::variability::abstract_feature& ft);

    static void update(const features::variability_bundle::feature_group& fg,
        meta_model::variability::abstract_bundle& fb);

private:
    static void process_features(const context& ctx,
        const std::unordered_map<std::string, std::string>& fixed_mappings,
        meta_model::model& m);

    static void process_feature_templates(const context& ctx,
        const std::unordered_map<std::string, std::string>& fixed_mappings,
        meta_model::model& m);

    static void process_initialiser(meta_model::model& m);

public:
    static void apply(const context& ctx,
        const std::unordered_map<std::string, std::string>& fixed_mappings,
        meta_model::model& m);
};

}

#endif
