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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_CLASS_TYPES_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_CLASS_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Possible types for a class.
 */
enum class class_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    user_defined = 1, ///< The class was created by the user
    unversioned_key = 2, ///< The class represents a system defined unversioned key
    versioned_key = 3, ///< The class represents a system defined versioned key
    service = 4
};

} } }

#endif
