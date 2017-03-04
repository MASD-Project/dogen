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
#include "dogen/test_models/cpp_model/io/package_4/shape_types_io.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {
namespace package_4 {

std::ostream& operator<<(std::ostream& s, const shape_types& v) {
    s << "{ " << "\"__type__\": " << "\"shape_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case shape_types::invalid:
        attr = "\"invalid\"";
        break;
    case shape_types::triangle:
        attr = "\"triangle\"";
        break;
    case shape_types::square:
        attr = "\"square\"";
        break;
    case shape_types::rectangle:
        attr = "\"rectangle\"";
        break;
    case shape_types::circle:
        attr = "\"circle\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for shape_types");
    }
    s << attr << " }";
    return s;
}

} } } }
