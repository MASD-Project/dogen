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
#ifndef MASD_DOGEN_CODING_TYPES_TRANSFORMS_ENDOMODEL_PRE_PROCESSING_CHAIN_HPP
#define MASD_DOGEN_CODING_TYPES_TRANSFORMS_ENDOMODEL_PRE_PROCESSING_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <unordered_set>
#include "masd.dogen.coding/types/meta_model/languages.hpp"
#include "masd.dogen.coding/types/meta_model/endomodel.hpp"
#include "masd.dogen.coding/types/transforms/context_fwd.hpp"

namespace masd::dogen::coding::transforms {

class endomodel_pre_processing_chain final {
private:
    /**
     * @brief Returns true if the model language is in the relevant
     * languages set, false otherwise.
     */
    static bool is_language_relevant(
        const std::unordered_set<meta_model::languages>& relevant_languages,
        const meta_model::endomodel& em);

private:
    /**
     * @brief Applies the first part of the pre-processing transforms.
     */
    static void apply_first_set_of_transforms(
        const context& ctx, meta_model::endomodel& em);

    /**
     * @brief Applies the second part of the pre-processing transforms.
     */
    static void apply_second_set_of_transforms(
        const context& ctx, meta_model::endomodel& em);

public:
    /**
     * @brief Unconditionally applies all of the pre-processing
     * transforms to the supplied endomodel.
     */
    static void transform(const context& ctx,
        meta_model::endomodel& em);

    /**
     * @brief Only pre-processes the model if its language is in the
     * relevant languages set.
     *
     * Note: in order to determine this, we need to apply some of the
     * pre-processing transforms, so even when we return false, we
     * would have applied these. This is not ideal, but is ok for now
     * since we just drop the model when it has an irrelevent
     * language.
     */
    static bool try_transform(const context& ctx,
        const std::unordered_set<meta_model::languages>& relevant_languages,
        meta_model::endomodel& em);
};

}

#endif
