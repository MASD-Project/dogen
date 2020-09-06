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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_MODULES_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_MODULES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/transforms/context.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Generates all of the modules implied by the defined types.
 */
class modules_transform final {
private:
    /**
     * @brief Gathers all internal modules referred to by model
     * elements.
     */
    static std::unordered_map<std::string, std::list<std::string>>
    gather_internal_modules(entities::model& m);

    /**
     * @brief Returns true if there is a containing element in the
     * model, across all containers, for this ID.
     */
    static bool containing_element_exists(
        const identification::entities::logical_id& id,
        const entities::model& m);

    /**
     * @brief Creates modules for the internal modules which are not
     * yet in model.
     */
    static void create_modules(
        const std::unordered_map<std::string, std::list<std::string>>&
        internal_modules, entities::model& m);

public:
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
