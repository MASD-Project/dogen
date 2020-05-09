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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_ARCHETYPE_RENDERING_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_ARCHETYPE_RENDERING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.logical/types/entities/model.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.logical/types/entities/physical/archetype.hpp"
#include "dogen.logical/types/transforms/context_fwd.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Renders all templates in archetypes.
 */
class archetype_rendering_transform final {
private:
    /**
     * @brief Renders the wale template if any exists.
     */
    static std::string render_wale_template(
        const variability::entities::feature_model& fm,
        const entities::physical::archetype& arch);

    /**
     * @brief Render the stitch template, if any exists.
     */
    static std::string render_stitch_template(
        const variability::entities::feature_model& fm,
        const std::string& wale_template,
        const entities::physical::archetype& arch);

public:
    /**
     * Execute the transform against the model.
     */
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
