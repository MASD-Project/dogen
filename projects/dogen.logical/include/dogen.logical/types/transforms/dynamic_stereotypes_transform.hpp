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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_DYNAMIC_STEREOTYPES_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_DYNAMIC_STEREOTYPES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.logical/types/entities/input_model_set.hpp"
#include "dogen.logical/types/transforms/context_fwd.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Populates the dynamic stereotypes of the logical model.
 *
 * Users add a number of stereotypes to their models. Some refer to
 * meta-model elements (e.g. static stereotypes), and some refer to
 * elements which are part of the model. These can be either profiles
 * (part of the variability processing) or, mostly, object templates
 * (at least at present; we may extend these in the future). The
 * purpose of this transform is to look at the existing stereotypes
 * and remove all of those which have already been handled
 * (e.g. profiles), leaving us with the dynamic stereotypes that
 * require further processing.
 *
 * @pre variability profiles chain must have been executed.
 */
class dynamic_stereotypes_transform final {
public:
    static void apply(const logical::transforms::context& ctx,
        logical::entities::input_model_set& ms);
};

}

#endif
