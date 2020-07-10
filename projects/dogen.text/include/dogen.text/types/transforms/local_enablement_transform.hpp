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
#ifndef DOGEN_TEXT_TYPES_TRANSFORMS_LOCAL_ENABLEMENT_TRANSFORM_HPP
#define DOGEN_TEXT_TYPES_TRANSFORMS_LOCAL_ENABLEMENT_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen.physical/types/entities/archetype_name_set.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.text/types/entities/element_archetype.hpp"
#include "dogen.logical/types/entities/artefact_properties.hpp"
#include "dogen.logical/types/entities/enablement_properties.hpp"
#include "dogen.text/types/entities/denormalised_archetype_properties.hpp"
#include "dogen.text/types/transforms/context.hpp"
#include "dogen.text/types/entities/model.hpp"

namespace dogen::text::transforms {

class local_enablement_transform final {
private:
    static bool is_element_disabled(
        const logical::entities::element& e);

    static void compute_enablement_for_artefact_properties(
        const std::unordered_map<std::string,
        entities::denormalised_archetype_properties>&
        global_enablement_properties,
        const std::unordered_map<std::string,
        logical::entities::enablement_properties>&
        local_enablement_properties,
        const std::string& archetype,
        logical::entities::artefact_properties& ap);

    static void compute_enablement_for_element(
        const std::unordered_map<std::string,
        physical::entities::archetype_name_set>&
        physical_names_by_meta_name,
        const std::unordered_map<std::string,
        entities::denormalised_archetype_properties>&
        global_enablement_properties,
        std::unordered_set<entities::element_archetype>&
        enabled_archetype_for_element, logical::entities::element& e);

public:
    static void apply(const context& ctx, entities::model& m);
};

}

#endif
