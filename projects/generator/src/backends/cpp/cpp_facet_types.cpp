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
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/generator/backends/cpp/cpp_facet_types.hpp"

namespace {

const std::string invalid("\"cpp_facet_types::invalid\"");
const std::string domain("\"cpp_facet_types::domain\"");
const std::string hash("\"cpp_facet_types::hash\"");
const std::string serialization("\"cpp_facet_types::serialization\"");
const std::string io("\"cpp_facet_types::io\"");
const std::string test_data("\"cpp_facet_types::test_data\"");
const std::string database("\"cpp_facet_types::database\"");
const std::string error_message("\"Invalid or unexpected C++ facet type\"");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

std::ostream& operator<<(std::ostream& stream, cpp_facet_types value) {
    switch (value) {
    case cpp_facet_types::invalid:
        return stream << invalid;
    case cpp_facet_types::domain:
        return stream << domain;
    case cpp_facet_types::hash:
        return stream << hash;
    case cpp_facet_types::serialization:
        return stream << serialization;
    case cpp_facet_types::io:
        return stream << io;
    case cpp_facet_types::test_data:
        return stream << test_data;
    case cpp_facet_types::database:
        return stream << database;
    default:
        break;
    }
    throw utility::exception::invalid_enum_value(error_message);
}

} } } }
