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
#ifndef DOGEN_MODELING_TYPES_TRANSFORMS_CONTEXT_FACTORY_HPP
#define DOGEN_MODELING_TYPES_TRANSFORMS_CONTEXT_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.annotations/types/archetype_location_repository.hpp"
#include "dogen.modeling/types/transforms/options.hpp"
#include "dogen.modeling/types/transforms/model_to_text_model_transform_registrar.hpp"
#include "dogen.modeling/types/transforms/context.hpp"

namespace dogen::modeling::transforms {

/**
 * @brief Factory that creates transformation contexts.
 */
class context_factory final {
private:
    static std::unordered_map<std::string,
                              meta_model::intra_backend_segment_properties>
    create_intra_backend_segment_properties(
        const options& o,
        const model_to_text_model_transform_registrar& rg);

    static annotations::archetype_location_repository
    create_archetype_location_repository(
        const model_to_text_model_transform_registrar& rg);

public:
    static context
    make(const options& o, const bool enable_validation = true);
};

}

#endif
