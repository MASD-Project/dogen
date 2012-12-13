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
#include <boost/throw_exception.hpp>
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/dia/io/object_types_io.hpp"
#include "dogen/utility/log/logger.hpp"

using namespace dogen::utility::log;

namespace {

const std::string prefix("object_types::");
const std::string invalid("invalid");
const std::string uml_large_package("uml_large_package");
const std::string uml_class("uml_class");
const std::string uml_generalization("uml_generalization");
const std::string uml_association("uml_association");
const std::string uml_note("uml_note");
const std::string uml_message("uml_message");

const std::string error_message("Invalid or unexpected object type");

auto lg(logger_factory("generator"));

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
    case object_types::uml_generalization:
        return stream << prefix << uml_generalization;
    case object_types::uml_association:
        return stream << prefix << uml_association;
    case object_types::uml_note:
        return stream << prefix << uml_note;
    case object_types::uml_message:
        return stream << prefix << uml_message;
    default:
        break;
    }
    BOOST_LOG_SEV(lg, error) << error_message;
    BOOST_THROW_EXCEPTION(utility::exception::invalid_enum_value(error_message));
}

} }
