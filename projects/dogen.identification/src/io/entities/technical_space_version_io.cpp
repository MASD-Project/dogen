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
#include <string>
#include <ostream>
#include <stdexcept>
#include "dogen.identification/io/entities/technical_space_version_io.hpp"

namespace dogen::identification::entities {

std::ostream& operator<<(std::ostream& s, const technical_space_version& v) {
    s << "{ " << "\"__type__\": " << "\"technical_space_version\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case technical_space_version::invalid:
        attr = "\"invalid\"";
        break;
    case technical_space_version::cpp_98:
        attr = "\"cpp_98\"";
        break;
    case technical_space_version::cpp_11:
        attr = "\"cpp_11\"";
        break;
    case technical_space_version::cpp_14:
        attr = "\"cpp_14\"";
        break;
    case technical_space_version::cpp_17:
        attr = "\"cpp_17\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for technical_space_version");
    }
    s << attr << " }";
    return s;
}

}
