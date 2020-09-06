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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_GLOBAL_MODULE_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_GLOBAL_MODULE_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/shared_ptr.hpp>
#include "dogen.identification/types/entities/model_type.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.logical/types/transforms/context.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Handles the creation of the global module and the updating
 * of containment of all module elements that belong to the global
 * module.
 */
class global_module_transform final {
private:
    /**
     * @brief Creates the module to represent the global namespace.
     */
    static boost::shared_ptr<entities::structural::module>
    create_global_module(const identification::entities::model_type mt);

    /**
     * @brief Injects the global module, and makes all modules that do
     * not have a containing namespace be contained by it.
     */
    static identification::entities::logical_name inject_global_module(entities::model& m);

    /**
     * @brief Updates the containment relationships in the model
     * related to the global module.
     */
    static void update_element_containment(
        const identification::entities::logical_name& global_module_name, entities::model& m);

public:
    /**
     * @brief Applies the transform.
     */
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
