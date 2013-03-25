/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_CPP_TYPES_ASPECT_TYPES_HPP
#define DOGEN_CPP_TYPES_ASPECT_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace cpp {

/**
 * @brief An aspect in a facet.
 *
 * Facets represent different ways of looking at domain objects.
 * However, not everything in a facet is related to the domain type;
 * some plumbing is required in order to fully implement a facet. This
 * enum allows us to distinguish between the different types of @e
 * components a facet has, which we choose to call @e aspects.
 */
enum class aspect_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    main = 1, ///< The representation of the domain type for this facet
    includers = 2, ///< Header file with includes for all headers in facet
    forward_decls = 3, ///< Forward declarations for type
    registrar = 4, ///< Boost serialisation registration
    null_aspect = 5 ///< Nothing is to be produced for this type
};

} }

#endif
