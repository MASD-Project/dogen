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
#ifndef DOGEN_ARCHETYPES_TYPES_LOCATION_REPOSITORY_BUILDER_HPP
#define DOGEN_ARCHETYPES_TYPES_LOCATION_REPOSITORY_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen.physical/types/location.hpp"
#include "dogen.physical/types/locations_group.hpp"
#include "dogen.physical/types/location_repository_parts.hpp"
#include "dogen.physical/types/location_repository.hpp"

namespace dogen::physical {

class location_repository_builder final {
private:
    void validate(const std::list<location>& als) const;
    void populate_locations(const std::list<location>& als);
    void populate_archetypes_by_facet_by_backend();
    void populate_facet_names_by_backend_name();
    void populate_formatter_names_by_backend_name();

public:
    void add(const std::list<location>& als);
    void add(const std::unordered_map<std::string, locations_group>&
        locations_by_meta_name);
    void add(const std::unordered_map<std::string,
        std::list<location>>& locations_by_family);

public:
    void add(const location_repository_parts& parts);

public:
    const location_repository& build();

private:
    location_repository repository_;
};

}

#endif
