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
#include "dogen/sml/io/meta_types_io.hpp"

namespace dogen {
namespace sml {

std::ostream& operator<<(std::ostream& s, const meta_types& v) {
    s << "{ " << "\"__type__\": " << "\"meta_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case meta_types::invalid:
        attr = "\"invalid\"";
        break;
    case meta_types::model:
        attr = "\"model\"";
        break;
    case meta_types::enumeration:
        attr = "\"enumeration\"";
        break;
    case meta_types::primitive:
        attr = "\"primitive\"";
        break;
    case meta_types::exception:
        attr = "\"exception\"";
        break;
    case meta_types::module:
        attr = "\"module\"";
        break;
    case meta_types::service:
        attr = "\"service\"";
        break;
    case meta_types::entity:
        attr = "\"entity\"";
        break;
    case meta_types::keyed_entity:
        attr = "\"keyed_entity\"";
        break;
    case meta_types::value_object:
        attr = "\"value_object\"";
        break;
    case meta_types::factory:
        attr = "\"factory\"";
        break;
    case meta_types::repository:
        attr = "\"repository\"";
        break;
    case meta_types::concept:
        attr = "\"concept\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for meta_types");
    }
    s << attr << " }";
    return s;
}

} }