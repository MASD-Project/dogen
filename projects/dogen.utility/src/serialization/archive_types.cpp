/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include "dogen.utility/exception/invalid_enum_value.hpp"
#include "dogen.utility/serialization/archive_types.hpp"

namespace {

const std::string invalid("\"archive_types::invalid\"");
const std::string xml("\"archive_types::xml\"");
const std::string text("\"archive_types::text\"");
const std::string binary("\"archive_types::binary\"");

const std::string error_message("Invalid or unexpected object type");

}

namespace dogen {
namespace utility {
namespace serialization {

std::ostream& operator<<(std::ostream& stream, archive_types value) {
    switch (value) {
    case archive_types::invalid:
        return stream << invalid;
    case archive_types::xml:
        return stream << xml;
    case archive_types::text:
        return stream << text;
    case archive_types::binary:
        return stream << binary;
    default:
        break;
    }
    BOOST_THROW_EXCEPTION(utility::exception::invalid_enum_value(error_message));
}

} } }
