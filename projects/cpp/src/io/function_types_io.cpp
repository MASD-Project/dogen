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
#include "dogen/cpp/io/function_types_io.hpp"

namespace dogen {
namespace cpp {

std::ostream& operator<<(std::ostream& s, const function_types& v) {
    s << "{ " << "\"__type__\": " << "\"function_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case function_types::invalid:
        attr = "\"invalid\"";
        break;
    case function_types::none:
        attr = "\"none\"";
        break;
    case function_types::normal_type:
        attr = "\"normal_type\"";
        break;
    case function_types::constructor_type:
        attr = "\"constructor_type\"";
        break;
    case function_types::destructor_type:
        attr = "\"destructor_type\"";
        break;
    case function_types::operator_type:
        attr = "\"operator_type\"";
        break;
    case function_types::conversion_type:
        attr = "\"conversion_type\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for function_types");
    }
    s << attr << " }";
    return s;
}

} }