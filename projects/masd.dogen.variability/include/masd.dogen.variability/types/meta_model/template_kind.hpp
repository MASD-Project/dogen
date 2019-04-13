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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_META_MODEL_TEMPLATE_KIND_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_META_MODEL_TEMPLATE_KIND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace masd::dogen::variability::meta_model {

/**
 * @brief Determines the operations to perform when expanding the template.
 */
enum class template_kind : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    instance = 1, ///< Template is directly converted into an instance.
    recursive_template = 2, ///< The template is expanded recursively for every point in archetype space.
    backend_template = 3, ///< The template is expanded for every backend in archetype space.
    facet_template = 4, ///< The template is expanded for every facet in archetype space.
    archetype_template = 5 ///< The template is expanded for every archetype in archetype space.
};

}

#endif
