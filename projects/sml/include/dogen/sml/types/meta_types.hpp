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
#ifndef DOGEN_SML_TYPES_META_TYPES_HPP
#define DOGEN_SML_TYPES_META_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace sml {

/**
 * @brief Type of type.
 */
enum class meta_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    enumeration = 1, ///< Type is an enumeration
    primitive = 2, ///< Type is a primitive
    exception = 3, ///< Type is an exception
    module = 4, ///< Type is a module
    service = 5, ///< Type is a service
    entity = 6, ///< Type is an entity
    keyed_entity = 7, ///< Type is a keyed entity
    value_object = 8, ///< Type is a value object
    factory = 9, ///< Type is a factory
    repository = 10, ///< Type is a repository
    concept = 11 ///< Type is a concept
};

} }

#endif
