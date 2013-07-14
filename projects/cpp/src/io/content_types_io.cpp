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
#include "dogen/cpp/io/content_types_io.hpp"

namespace dogen {
namespace cpp {

std::ostream& operator<<(std::ostream& s, const content_types& v) {
    s << "{ " << "\"__type__\": " << "\"content_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case content_types::invalid:
        attr = "\"invalid\"";
        break;
    case content_types::exception:
        attr = "\"exception\"";
        break;
    case content_types::enumeration:
        attr = "\"enumeration\"";
        break;
    case content_types::primitive:
        attr = "\"primitive\"";
        break;
    case content_types::value_object:
        attr = "\"value_object\"";
        break;
    case content_types::user_defined_service:
        attr = "\"user_defined_service\"";
        break;
    case content_types::visitor:
        attr = "\"visitor\"";
        break;
    case content_types::key_extractor:
        attr = "\"key_extractor\"";
        break;
    case content_types::factory:
        attr = "\"factory\"";
        break;
    case content_types::repository:
        attr = "\"repository\"";
        break;
    case content_types::keyed_entity:
        attr = "\"keyed_entity\"";
        break;
    case content_types::entity:
        attr = "\"entity\"";
        break;
    case content_types::registrar:
        attr = "\"registrar\"";
        break;
    case content_types::namespace_doc:
        attr = "\"namespace_doc\"";
        break;
    case content_types::includer:
        attr = "\"includer\"";
        break;
    case content_types::versioned_key:
        attr = "\"versioned_key\"";
        break;
    case content_types::unversioned_key:
        attr = "\"unversioned_key\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for content_types");
    }
    s << attr << " }";
    return s;
}

} }