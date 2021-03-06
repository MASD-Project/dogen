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
#include "dogen.logical/io/entities/generability_status_io.hpp"

namespace dogen::logical::entities {

std::ostream& operator<<(std::ostream& s, const generability_status& v) {
    s << "{ " << "\"__type__\": " << "\"generability_status\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case generability_status::invalid:
        attr = "\"invalid\"";
        break;
    case generability_status::non_generatable_source:
        attr = "\"non_generatable_source\"";
        break;
    case generability_status::generation_not_expected:
        attr = "\"generation_not_expected\"";
        break;
    case generability_status::non_generatable_state:
        attr = "\"non_generatable_state\"";
        break;
    case generability_status::generation_disabled:
        attr = "\"generation_disabled\"";
        break;
    case generability_status::generation_ignored:
        attr = "\"generation_ignored\"";
        break;
    case generability_status::generatable:
        attr = "\"generatable\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for generability_status");
    }
    s << attr << " }";
    return s;
}

}
