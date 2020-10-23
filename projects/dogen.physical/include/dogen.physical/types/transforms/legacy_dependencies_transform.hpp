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
#ifndef DOGEN_PHYSICAL_TYPES_TRANSFORMS_LEGACY_DEPENDENCIES_TRANSFORM_HPP
#define DOGEN_PHYSICAL_TYPES_TRANSFORMS_LEGACY_DEPENDENCIES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_map>
#include "dogen.identification/types/entities/logical_meta_physical_id.hpp"
#include "dogen.physical/types/entities/inclusion_directives.hpp"
#include "dogen.physical/types/entities/model.hpp"
#include "dogen.physical/types/transforms/context.hpp"

namespace dogen::physical::transforms {

/**
 * @brief Computes dependencies in the legacy format.
 */
class legacy_dependencies_transform final {
private:
    /**
     * @brief Finds all inclusion directives in the model, and indexes
     * them to logical-physical points.
     */
    static
    std::unordered_map<identification::entities::logical_meta_physical_id,
                       entities::inclusion_directives>
    get_inclusion_directives(const entities::model& m);

public:
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
