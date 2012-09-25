/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include <string>
#include <ostream>
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/sml/io/meta_types_io.hpp"

namespace {

const std::string prefix("meta_types::");
const std::string invalid("invalid");
const std::string enumeration("enumeration");
const std::string pod("pod");
const std::string primitive("primitive");
const std::string attribute("attribute");
const std::string package("package");

const std::string error_message("Invalid enum value");

}

namespace dogen {
namespace sml {

std::ostream& operator<<(std::ostream& stream, meta_types value) {
    switch (value) {
    case meta_types::invalid:
        return stream << prefix << invalid;
    case meta_types::enumeration:
        return stream << prefix << enumeration;
    case meta_types::pod:
        return stream << prefix << pod;
    case meta_types::attribute:
        return stream << prefix << attribute;
    case meta_types::package:
        return stream << prefix << package;
    case meta_types::primitive:
        return stream << prefix << primitive;
    }
    return stream << prefix << error_message;
}

} }
