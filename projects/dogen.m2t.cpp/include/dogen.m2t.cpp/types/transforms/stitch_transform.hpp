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
#ifndef DOGEN_M2T_CPP_TYPES_TRANSFORMS_STITCH_TRANSFORM_HPP
#define DOGEN_M2T_CPP_TYPES_TRANSFORMS_STITCH_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.variability/types/helpers/configuration_factory.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.logical/types/entities/element_fwd.hpp"
#include "dogen.templating/types/stitch/instantiator.hpp"
#include "dogen.m2t.cpp/types/formattables/locator.hpp"
#include "dogen.m2t.cpp/types/formattables/artefact_properties.hpp"
#include "dogen.m2t.cpp/types/transforms/model_to_text_transform.hpp"

namespace dogen::m2t::cpp::transforms {

class stitch_transform final {
public:
    stitch_transform(const formattables::locator& l,
        const variability::entities::feature_model& fm,
        const variability::helpers::configuration_factory& cf);

private:
    bool is_header(const inclusion_support_types ist) const;

public:
    void apply(const model_to_text_transform& stock_transform,
        const context& ctx, const logical::entities::element& e,
        physical::entities::artefact& a) const;

private:
    const templating::stitch::instantiator instantiator_;
};

}

#endif
