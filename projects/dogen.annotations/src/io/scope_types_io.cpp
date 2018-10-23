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
#include "dogen.annotations/io/scope_types_io.hpp"

namespace dogen::annotations {

std::ostream& operator<<(std::ostream& s, const scope_types& v) {
    s << "{ " << "\"__type__\": " << "\"scope_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case scope_types::invalid:
        attr = "\"invalid\"";
        break;
    case scope_types::any:
        attr = "\"any\"";
        break;
    case scope_types::not_applicable:
        attr = "\"not_applicable\"";
        break;
    case scope_types::root_module:
        attr = "\"root_module\"";
        break;
    case scope_types::any_module:
        attr = "\"any_module\"";
        break;
    case scope_types::entity:
        attr = "\"entity\"";
        break;
    case scope_types::property:
        attr = "\"property\"";
        break;
    case scope_types::operation:
        attr = "\"operation\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for scope_types");
    }
    s << attr << " }";
    return s;
}

}
