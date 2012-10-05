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
