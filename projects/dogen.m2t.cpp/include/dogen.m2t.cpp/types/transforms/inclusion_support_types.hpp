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
#ifndef DOGEN_M2T_CPP_TYPES_TRANSFORMS_INCLUSION_SUPPORT_TYPES_HPP
#define DOGEN_M2T_CPP_TYPES_TRANSFORMS_INCLUSION_SUPPORT_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen::m2t::cpp::transforms {

enum class inclusion_support_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    not_supported = 1, ///< This formatter does not export an inclusion directive.
    regular_support = 2, ///< This formatter exports a regular inclusion directive.
    canonical_support = 3 ///< This formatter exports a regular inclusion directive and is the default for its facet///< and element.
};

}

#endif
