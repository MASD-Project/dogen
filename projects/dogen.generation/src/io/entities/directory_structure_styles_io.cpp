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
#include "dogen.generation/io/entities/directory_structure_styles_io.hpp"

namespace dogen::generation::entities {

std::ostream& operator<<(std::ostream& s, const directory_structure_styles& v) {
    s << "{ " << "\"__type__\": " << "\"directory_structure_styles\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case directory_structure_styles::invalid:
        attr = "\"invalid\"";
        break;
    case directory_structure_styles::structured:
        attr = "\"structured\"";
        break;
    case directory_structure_styles::completely_flat:
        attr = "\"completely_flat\"";
        break;
    case directory_structure_styles::flatten_facets:
        attr = "\"flatten_facets\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for directory_structure_styles");
    }
    s << attr << " }";
    return s;
}

}
