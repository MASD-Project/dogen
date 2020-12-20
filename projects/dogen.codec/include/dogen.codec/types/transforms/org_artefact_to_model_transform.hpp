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
#ifndef DOGEN_CODEC_TYPES_TRANSFORMS_ORG_ARTEFACT_TO_MODEL_TRANSFORM_HPP
#define DOGEN_CODEC_TYPES_TRANSFORMS_ORG_ARTEFACT_TO_MODEL_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.codec/types/entities/model.hpp"
#include "dogen.codec/types/entities/artefact.hpp"
#include "dogen.codec/types/transforms/context.hpp"

namespace dogen::codec::transforms {

/**
 * @brief Processes the artefact as if encoded as an org-mode
 * document, and converts it into an instance of the codec model.
 */
class org_artefact_to_model_transform final {
public:
    static entities::model
    apply(const transforms::context& ctx, const entities::artefact& a);
};

}

#endif
