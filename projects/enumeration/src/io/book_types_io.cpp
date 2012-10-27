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
#include <ostream>
#include <stdexcept>
#include "dogen/enumeration/io/book_types_io.hpp"

namespace dogen {
namespace enumeration {

std::ostream& operator<<(std::ostream& s, const book_types& v) {
    switch (v) {
    case book_types::great:
        return s << "book_types" << "::" << "great";
    case book_types::not_so_great:
        return s << "book_types" << "::" << "not_so_great";
    case book_types::bad:
        return s << "book_types" << "::" << "bad";
    default:
        throw std::invalid_argument("Invalid value for book_types");
    }
}

} }