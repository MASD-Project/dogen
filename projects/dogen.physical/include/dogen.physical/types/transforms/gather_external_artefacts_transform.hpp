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
#ifndef DOGEN_PHYSICAL_TYPES_TRANSFORMS_GATHER_EXTERNAL_ARTEFACTS_TRANSFORM_HPP
#define DOGEN_PHYSICAL_TYPES_TRANSFORMS_GATHER_EXTERNAL_ARTEFACTS_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/shared_ptr.hpp>
#include "dogen.physical/types/transforms/context.hpp"
#include "dogen.physical/types/entities/operation_reason.hpp"
#include "dogen.physical/types/entities/operation_type.hpp"
#include "dogen.physical/types/entities/model.hpp"

namespace dogen::physical::transforms {

/**
 * @brief Handles any extraneous files which should be removed.
 */
class gather_external_artefacts_transform final {
private:
    /**
     * @brief Generates a new bare-bones artefact.
     *
     * Note that, at present we are not loading the contents of
     * extraneous artefacts.
     */
    static boost::shared_ptr<entities::artefact>
    make_artefact(const boost::filesystem::path& p,
        const entities::operation_type ot,
        const entities::operation_reason rsn);

public:
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
