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
#include "dogen/om/io/cpp_memory_types_io.hpp"

namespace dogen {
namespace om {

std::ostream& operator<<(std::ostream& s, const cpp_memory_types& v) {
    s << "{ " << "\"__type__\": " << "\"cpp_memory_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case cpp_memory_types::invalid:
        attr = "\"invalid\"";
        break;
    case cpp_memory_types::stack:
        attr = "\"stack\"";
        break;
    case cpp_memory_types::pointer:
        attr = "\"pointer\"";
        break;
    case cpp_memory_types::reference:
        attr = "\"reference\"";
        break;
    case cpp_memory_types::move_reference:
        attr = "\"move_reference\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for cpp_memory_types");
    }
    s << attr << " }";
    return s;
}

} }