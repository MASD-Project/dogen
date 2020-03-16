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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_MAPPING_ELEMENTS_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_MAPPING_ELEMENTS_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_map>
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.logical/types/entities/model_set.hpp"
#include "dogen.logical/types/entities/mapping/destination.hpp"
#include "dogen.logical/types/entities/variability/feature_template_bundle.hpp"
#include "dogen.logical/types/transforms/context_fwd.hpp"

namespace dogen::logical::transforms {

class mapping_elements_transform final {
private:
    static std::unordered_map<std::string,
                              std::list<
                                  logical::entities::mapping::destination>
                              >
    make_destinations(const variability::entities::feature_model& fm,
        const logical::entities::model_set& ms);

    static void populate_extensible_mappables(
        const std::unordered_map<std::string,
        std::list<logical::entities::mapping::destination>>&
        destinations_for_target, logical::entities::model_set& ms);

private:
    static void populate_fixed_mappables(
        const variability::entities::feature_model& fm,
        logical::entities::model_set& ms);

public:
    static void
    apply(const context& ctx, logical::entities::model_set& ms);
};

}

#endif
