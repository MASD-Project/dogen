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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_ANNOTATIONS_TRANSFORM_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_ANNOTATIONS_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/annotations/types/annotation_groups_factory.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

/**
 * @brief Reads raw meta-data and uses it to create the annotations
 * objects.
 */
class annotations_transform final {
private:
    static void update_scribble_groups(intermediate_model& im);
    static void update_annotations(
        const annotations::annotation_groups_factory& agf,
        intermediate_model& im);

public:
    static void transform(const context& ctx, intermediate_model& im);
};

} } }

#endif
