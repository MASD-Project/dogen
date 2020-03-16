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
#ifndef DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_INJECTION_MODEL_TO_ASSETS_MODEL_TRANSFORM_HPP
#define DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_INJECTION_MODEL_TO_ASSETS_MODEL_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <vector>
#include <unordered_map>
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.injection/types/entities/model.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/location.hpp"
#include "dogen.logical/types/entities/attribute.hpp"
#include "dogen.logical/types/entities/model.hpp"
#include "dogen.orchestration/types/transforms/context_fwd.hpp"
#include "dogen.orchestration/types/helpers/adapter.hpp"

namespace dogen::orchestration::transforms {

/**
 * @brief Converts an injection model into an assets representation.
 */
class injection_model_to_assets_model_transform final {
private:
    static logical::entities::location
    create_location(const context& ctx, const injection::entities::model& m);

    static logical::entities::static_stereotypes compute_element_type(
        const std::list<logical::entities::static_stereotypes>& st,
        const std::string& fallback_element_type);

    static void process_element(const helpers::adapter& ad,
        const logical::entities::location& l,
        const injection::entities::element& ie,
        logical::entities::model& m);

public:
    static logical::entities::model
    apply(const context& ctx, const injection::entities::model& m);
};

}

#endif
