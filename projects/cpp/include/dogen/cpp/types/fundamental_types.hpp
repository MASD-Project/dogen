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
#ifndef DOGEN_CPP_TYPES_FUNDAMENTAL_TYPES_HPP
#define DOGEN_CPP_TYPES_FUNDAMENTAL_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace cpp {

enum class fundamental_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    char_type = 1, ///< Object large enough to stora any member of the basic character set.
    unsigned_char_type = 2, ///< Like an char but with only natural numbers including zero.
    signed_char_type = 3, ///< Version of char with both positive and negative values.
    bool_type = 4, ///< Either true of false
    unsigned_int_type = 5, ///< Like an int but with only natural numbers including zero.
    int_type = 6, ///< Has the natural size suggested by the hardware architecture.
    unsinged_short_int_type = 7, ///< Like an short int but with only natural numbers including zero.
    short_int_type = 8, ///< Type of an integer which can (but needn't) be smaller than an int.
    unsigned_long_int_type = 9, ///< Like an long int but with only natural numbers including zero.
    long_int_type = 10, ///< Type of an integer which can (but needn't) be bigger than an int.
    wchar_t_type = 11, ///< Object large enough to store any member of the extended character set.
    float_type = 12, ///< Basic floating point type.
    double_type = 13, ///< Floating point type which must have at least as much precision as float.
    long_double_type = 14, ///< Floating point type which must have at least as much precision as double.
    void_type = 15, ///< Has an empty set of values. Incomplete type that cannot be completed.
    non_iso_type = 16 ///< Type is not part of the C++ ISO standard.
};

} }

#endif
