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
#ifndef DOGEN_SML_TYPES_VALUE_OBJECT_TYPES_HPP
#define DOGEN_SML_TYPES_VALUE_OBJECT_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace sml {

/**
 * @brief Types of value objects.
 */
enum class value_object_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    plain = 1, ///< Regular value object with no distinguishing features.
    unversioned_key = 2, ///< Value is an unversioned key.
    versioned_key = 3, ///< Value is a versioned key.
    exception = 4, ///< Value represents an exception type.
    smart_pointer = 5, ///< Value is a smart pointer.
    associative_container = 6, ///< Type is an associative container.
    sequence_container = 7 ///< Type is a sequence container.
};

} }

#endif
