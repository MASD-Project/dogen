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
#ifndef DOGEN_TEXT_CPP_TYPES_TRANSFORMS_STITCH_TRANSFORM_HPP
#define DOGEN_TEXT_CPP_TYPES_TRANSFORMS_STITCH_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include "dogen.variability/types/helpers/configuration_factory.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.logical/types/entities/element_fwd.hpp"
#include "dogen.templating/types/stitch/instantiator.hpp"
#include "dogen.text.cpp/types/transforms/model_to_text_transform.hpp"

namespace dogen::text::cpp::transforms {

class stitch_transform final {
public:
    stitch_transform(const boost::filesystem::path& templates_directory,
        const variability::entities::feature_model& fm,
        const variability::helpers::configuration_factory& cf);

public:
    void apply(const model_to_text_transform& stock_transform,
        const logical::entities::element& e,
        physical::entities::artefact& a) const;

private:
    const templating::stitch::instantiator instantiator_;
};

}

#endif
