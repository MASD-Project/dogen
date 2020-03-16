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
#include "dogen.variability/types/meta_model/feature_model.hpp"
#include "dogen.logical/types/helpers/indices.hpp"
#include "dogen.logical/types/meta_model/name.hpp"
#include "dogen.logical/types/meta_model/model.hpp"
#include "dogen.logical/types/meta_model/structural/object.hpp"
#include "dogen.logical/types/transforms/context_fwd.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Expands generalisation relationships in model.
 */
class generalization_transform final {
private:
    static std::unordered_set<std::string>
    update_and_collect_parent_ids(const helpers::indices& idx,
        const variability::meta_model::feature_model& fm,
        meta_model::model& m);

    static void walk_up_generalization_tree(const meta_model::name& leaf,
        meta_model::model& m, meta_model::structural::object& o);

    static void populate_generalizable_properties(
        const std::unordered_set<std::string>& parent_ids,
        meta_model::model& m);

    static void sort_leaves(meta_model::model& m);

public:
    static void apply(const context& ctx, const helpers::indices& idx,
        meta_model::model& m);
};

}

#endif
