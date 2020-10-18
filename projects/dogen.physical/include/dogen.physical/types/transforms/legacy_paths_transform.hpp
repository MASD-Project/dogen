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

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include "dogen.variability/types/entities/feature.hpp"
#include "dogen.variability/types/entities/configuration.hpp"
#include "dogen.variability/types/entities/feature_model.hpp"
#include "dogen.identification/types/entities/logical_name.hpp"
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.identification/types/entities/physical_meta_name.hpp"
#include "dogen.physical/types/entities/model.hpp"
#include "dogen.physical/types/transforms/context.hpp"
#include "dogen.physical/types/entities/legacy_archetype_kind.hpp"

namespace dogen::physical::transforms {

class locator;

/**
 * @brief Populates the include and full paths in artefacts.
 */
class legacy_paths_transform final {
private:

private:
    /**
     * @brief Returns the enumeration for the given archetype.
     */
    static entities::legacy_archetype_kind
    get_archetye_kind(const std::string& archetype_name, const bool is_tests);

    /**
     * @brief Returns the full path for a given archetype.
     */
    static boost::filesystem::path get_full_path_for_archetype(
        const identification::entities::logical_name& ln,
        const identification::entities::physical_meta_name& pmn,
        const locator& l);

    /**
     * @brief Computes the inclusion path for an archetype.
     */
    static boost::filesystem::path get_relative_path_for_archetype(
        const identification::entities::logical_name& ln,
        const identification::entities::physical_meta_name& pmn,
        const locator& l);

public:
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
