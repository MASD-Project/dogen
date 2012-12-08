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
#include <boost/throw_exception.hpp>
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/generator/backends/cpp/cpp_aspect_types.hpp"

namespace {

const std::string invalid("\"cpp_aspect_types::invalid\"");
const std::string main("\"cpp_aspect_types::main\"");
const std::string includers("\"cpp_aspect_types::includers\"");
const std::string forward_decls("\"cpp_aspect_types::forward_decls\"");
const std::string registrar("\"cpp_aspect_types::registrar\"");
const std::string null_aspect("\"cpp_aspect_types::null_aspect\"");
const std::string error_message("\"Invalid or unexpected aspect type\"");

}

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {

std::ostream& operator<<(std::ostream& stream, cpp_aspect_types value) {
    switch (value) {
    case cpp_aspect_types::invalid:
        return stream << invalid;
    case cpp_aspect_types::main:
        return stream << main;
    case cpp_aspect_types::includers:
        return stream << includers;
    case cpp_aspect_types::forward_decls:
        return stream << forward_decls;
    case cpp_aspect_types::registrar:
        return stream << registrar;
    case cpp_aspect_types::null_aspect:
        return stream << null_aspect;
    default:
        break;
    }
    BOOST_THROW_EXCEPTION(dogen::utility::exception::invalid_enum_value(error_message));
}

} } } }
