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
#include "dogen/cpp/io/formatters/formatter_types_io.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

std::ostream& operator<<(std::ostream& s, const formatter_types& v) {
    s << "{ " << "\"__type__\": " << "\"formatter_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case formatter_types::invalid:
        attr = "\"invalid\"";
        break;
    case formatter_types::class_formatter:
        attr = "\"class_formatter\"";
        break;
    case formatter_types::visitor_formatter:
        attr = "\"visitor_formatter\"";
        break;
    case formatter_types::enum_formatter:
        attr = "\"enum_formatter\"";
        break;
    case formatter_types::registrar_formatter:
        attr = "\"registrar_formatter\"";
        break;
    case formatter_types::namespace_formatter:
        attr = "\"namespace_formatter\"";
        break;
    case formatter_types::exception_formatter:
        attr = "\"exception_formatter\"";
        break;
    case formatter_types::forward_declarations_formatter:
        attr = "\"forward_declarations_formatter\"";
        break;
    case formatter_types::includers_formatter:
        attr = "\"includers_formatter\"";
        break;
    case formatter_types::odb_options_formatter:
        attr = "\"odb_options_formatter\"";
        break;
    case formatter_types::cmakelists_formatter:
        attr = "\"cmakelists_formatter\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for formatter_types");
    }
    s << attr << " }";
    return s;
}

} } }