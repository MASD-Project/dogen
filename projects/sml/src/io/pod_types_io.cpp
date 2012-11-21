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
#include "dogen/sml/io/pod_types_io.hpp"

namespace {

const std::string prefix("pod_types::");
const std::string invalid("invalid");
const std::string sequence_container("sequence_container");
const std::string associative_container("associative_container");
const std::string smart_pointer("smart_pointer");
const std::string entity("entity");
const std::string value("value");
const std::string service("service");

const std::string error_message("Invalid enum value");

}

namespace dogen {
namespace sml {

std::ostream& operator<<(std::ostream& stream, pod_types v) {
    switch (v) {
    case pod_types::invalid:
        return stream << prefix << invalid;
    case pod_types::sequence_container:
        return stream << prefix << sequence_container;
    case pod_types::associative_container:
        return stream << prefix << associative_container;
    case pod_types::smart_pointer:
        return stream << prefix << smart_pointer;
    case pod_types::entity:
        return stream << prefix << entity;
    case pod_types::value:
        return stream << prefix << value;
    case pod_types::service:
        return stream << prefix << service;
    default:
        using utility::exception::invalid_enum_value;
        throw invalid_enum_value(error_message);
    }
    return stream << prefix << error_message;
}

} }
