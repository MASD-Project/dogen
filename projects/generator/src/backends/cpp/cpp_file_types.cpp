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
 * You should have received a copy of the GNU General PublicLicense
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <ostream>
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/generator/backends/cpp/cpp_file_types.hpp"

namespace {

const std::string invalid("\"cpp_file_types::invalid\"");
const std::string header("\"cpp_file_types::header\"");
const std::string implementation("\"cpp_file_types::implementation\"");
const std::string error_message("\"Invalid or unexpected file type\"");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

std::ostream& operator<<(std::ostream& stream, cpp_file_types value) {
    switch (value) {
    case cpp_file_types::invalid:
        return stream << invalid;
    case cpp_file_types::header:
        return stream << header;
    case cpp_file_types::implementation:
        return stream << implementation;
    default:
        break;
    }
    throw utility::exception::invalid_enum_value(error_message);
}

} } } }
