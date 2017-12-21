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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_CONTAINMENT_TRANSFORM_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_CONTAINMENT_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/shared_ptr.hpp>
#include "dogen.modeling/types/meta_model/module.hpp"
#include "dogen.modeling/types/meta_model/origin_types.hpp"
#include "dogen.modeling/types/meta_model/endomodel.hpp"
#include "dogen.modeling/types/transforms/context.hpp"

namespace dogen {
namespace modeling {
namespace transforms {

class containment_transform final {
private:
    /**
     * @brief Creates the module to represent the global namespace.
     */
    static boost::shared_ptr<meta_model::module>
    create_global_module(const meta_model::origin_types ot);

    /**
     * @brief Injects the global module, and makes all modules that do
     * not have a containing namespace be contained by it.
     */
    static void inject_global_module(meta_model::endomodel& im);

public:

    /**
     * @brief Updates the containment relationships in the model.
     *
     * @param m Yarn model to operate on.
     */
    static void transform(const context& ctx, meta_model::endomodel& im);
};

} } }

#endif
