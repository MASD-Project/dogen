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
#ifndef DOGEN_SML_TYPES_OBJECT_TYPES_HPP
#define DOGEN_SML_TYPES_OBJECT_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace sml {

/**
 * @brief Types of objects.
 *
 * In the future, it will replace all other enumerations such as value_object_types,
 * etc.
 */
enum class object_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    entity = 1, ///< Object is an entity.
    keyed_entity = 2, ///< Object is an entity with associated key or keys.
    factory = 3, ///< Type whose responsibility is to create other types.
    repository = 4, ///< Represents all objects of a certain type as a conceptual set.
    user_defined_service = 5, ///< The service has been defined by the user.
    visitor = 6, ///< The service is a system generated visitor.
    key_extractor = 7, ///< The service is a system defined key extractor.
    user_defined_value_object = 8, ///< Regular value object with no distinguishing features.
    unversioned_key = 9, ///< Value is an unversioned key.
    versioned_key = 10, ///< Value is an versioned key.
    exception = 11, ///< Value represents an exception type.
    smart_pointer = 12, ///< Value is a smart pointer.
    hash_container = 13, ///< Type is a hash-based container.
    sequence_container = 14, ///< Type is a sequence container.
    ordered_container = 15 ///< Type is a ordered container.
};

} }

#endif
