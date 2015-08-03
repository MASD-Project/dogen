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
#include "dogen/tack/io/relationship_types_io.hpp"

namespace dogen {
namespace tack {

std::ostream& operator<<(std::ostream& s, const relationship_types& v) {
    s << "{ " << "\"__type__\": " << "\"relationship_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case relationship_types::invalid:
        attr = "\"invalid\"";
        break;
    case relationship_types::original_parents:
        attr = "\"original_parents\"";
        break;
    case relationship_types::parents:
        attr = "\"parents\"";
        break;
    case relationship_types::regular_associations:
        attr = "\"regular_associations\"";
        break;
    case relationship_types::weak_associations:
        attr = "\"weak_associations\"";
        break;
    case relationship_types::leaves:
        attr = "\"leaves\"";
        break;
    case relationship_types::visits:
        attr = "\"visits\"";
        break;
    case relationship_types::visited_by:
        attr = "\"visited_by\"";
        break;
    case relationship_types::modeled_concepts:
        attr = "\"modeled_concepts\"";
        break;
    case relationship_types::hash_container_keys:
        attr = "\"hash_container_keys\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for relationship_types");
    }
    s << attr << " }";
    return s;
}

} }
