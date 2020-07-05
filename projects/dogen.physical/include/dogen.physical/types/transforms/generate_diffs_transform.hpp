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
#ifndef DOGEN_PHYSICAL_TYPES_TRANSFORMS_GENERATE_DIFFS_TRANSFORM_HPP
#define DOGEN_PHYSICAL_TYPES_TRANSFORMS_GENERATE_DIFFS_TRANSFORM_HPP

#include "dogen.physical/types/entities/artefact.hpp"
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.physical/types/transforms/context.hpp"
#include "dogen.physical/types/entities/model.hpp"

namespace dogen::physical::transforms {

/**
 * @brief Populates artefacts with a unified diff representation
 * between files in the filesystem and the generated content.
 */
class generate_diffs_transform final {
    static bool
    process_artefact(const boost::filesystem::path& managed_dir,
        physical::entities::artefact& a);

public:
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
