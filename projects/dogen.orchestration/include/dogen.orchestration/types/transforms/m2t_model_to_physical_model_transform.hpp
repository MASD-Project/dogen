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
#ifndef DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_M2T_MODEL_TO_PHYSICAL_MODEL_TRANSFORM_HPP
#define DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_M2T_MODEL_TO_PHYSICAL_MODEL_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.m2t/types/entities/model.hpp"
#include "dogen.m2t/types/transforms/context.hpp"
#include "dogen.physical/types/entities/model.hpp"

namespace dogen::orchestration::transforms {

/**
 * @brief Converts M2T models into physical models.
 */
class m2t_model_to_physical_model_transform final {
public:
    /**
     * @brief Applies the transform to the input model set.
     */
    static std::list<physical::entities::model>
    apply(const m2t::transforms::context& ctx,
        const std::list<m2t::entities::model>& ms);
};

}

#endif