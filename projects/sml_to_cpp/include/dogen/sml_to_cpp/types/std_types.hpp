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
#ifndef DOGEN_SML_TO_CPP_TYPES_STD_TYPES_HPP
#define DOGEN_SML_TO_CPP_TYPES_STD_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {
namespace sml_to_cpp {

/**
 * @brief Available types in the standard library
 */
enum class std_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    string = 1,
    int8_t = 2,
    int16_t = 3,
    int32_t = 4,
    int64_t = 5,
    uint8_t = 6,
    uint16_t = 7,
    uint32_t = 8,
    uint64_t = 9,
    array = 10,
    forward_list = 11,
    vector = 12,
    set = 13,
    multiset = 14,
    map = 15,
    multimap = 16,
    deque = 17,
    list = 18,
    unordered_map = 19,
    unordered_set = 20,
    algorithm = 21,
    ostream = 22,
    iosfwd = 23,
    sstream = 24,
    stdexcept = 25,
    functional = 26,
    pair = 27
};

} }

#endif
