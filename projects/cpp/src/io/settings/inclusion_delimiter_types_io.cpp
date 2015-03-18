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
#include "dogen/cpp/io/settings/inclusion_delimiter_types_io.hpp"

namespace dogen {
namespace cpp {
namespace settings {

std::ostream& operator<<(std::ostream& s, const inclusion_delimiter_types& v) {
    s << "{ " << "\"__type__\": " << "\"inclusion_delimiter_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case inclusion_delimiter_types::invalid:
        attr = "\"invalid\"";
        break;
    case inclusion_delimiter_types::angle_brackets:
        attr = "\"angle_brackets\"";
        break;
    case inclusion_delimiter_types::double_quotes:
        attr = "\"double_quotes\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for inclusion_delimiter_types");
    }
    s << attr << " }";
    return s;
}

} } }