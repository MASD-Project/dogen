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
