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
#include "dogen.logical/io/entities/technical_space_io.hpp"

namespace dogen::logical::entities {

std::ostream& operator<<(std::ostream& s, const technical_space& v) {
    s << "{ " << "\"__type__\": " << "\"technical_space\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case technical_space::invalid:
        attr = "\"invalid\"";
        break;
    case technical_space::agnostic:
        attr = "\"agnostic\"";
        break;
    case technical_space::cpp:
        attr = "\"cpp\"";
        break;
    case technical_space::csharp:
        attr = "\"csharp\"";
        break;
    case technical_space::cmake:
        attr = "\"cmake\"";
        break;
    case technical_space::xml:
        attr = "\"xml\"";
        break;
    case technical_space::odb:
        attr = "\"odb\"";
        break;
    case technical_space::sln:
        attr = "\"sln\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for technical_space");
    }
    s << attr << " }";
    return s;
}

}
