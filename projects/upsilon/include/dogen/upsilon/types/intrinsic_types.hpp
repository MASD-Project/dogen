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
#ifndef DOGEN_UPSILON_TYPES_INTRINSIC_TYPES_HPP
#define DOGEN_UPSILON_TYPES_INTRINSIC_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace upsilon {

enum class intrinsic_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    integer = 1,
    binary = 2,
    boolean = 3,
    date = 4,
    decimal = 5,
    double_x = 6,
    guid = 7,
    integer64 = 8,
    string_x = 9,
    utc_time = 10,
    utc_date_time = 11
};

} }

#endif
