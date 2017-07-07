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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_PRE_PROCESSING_CHAIN_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_PRE_PROCESSING_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

class pre_processing_chain final {
private:
    /**
     * @brief Returns true if the languages are compatible, false
     * otherwise.
     */
    static bool are_languages_compatible(
        const languages target_language, intermediate_model& im);

private:
    /**
     * @brief Applies the first part of the pre-processing transforms.
     */
    static void apply_first_set_of_transforms(
        const context& ctx, intermediate_model& im);

    /**
     * @brief Applies the second part of the pre-processing transforms.
     */
    static void apply_second_set_of_transforms(
        const context& ctx, intermediate_model& im);

public:
    /**
     * @brief Unconditionally applies all of the pre-processing
     * transforms to the supplied intermediate model.
     */
    static void transform(const context& ctx, intermediate_model& im);

    /**
     * @brief Determines if the language of the supplied model is
     * compatible with the target language; if so, applies the
     * pre-processing transforms and returns true. Otherwise returns
     * false.
     */
    static bool try_transform(const context& ctx,
        const languages target_language, intermediate_model& im);

};

} } }

#endif
