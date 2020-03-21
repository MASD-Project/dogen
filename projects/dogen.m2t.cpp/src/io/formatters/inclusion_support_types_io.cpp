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
#include "dogen.m2t.cpp/io/formatters/inclusion_support_types_io.hpp"

namespace dogen::m2t::cpp::formatters {

std::ostream& operator<<(std::ostream& s, const inclusion_support_types& v) {
    s << "{ " << "\"__type__\": " << "\"inclusion_support_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case inclusion_support_types::invalid:
        attr = "\"invalid\"";
        break;
    case inclusion_support_types::not_supported:
        attr = "\"not_supported\"";
        break;
    case inclusion_support_types::regular_support:
        attr = "\"regular_support\"";
        break;
    case inclusion_support_types::canonical_support:
        attr = "\"canonical_support\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for inclusion_support_types");
    }
    s << attr << " }";
    return s;
}

}
