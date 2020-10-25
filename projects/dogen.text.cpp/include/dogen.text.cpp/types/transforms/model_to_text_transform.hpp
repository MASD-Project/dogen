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
#ifndef DOGEN_TEXT_CPP_TYPES_TRANSFORMS_MODEL_TO_TEXT_TRANSFORM_HPP
#define DOGEN_TEXT_CPP_TYPES_TRANSFORMS_MODEL_TO_TEXT_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include "dogen.identification/types/entities/logical_name.hpp"
#include "dogen.identification/types/entities/physical_meta_name.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.text/types/transforms/model_to_text_transform.hpp"
#include "dogen.text.cpp/types/formattables/locator.hpp"
#include "dogen.text.cpp/types/formattables/dependencies_builder_factory.hpp"
#include "dogen.text.cpp/types/transforms/inclusion_support_types.hpp"
#include "dogen.text.cpp/types/transforms/context.hpp"

namespace dogen::text::cpp::transforms {

class model_to_text_transform : public text::transforms::model_to_text_transform {
public:
    model_to_text_transform() = default;
    model_to_text_transform(model_to_text_transform&&) = default;
    model_to_text_transform(const model_to_text_transform&) = delete;
    virtual ~model_to_text_transform() noexcept = default;

public:
    /**
     * @brief Generate a physical representation of the logical
     * element.
     */
    virtual void apply(const context& ctx, const logical::entities::element& e,
        physical::entities::artefact& a) const = 0;
};

}

#endif
