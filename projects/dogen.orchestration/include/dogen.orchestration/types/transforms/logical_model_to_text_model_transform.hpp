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
#ifndef DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_LOGICAL_MODEL_TO_TEXT_MODEL_TRANSFORM_HPP
#define DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_LOGICAL_MODEL_TO_TEXT_MODEL_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/entities/output_model_set.hpp"
#include "dogen.text/types/entities/model_set.hpp"
#include "dogen.text/types/transforms/context.hpp"

namespace dogen::orchestration::transforms {

/**
 * @brief Transforms a logical model representation into a text
 * representation, performing an expansion into physical space.
 */
class logical_model_to_text_model_transform final {
private:
    /**
     * @brief Transform a logical model into its text counterpart.
     */
    static text::entities::model
    apply(const text::transforms::context& ctx,
        const logical::entities::model& lm);

public:
    /**
     * @brief Transform logical models into its text counterparts.
     */
    static text::entities::model_set apply(const text::transforms::context& ctx,
        const logical::entities::output_model_set& loms);
};

}

#endif
