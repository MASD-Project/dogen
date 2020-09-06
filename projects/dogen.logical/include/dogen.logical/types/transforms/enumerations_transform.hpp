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
#ifndef DOGEN_LOGICAL_TYPES_TRANSFORMS_ENUMERATIONS_TRANSFORM_HPP
#define DOGEN_LOGICAL_TYPES_TRANSFORMS_ENUMERATIONS_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <iosfwd>
#include "dogen.identification/types/entities/technical_space.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/transforms/context_fwd.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Expands all enumerations in model.
 */
class enumerations_transform final {
private:
    static identification::entities::logical_name obtain_enumeration_default_underlying_element_name(
        const entities::model& m);
    static std::string obtain_invalid_enumerator_simple_name(
        const identification::entities::technical_space ts);
    static entities::structural::enumerator
    make_invalid_enumerator(const identification::entities::logical_name& n,
        const identification::entities::technical_space ts);

public:
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
