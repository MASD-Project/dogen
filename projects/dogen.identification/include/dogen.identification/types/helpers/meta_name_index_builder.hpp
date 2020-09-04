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
#ifndef DOGEN_IDENTIFICATION_TYPES_HELPERS_META_NAME_INDEX_BUILDER_HPP
#define DOGEN_IDENTIFICATION_TYPES_HELPERS_META_NAME_INDEX_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen.identification/types/entities/logical_meta_id.hpp"
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.identification/types/entities/physical_meta_name.hpp"
#include "dogen.identification/types/entities/archetype_name_set.hpp"
#include "dogen.identification/types/entities/physical_meta_name_indices.hpp"

namespace dogen::identification::helpers {

class meta_name_index_builder final {
private:
    void validate(const std::list<entities::physical_meta_name>& mns) const;
    void populate_names(const std::list<entities::physical_meta_name>& mns);
    void populate_archetypes_by_facet_by_backend();
    void populate_facet_names_by_backend_name();

public:
    void add(const std::list<entities::physical_meta_name>& mns);
    void add(const std::unordered_map<entities::logical_meta_id,
        entities::archetype_name_set>& by_logical_meta_name);

public:
    const entities::physical_meta_name_indices& build();

private:
    entities::physical_meta_name_indices index_;
};

}

#endif
