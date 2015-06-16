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
#include "dogen/dia_to_sml/io/object_types_io.hpp"

namespace dogen {
namespace dia_to_sml {

std::ostream& operator<<(std::ostream& s, const object_types& v) {
    s << "{ " << "\"__type__\": " << "\"object_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case object_types::invalid:
        attr = "\"invalid\"";
        break;
    case object_types::uml_large_package:
        attr = "\"uml_large_package\"";
        break;
    case object_types::uml_class:
        attr = "\"uml_class\"";
        break;
    case object_types::uml_generalization:
        attr = "\"uml_generalization\"";
        break;
    case object_types::uml_association:
        attr = "\"uml_association\"";
        break;
    case object_types::uml_note:
        attr = "\"uml_note\"";
        break;
    case object_types::uml_message:
        attr = "\"uml_message\"";
        break;
    case object_types::uml_realization:
        attr = "\"uml_realization\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for object_types");
    }
    s << attr << " }";
    return s;
}

} }
