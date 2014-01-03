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
#include "dogen/om/io/padding_types_io.hpp"

namespace dogen {
namespace om {

std::ostream& operator<<(std::ostream& s, const padding_types& v) {
    s << "{ " << "\"__type__\": " << "\"padding_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case padding_types::invalid:
        attr = "\"invalid\"";
        break;
    case padding_types::none:
        attr = "\"none\"";
        break;
    case padding_types::before:
        attr = "\"before\"";
        break;
    case padding_types::after:
        attr = "\"after\"";
        break;
    case padding_types::before_and_after:
        attr = "\"before_and_after\"";
        break;
    case padding_types::new_line:
        attr = "\"new_line\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for padding_types");
    }
    s << attr << " }";
    return s;
}

} }