/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <ostream>
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/generator/backends/cpp/cpp_aspect_types.hpp"

namespace {

const std::string invalid("\"cpp_aspect_types::invalid\"");
const std::string main("\"cpp_aspect_types::main\"");
const std::string includers("\"cpp_aspect_types::includers\"");
const std::string versioned_key("\"cpp_aspect_types::versioned_key\"");
const std::string unversioned_key("\"cpp_aspect_types::unversioned_key\"");
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
    case cpp_aspect_types::versioned_key:
        return stream << versioned_key;
    case cpp_aspect_types::unversioned_key:
        return stream << unversioned_key;
    default:
        break;
    }
    throw dogen::utility::exception::invalid_enum_value(error_message);
}

} } } }
