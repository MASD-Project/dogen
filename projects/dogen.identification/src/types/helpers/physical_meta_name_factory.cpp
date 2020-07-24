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
#include "dogen.identification/types/helpers/physical_meta_name_builder.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"

namespace dogen::identification::helpers {

entities::physical_meta_name
physical_meta_name_factory::make(const std::string& backend,
    const std::string& facet, const std::string& archetype) {
    physical_meta_name_builder b;
    b.backend(backend);
    b.facet(facet);
    b.archetype(archetype);
    return b.build();
}

}
