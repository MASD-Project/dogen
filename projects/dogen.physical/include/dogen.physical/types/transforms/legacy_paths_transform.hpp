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
#ifndef DOGEN_PHYSICAL_TYPES_TRANSFORMS_LEGACY_PATHS_TRANSFORM_HPP
#define DOGEN_PHYSICAL_TYPES_TRANSFORMS_LEGACY_PATHS_TRANSFORM_HPP

#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include <libxml/tree.h>
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.physical/types/entities/model.hpp"
#include "dogen.physical/types/transforms/context.hpp"
#include "dogen.physical/types/entities/legacy_archetype_kind.hpp"

namespace dogen::physical::transforms {

/**
 * @brief Populates the include and full paths in artefacts.
 */
class legacy_paths_transform final {
private:
    static entities::legacy_archetype_kind
    get_archetye_kind(const std::string& archetype_name);

public:
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
