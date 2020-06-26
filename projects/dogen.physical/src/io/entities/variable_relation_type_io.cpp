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
#include "dogen.physical/io/entities/variable_relation_type_io.hpp"

namespace dogen::physical::entities {

std::ostream& operator<<(std::ostream& s, const variable_relation_type& v) {
    s << "{ " << "\"__type__\": " << "\"variable_relation_type\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case variable_relation_type::invalid:
        attr = "\"invalid\"";
        break;
    case variable_relation_type::self:
        attr = "\"self\"";
        break;
    case variable_relation_type::parent:
        attr = "\"parent\"";
        break;
    case variable_relation_type::child:
        attr = "\"child\"";
        break;
    case variable_relation_type::transparent:
        attr = "\"transparent\"";
        break;
    case variable_relation_type::opaque:
        attr = "\"opaque\"";
        break;
    case variable_relation_type::associative_key:
        attr = "\"associative_key\"";
        break;
    case variable_relation_type::visitation:
        attr = "\"visitation\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for variable_relation_type");
    }
    s << attr << " }";
    return s;
}

}
