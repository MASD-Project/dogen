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
#include "dogen/cpp/io/cpp_aspect_types_io.hpp"

namespace dogen {
namespace cpp {

std::ostream& operator<<(std::ostream& s, const cpp_aspect_types& v) {
    s << "{ " << "\"__type__\": " << "\"cpp_aspect_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case cpp_aspect_types::invalid:
        attr = "\"invalid\"";
        break;
    case cpp_aspect_types::main:
        attr = "\"main\"";
        break;
    case cpp_aspect_types::includers:
        attr = "\"includers\"";
        break;
    case cpp_aspect_types::forward_decls:
        attr = "\"forward_decls\"";
        break;
    case cpp_aspect_types::registrar:
        attr = "\"registrar\"";
        break;
    case cpp_aspect_types::null_aspect:
        attr = "\"null_aspect\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for cpp_aspect_types");
    }
    s << attr << " }";
    return s;
}

} }