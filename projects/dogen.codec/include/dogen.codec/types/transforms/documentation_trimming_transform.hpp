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
#ifndef DOGEN_CODEC_TYPES_TRANSFORMS_DOCUMENTATION_TRIMMING_TRANSFORM_HPP
#define DOGEN_CODEC_TYPES_TRANSFORMS_DOCUMENTATION_TRIMMING_TRANSFORM_HPP

#include "dogen.codec/types/entities/comment.hpp"
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <sstream>
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.codec/types/entities/model.hpp"
#include "dogen.codec/types/entities/element.hpp"
#include "dogen.codec/types/entities/attribute.hpp"
#include "dogen.codec/types/features/meta_data.hpp"
#include "dogen.codec/types/transforms/context_fwd.hpp"

namespace dogen::codec::transforms {

/**
 * @brief Removes any leading and trailing whitespace from all the
 * documentation.
 */
class documentation_trimming_transform final {
private:
    /**
     * @brief Performs a left and right trim of the string.
     */
    static void trim(std::string& s);

    /**
     * @brief Trims the comment.
     */
    static void trim(entities::comment& c,
        const bool add_trailing_new_line = false);

    /**
     * @brief Returns true if the element has a stereotype of
     * generation marker.
     */
    static bool is_generation_marker(const entities::element& e);

    /**
     * @brief Process the supplied element.
     */
    static void process_element(entities::element& e);

public:
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
