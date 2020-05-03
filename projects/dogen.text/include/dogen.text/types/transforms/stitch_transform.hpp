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
#ifndef DOGEN_TEXT_TYPES_TRANSFORMS_STITCH_TRANSFORM_HPP
#define DOGEN_TEXT_TYPES_TRANSFORMS_STITCH_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen.text/types/transforms/text_to_text_transform.hpp"

namespace dogen::text::transforms {

/**
 * @brief Transforms artefacts that contain stitch templates into the
 * expanded output of the template.
 */
class stitch_transform final : public text_to_text_transform {
public:
    std::string id() const override;
    std::string description() const override;
    void apply(const context& ctx, const logical::entities::element& e,
        const boost::shared_ptr<physical::entities::artefact> input,
        std::list<boost::shared_ptr<physical::entities::artefact>>& outputs)
        const override;
};

}

#endif
