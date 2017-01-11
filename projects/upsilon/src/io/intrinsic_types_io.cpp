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
#include "dogen/upsilon/io/intrinsic_types_io.hpp"

namespace dogen {
namespace upsilon {

std::ostream& operator<<(std::ostream& s, const intrinsic_types& v) {
    s << "{ " << "\"__type__\": " << "\"intrinsic_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case intrinsic_types::invalid:
        attr = "\"invalid\"";
        break;
    case intrinsic_types::integer:
        attr = "\"integer\"";
        break;
    case intrinsic_types::binary:
        attr = "\"binary\"";
        break;
    case intrinsic_types::boolean:
        attr = "\"boolean\"";
        break;
    case intrinsic_types::date:
        attr = "\"date\"";
        break;
    case intrinsic_types::decimal:
        attr = "\"decimal\"";
        break;
    case intrinsic_types::double_x:
        attr = "\"double_x\"";
        break;
    case intrinsic_types::guid:
        attr = "\"guid\"";
        break;
    case intrinsic_types::integer64:
        attr = "\"integer64\"";
        break;
    case intrinsic_types::string:
        attr = "\"string\"";
        break;
    case intrinsic_types::utc_time:
        attr = "\"utc_time\"";
        break;
    case intrinsic_types::utc_date_time:
        attr = "\"utc_date_time\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for intrinsic_types");
    }
    s << attr << " }";
    return s;
}

} }
