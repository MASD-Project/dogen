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
#ifndef DOGEN_SML_TYPES_VALUE_TYPES_HPP
#define DOGEN_SML_TYPES_VALUE_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace sml {

enum class value_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    user_defined = 1, ///< Value was created by the user.
    unversioned_key = 2, ///< Value is an unversioned key.
    versioned_key = 3, ///< Value is a versioned key.
    enumeration = 4, ///< Value is an enumeration.
    exception = 5, ///< Value represents an exception type.
    string_table = 6, ///< Value is a list of strings.
    smart_pointer = 7, ///< Value is a smart pointer.
    associative_container = 8, ///< Type is an associative container.
    sequence_container = 9 ///< Type is a sequence container.
};

} }

#endif
