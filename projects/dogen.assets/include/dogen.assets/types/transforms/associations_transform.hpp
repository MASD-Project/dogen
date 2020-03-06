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
#ifndef DOGEN_ASSETS_TYPES_TRANSFORMS_ASSOCIATIONS_TRANSFORM_HPP
#define DOGEN_ASSETS_TYPES_TRANSFORMS_ASSOCIATIONS_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_set>
#include "dogen.assets/types/meta_model/name.hpp"
#include "dogen.assets/types/meta_model/model.hpp"
#include "dogen.assets/hash/meta_model/name_hash.hpp"
#include "dogen.assets/types/meta_model/structural/object.hpp"
#include "dogen.assets/types/meta_model/variability/feature_bundle.hpp"
#include "dogen.assets/types/meta_model/variability/feature_template_bundle.hpp"
#include "dogen.assets/types/transforms/context.hpp"

namespace dogen::assets::transforms {

/**
 * @brief Transform that specialises in indexing associations for
 * objects.
 *
 * @section assets_associations_transform_0 Requirements
 *
 * The transform of local attributes is expected to have taken place.
 *
 * @section assets_associations_transform_1 Indexing Process
 *
 * The transform goes through all attributes in objects and, for every
 * name tree, unpacks all the associations implied by their presence.
 *
 * Associations are of two types: @e regular or @e weak. This
 * distinction is required due to the usage of the association at code
 * generation time.
 *
 * A @e regular association means a full type definition is required
 * to be available due to the association. A @e weak association means
 * that the type is used via pointer and as such a forward declaration
 * may suffice.
 */
class associations_transform final {
private:
    /**
     * @brief Processes a specific object.
     */
    static void process_object(const meta_model::model& m,
        meta_model::structural::object& o);

    /**
     * @brief Processes a feature template bundle.
     */
    static void process_feature_template_bundle(const meta_model::model& m,
        meta_model::variability::feature_template_bundle& fb);

        /**
     * @brief Processes a feature bundle.
     */
    static void process_feature_bundle(const meta_model::model& m,
        meta_model::variability::feature_bundle& fb);

public:
    /**
     * @brief Transforms all association relationships on all objects.
     */
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
