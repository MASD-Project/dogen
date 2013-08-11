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
#include "dogen/cpp/io/fundamental_types_io.hpp"

namespace dogen {
namespace cpp {

std::ostream& operator<<(std::ostream& s, const fundamental_types& v) {
    s << "{ " << "\"__type__\": " << "\"fundamental_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case fundamental_types::invalid:
        attr = "\"invalid\"";
        break;
    case fundamental_types::char_type:
        attr = "\"char_type\"";
        break;
    case fundamental_types::unsigned_char_type:
        attr = "\"unsigned_char_type\"";
        break;
    case fundamental_types::signed_char_type:
        attr = "\"signed_char_type\"";
        break;
    case fundamental_types::bool_type:
        attr = "\"bool_type\"";
        break;
    case fundamental_types::unsigned_int_type:
        attr = "\"unsigned_int_type\"";
        break;
    case fundamental_types::int_type:
        attr = "\"int_type\"";
        break;
    case fundamental_types::unsinged_short_int_type:
        attr = "\"unsinged_short_int_type\"";
        break;
    case fundamental_types::short_int_type:
        attr = "\"short_int_type\"";
        break;
    case fundamental_types::unsigned_long_int_type:
        attr = "\"unsigned_long_int_type\"";
        break;
    case fundamental_types::long_int_type:
        attr = "\"long_int_type\"";
        break;
    case fundamental_types::wchar_t_type:
        attr = "\"wchar_t_type\"";
        break;
    case fundamental_types::float_type:
        attr = "\"float_type\"";
        break;
    case fundamental_types::double_type:
        attr = "\"double_type\"";
        break;
    case fundamental_types::long_double_type:
        attr = "\"long_double_type\"";
        break;
    case fundamental_types::void_type:
        attr = "\"void_type\"";
        break;
    case fundamental_types::non_iso_type:
        attr = "\"non_iso_type\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for fundamental_types");
    }
    s << attr << " }";
    return s;
}

} }