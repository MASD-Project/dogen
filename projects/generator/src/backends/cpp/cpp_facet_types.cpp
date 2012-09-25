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
