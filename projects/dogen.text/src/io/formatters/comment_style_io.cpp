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
#include "dogen.text/io/formatters/comment_style_io.hpp"

namespace dogen::text::formatters {

std::ostream& operator<<(std::ostream& s, const comment_style& v) {
    s << "{ " << "\"__type__\": " << "\"comment_style\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case comment_style::invalid:
        attr = "\"invalid\"";
        break;
    case comment_style::c_style:
        attr = "\"c_style\"";
        break;
    case comment_style::cpp_style:
        attr = "\"cpp_style\"";
        break;
    case comment_style::csharp_style:
        attr = "\"csharp_style\"";
        break;
    case comment_style::shell_style:
        attr = "\"shell_style\"";
        break;
    case comment_style::sql_style:
        attr = "\"sql_style\"";
        break;
    case comment_style::xml_style:
        attr = "\"xml_style\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for comment_style");
    }
    s << attr << " }";
    return s;
}

}
