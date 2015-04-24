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
#include "dogen/stitch/io/token_types_io.hpp"

namespace dogen {
namespace stitch {

std::ostream& operator<<(std::ostream& s, const token_types& v) {
    s << "{ " << "\"__type__\": " << "\"token_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case token_types::invalid:
        attr = "\"invalid\"";
        break;
    case token_types::directive:
        attr = "\"directive\"";
        break;
    case token_types::start_standard_control_block:
        attr = "\"start_standard_control_block\"";
        break;
    case token_types::standard_control_block_content:
        attr = "\"standard_control_block_content\"";
        break;
    case token_types::end_standard_control_block:
        attr = "\"end_standard_control_block\"";
        break;
    case token_types::expression_control_block:
        attr = "\"expression_control_block\"";
        break;
    case token_types::text_content:
        attr = "\"text_content\"";
        break;
    case token_types::eol:
        attr = "\"eol\"";
        break;
    case token_types::eof:
        attr = "\"eof\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for token_types");
    }
    s << attr << " }";
    return s;
}

} }