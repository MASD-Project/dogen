/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/dia/utility/dia_utility.hpp"

namespace {

const std::string uml_large_package("UML - LargePackage");
const std::string uml_class("UML - Class");

const std::string error_message("Invalid or unsupported Dia type");

}

namespace dogen {
namespace dia {
namespace utility {

object_types parse_object_type(const std::string& dia_type) {
    if (dia_type == uml_large_package)
        return object_types::uml_large_package;

    if (dia_type == uml_class)
        return object_types::uml_class;

    throw dogen::utility::exception::exception(error_message);
}

} } }
