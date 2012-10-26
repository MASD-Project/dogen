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
#include <string>
#include <ostream>
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/dia/io/stereotypes_io.hpp"

namespace {

const std::string prefix("stereotypes::");
const std::string invalid("invalid");
const std::string enumeration("enumeration");

const std::string error_message("Invalid or unexpected object type");

}

namespace dogen {
namespace dia {

std::ostream& operator<<(std::ostream& stream, stereotypes value) {
    switch (value) {
    case stereotypes::invalid:
        return stream << prefix << invalid;
    case stereotypes::enumeration:
        return stream << prefix << enumeration;
    default:
        break;
    }
    throw utility::exception::invalid_enum_value(error_message);
}

} }
