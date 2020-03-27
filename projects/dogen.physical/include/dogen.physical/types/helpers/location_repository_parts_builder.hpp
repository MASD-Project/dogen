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
#ifndef DOGEN_LOGICAL_TYPES_HELPERS_LOCATION_REPOSITORY_PARTS_BUILDER_HPP
#define DOGEN_LOGICAL_TYPES_HELPERS_LOCATION_REPOSITORY_PARTS_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen.physical/types/entities/location.hpp"
#include "dogen.physical/types/entities/name_repository_parts.hpp"

namespace dogen::physical::helpers {

class location_repository_parts_builder final {
private:
    void validate(const std::string& meta_name, const std::string& family,
        const std::string& intra_backend_segment, const entities::location& al);

public:
    void add(const std::string& meta_name, const std::string& family,
        const std::string& intra_backend_segment,
        const std::string& canonical_archetype, const entities::location& al);
    entities::name_repository_parts build();

private:
    entities::name_repository_parts parts_;
};

}

#endif
