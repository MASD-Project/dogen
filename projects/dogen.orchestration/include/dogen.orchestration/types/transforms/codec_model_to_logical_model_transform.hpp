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
#ifndef DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_CODEC_MODEL_TO_LOGICAL_MODEL_TRANSFORM_HPP
#define DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_CODEC_MODEL_TO_LOGICAL_MODEL_TRANSFORM_HPP

#include "dogen.codec/types/entities/element.hpp"
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <vector>
#include <unordered_map>
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.identification/types/entities/logical_location.hpp"
#include "dogen.codec/types/entities/model.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/attribute.hpp"
#include "dogen.logical/types/entities/stereotypes.hpp"
#include "dogen.orchestration/types/transforms/context_fwd.hpp"
#include "dogen.orchestration/types/helpers/codec_to_logical_projector.hpp"

namespace dogen::orchestration::transforms {

/**
 * @brief Converts an codec model into an logical representation.
 */
class codec_model_to_logical_model_transform final {
private:
    /**
     * @brief Obtains the set of stereotypes associated with this element.
     */
    static logical::entities::stereotypes
    obtain_stereotypes(const codec::entities::element& e);

    static identification::entities::logical_location
    create_location(const context& ctx, const codec::entities::model& m);

    static logical::entities::static_stereotypes compute_element_type(
        const std::list<logical::entities::static_stereotypes>& sts,
        const std::string& fallback_element_type);

    static void process_element(const helpers::codec_to_logical_projector& p,
        const identification::entities::logical_location& l,
        const codec::entities::element& ie,
        logical::entities::model& m);

public:
    static logical::entities::model
    apply(const context& ctx, const codec::entities::model& m);
};

}

#endif
