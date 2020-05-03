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
#ifndef DOGEN_TEXT_TYPES_TRANSFORMS_TEXT_TO_TEXT_TRANSFORM_HPP
#define DOGEN_TEXT_TYPES_TRANSFORMS_TEXT_TO_TEXT_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/shared_ptr.hpp>
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.logical/types/entities/element_fwd.hpp"
#include "dogen.text/types/transforms/context.hpp"

namespace dogen::text::transforms {

/**
 * @brief Transforms one artefact into one or more artefacts.
 */
class text_to_text_transform {
public:
    text_to_text_transform() = default;
    text_to_text_transform(const text_to_text_transform&) = delete;
    text_to_text_transform(text_to_text_transform&&) = default;
    virtual ~text_to_text_transform() noexcept = default;

public:
    /**
     * @brief Returns the identity of this transform.
     */
    virtual std::string id() const = 0;

    /**
     * @brief Returns a human readable description of this transform.
     */
    virtual std::string description() const = 0;

public:
    /**
     * @brief Executes the transform.
     */
    virtual void apply(const context& ctx, const logical::entities::element& e,
        const boost::shared_ptr<physical::entities::artefact> input, std::list<
        boost::shared_ptr<physical::entities::artefact>>& outputs) const = 0;
};

}

#endif
