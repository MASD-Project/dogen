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
#ifndef DOGEN_TEXT_TYPES_TRANSFORMS_DECORATION_TRANSFORM_HPP
#define DOGEN_TEXT_TYPES_TRANSFORMS_DECORATION_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif


#include <list>
#include <string>
#include <boost/optional.hpp>
#include "dogen.logical/types/entities/name.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.logical/types/entities/decoration/element_properties.hpp"
#include "dogen.text/types/transforms/context.hpp"
#include "dogen.text/types/entities/model.hpp"

namespace dogen::text::transforms {

/**
 * @brief Updates the decoration of all modeling elements.
 */
class decoration_transform final {
private:
    /**
     * @brief Returns true if the meta-model element can be generated,
     * false otherwise.
     */
    static bool is_generatable(const logical::entities::name& meta_name);


public:
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
