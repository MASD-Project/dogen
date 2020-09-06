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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_GENERALIZATION_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_GENERALIZATION_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_set>
#include <boost/optional.hpp>
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.identification/types/entities/logical_name.hpp"
#include "dogen.logical/types/helpers/indices.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/transforms/context_fwd.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Expands generalisation relationships in model.
 */
class generalization_transform final {
private:
    static std::unordered_set<identification::entities::logical_id>
    update_and_collect_parent_ids(const helpers::indices& idx,
        const variability::entities::feature_model& fm,
        entities::model& m);

    static void walk_up_generalization_tree(
        const identification::entities::logical_name& leaf,
        entities::model& m, entities::structural::object& o);

    static void populate_generalizable_properties(const std::unordered_set<
        identification::entities::logical_id>& parent_ids, entities::model& m);

    static void sort_leaves(entities::model& m);

public:
    static void apply(const context& ctx, const helpers::indices& idx,
        entities::model& m);
};

}

#endif
