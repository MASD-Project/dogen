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
#ifndef DOGEN_CONFIG_TYPES_CPP_FACET_TYPES_HPP
#define DOGEN_CONFIG_TYPES_CPP_FACET_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace config {

/*
 * @brief Facets are different aspects of the domain objects we're
 * interested in.
 */
enum class cpp_facet_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    types = 1, ///< The definition of the domain type itself
    hash = 2, ///< Hashing for the domain type
    serialization = 3, ///< Serialisation for the domain type
    io = 4, ///< IO (streaming) for the domain type
    test_data = 5 ///< Test data generators for all domain types
};

} }

#endif
