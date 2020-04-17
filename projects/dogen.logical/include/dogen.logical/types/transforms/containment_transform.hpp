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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_CONTAINMENT_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_CONTAINMENT_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/transforms/context.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Update element containment relationships.
 *
 * Model elements which can contain other model elements have a
 * property called @e contains. This transform looks at the names of
 * each element, and infers what its expected container should be. It
 * then locates the container, and updates its @e contains
 * property. There are several types of objects capable of
 * containment, so the transform takes that into account. However, at
 * present we do not have a way to check if a container can contain
 * objects of a given type.
 */
class containment_transform final {
public:
    /**
     * @brief Execute the transform against the supplied model.
     */
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
