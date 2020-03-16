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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_LOCATION_REPOSITORY_BUILDER_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_LOCATION_REPOSITORY_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen.physical/types/entities/location.hpp"
#include "dogen.physical/types/entities/locations_group.hpp"
#include "dogen.physical/types/entities/location_repository_parts.hpp"
#include "dogen.physical/types/entities/location_repository.hpp"

namespace dogen::physical::helpers {

class location_repository_builder final {
private:
    void validate(const std::list<entities::location>& als) const;
    void populate_locations(const std::list<entities::location>& als);
    void populate_archetypes_by_facet_by_backend();
    void populate_facet_names_by_backend_name();
    void populate_formatter_names_by_backend_name();

public:
    void add(const std::list<entities::location>& als);
    void add(const std::unordered_map<std::string, entities::locations_group>&
        locations_by_meta_name);
    void add(const std::unordered_map<std::string,
        std::list<entities::location>>& locations_by_family);

public:
    void add(const entities::location_repository_parts& parts);

public:
    const entities::location_repository& build();

private:
    entities::location_repository repository_;
};

}

#endif
