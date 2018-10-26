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
#include "masd.dogen/io/log_level_io.hpp"

namespace masd::dogen {

std::ostream& operator<<(std::ostream& s, const log_level& v) {
    s << "{ " << "\"__type__\": " << "\"log_level\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case log_level::invalid:
        attr = "\"invalid\"";
        break;
    case log_level::trace:
        attr = "\"trace\"";
        break;
    case log_level::debug:
        attr = "\"debug\"";
        break;
    case log_level::info:
        attr = "\"info\"";
        break;
    case log_level::warn:
        attr = "\"warn\"";
        break;
    case log_level::error:
        attr = "\"error\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for log_level");
    }
    s << attr << " }";
    return s;
}

}
