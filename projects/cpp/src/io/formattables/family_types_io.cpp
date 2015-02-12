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
#include "dogen/cpp/io/formattables/family_types_io.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

std::ostream& operator<<(std::ostream& s, const family_types& v) {
    s << "{ " << "\"__type__\": " << "\"family_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case family_types::invalid:
        attr = "\"invalid\"";
        break;
    case family_types::character:
        attr = "\"character\"";
        break;
    case family_types::string:
        attr = "\"string\"";
        break;
    case family_types::boolean:
        attr = "\"boolean\"";
        break;
    case family_types::integer:
        attr = "\"integer\"";
        break;
    case family_types::floating_point:
        attr = "\"floating_point\"";
        break;
    case family_types::smart_pointer:
        attr = "\"smart_pointer\"";
        break;
    case family_types::ordered_container:
        attr = "\"ordered_container\"";
        break;
    case family_types::sequence_container:
        attr = "\"sequence_container\"";
        break;
    case family_types::hash_container:
        attr = "\"hash_container\"";
        break;
    case family_types::other:
        attr = "\"other\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for family_types");
    }
    s << attr << " }";
    return s;
}

} } }