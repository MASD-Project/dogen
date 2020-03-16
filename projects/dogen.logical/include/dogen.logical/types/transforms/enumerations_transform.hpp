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
#include "dogen.logical/types/meta_model/technical_space.hpp"
#include "dogen.logical/types/meta_model/structural/enumeration.hpp"
#include "dogen.logical/types/meta_model/model.hpp"
#include "dogen.logical/types/transforms/context_fwd.hpp"

namespace dogen::logical::transforms {

/**
 * @brief Expands all enumerations in model.
 */
class enumerations_transform final {
private:
    static meta_model::name obtain_enumeration_default_underlying_element_name(
        const meta_model::model& m);
    static std::string obtain_invalid_enumerator_simple_name(
        const meta_model::technical_space ts);
    static meta_model::structural::enumerator make_invalid_enumerator(
        const meta_model::name& n, const meta_model::technical_space ts);

public:
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
