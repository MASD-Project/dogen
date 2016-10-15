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
#ifndef DOGEN_YARN_TYPES_OBJECT_TYPES_HPP
#define DOGEN_YARN_TYPES_OBJECT_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace yarn {

/**
 * @brief Types of objects.
 *
 * In the future, it will replace all other enumerations such as value_object_types,
 * etc.
 */
enum class object_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    smart_pointer = 1, ///< Value is a smart pointer.
    associative_container = 2, ///< Type is an associative container.
    sequence_container = 3 ///< Type is a sequence container.
};

} }

#endif
