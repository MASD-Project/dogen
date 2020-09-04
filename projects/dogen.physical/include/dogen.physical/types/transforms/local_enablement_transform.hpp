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
#ifndef DOGEN_PHYSICAL_TYPES_TRANSFORMS_LOCAL_ENABLEMENT_TRANSFORM_HPP
#define DOGEN_PHYSICAL_TYPES_TRANSFORMS_LOCAL_ENABLEMENT_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen.identification/types/entities/archetype_name_set.hpp"
#include "dogen.identification/types/entities/logical_meta_physical_id.hpp"
#include "dogen.physical/types/entities/artefact_properties.hpp"
#include "dogen.physical/types/entities/enablement_properties.hpp"
#include "dogen.physical/types/entities/denormalised_archetype_properties.hpp"
#include "dogen.physical/types/entities/artefact_set.hpp"
#include "dogen.physical/types/entities/artefact_repository.hpp"
#include "dogen.physical/types/transforms/context.hpp"

namespace dogen::physical::transforms {

class local_enablement_transform final {
private:
    static void compute_enablement_for_artefact_properties(
        const entities::denormalised_archetype_properties&
        global_enablement_properties,
        const entities::enablement_properties&
        local_enablement_properties,
        const identification::entities::physical_meta_id& archetype,
        entities::artefact_properties& ap);

    static void compute_enablement_for_artefact_set(
        const std::unordered_map<identification::entities::logical_meta_id,
        identification::entities::archetype_name_set>&
        physical_names_by_meta_name,
        const std::unordered_map<identification::entities::physical_meta_id,
        entities::denormalised_archetype_properties>&
        global_enablement_properties,
        std::unordered_set<identification::entities::logical_meta_physical_id>&
        enabled_archetype_for_element, entities::artefact_set& as);

public:
    static void apply(const context& ctx, entities::artefact_repository& arp);
};

}

#endif
