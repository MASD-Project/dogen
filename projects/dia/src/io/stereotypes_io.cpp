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
const std::string exception("exception");
const std::string versioned("versioned");
const std::string entity("entity");
const std::string value("value");
const std::string service("service");
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
    case stereotypes::exception:
        return stream << prefix << exception;
    case stereotypes::entity:
        return stream << prefix << entity;
    case stereotypes::value:
        return stream << prefix << value;
    case stereotypes::service:
        return stream << prefix << service;
    default:
        break;
    }
    throw utility::exception::invalid_enum_value(error_message);
}

} }
