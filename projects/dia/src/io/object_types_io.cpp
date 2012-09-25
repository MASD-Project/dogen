/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Dogen
 *
 * This file is distributed under the Dogen Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <string>
#include <ostream>
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/dia/io/object_types_io.hpp"

namespace {

const std::string prefix("object_types::");
const std::string invalid("invalid");
const std::string uml_large_package("uml_large_package");
const std::string uml_class("uml_class");

const std::string error_message("Invalid or unexpected object type");

}

namespace dogen {
namespace dia {

std::ostream& operator<<(std::ostream& stream, object_types value) {
    switch (value) {
    case object_types::invalid:
        return stream << prefix << invalid;
    case object_types::uml_large_package:
        return stream << prefix << uml_large_package;
    case object_types::uml_class:
        return stream << prefix << uml_class;
    default:
        break;
    }
    throw utility::exception::invalid_enum_value(error_message);
}

} }
