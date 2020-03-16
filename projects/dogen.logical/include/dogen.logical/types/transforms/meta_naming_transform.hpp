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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_META_NAMING_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_META_NAMING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.logical/types/meta_model/model_fwd.hpp"
#include "dogen.logical/types/transforms/context.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Updates the meta-names of all of the assets meta-model
 * elements.
 */
class meta_naming_transform final {
public:
    /**
     * @brief Performs the transform on the model.
     *
     * Note that any injected meta-model elements are not updated as
     * part of this transform; these are expected to be handled
     * internally as they are generated. We only concern ourselves
     * with well-known meta-model elements from assets.
     */
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
