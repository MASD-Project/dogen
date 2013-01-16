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
#include "dogen/config/io/cpp_facet_types_io.hpp"

namespace dogen {
namespace config {

std::ostream& operator<<(std::ostream& s, const cpp_facet_types& v) {
    s << "{ " << "\"__type__\": " << "\"cpp_facet_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case cpp_facet_types::invalid:
        attr = "\"invalid\"";
        break;
    case cpp_facet_types::types:
        attr = "\"types\"";
        break;
    case cpp_facet_types::hash:
        attr = "\"hash\"";
        break;
    case cpp_facet_types::serialization:
        attr = "\"serialization\"";
        break;
    case cpp_facet_types::io:
        attr = "\"io\"";
        break;
    case cpp_facet_types::test_data:
        attr = "\"test_data\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for cpp_facet_types");
    }
    s << attr << " }";
    return s;
}

} }