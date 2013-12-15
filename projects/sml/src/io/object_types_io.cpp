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
#include "dogen/sml/io/object_types_io.hpp"

namespace dogen {
namespace sml {

std::ostream& operator<<(std::ostream& s, const object_types& v) {
    s << "{ " << "\"__type__\": " << "\"object_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case object_types::invalid:
        attr = "\"invalid\"";
        break;
    case object_types::entity:
        attr = "\"entity\"";
        break;
    case object_types::keyed_entity:
        attr = "\"keyed_entity\"";
        break;
    case object_types::factory:
        attr = "\"factory\"";
        break;
    case object_types::repository:
        attr = "\"repository\"";
        break;
    case object_types::user_defined_service:
        attr = "\"user_defined_service\"";
        break;
    case object_types::visitor:
        attr = "\"visitor\"";
        break;
    case object_types::key_extractor:
        attr = "\"key_extractor\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for object_types");
    }
    s << attr << " }";
    return s;
}

} }