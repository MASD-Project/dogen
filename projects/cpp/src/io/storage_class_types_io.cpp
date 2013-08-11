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
#include <stdexcept>
#include "dogen/cpp/io/storage_class_types_io.hpp"

namespace dogen {
namespace cpp {

std::ostream& operator<<(std::ostream& s, const storage_class_types& v) {
    s << "{ " << "\"__type__\": " << "\"storage_class_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case storage_class_types::invalid:
        attr = "\"invalid\"";
        break;
    case storage_class_types::none:
        attr = "\"none\"";
        break;
    case storage_class_types::auto_type:
        attr = "\"auto_type\"";
        break;
    case storage_class_types::register_type:
        attr = "\"register_type\"";
        break;
    case storage_class_types::static_type:
        attr = "\"static_type\"";
        break;
    case storage_class_types::extern_type:
        attr = "\"extern_type\"";
        break;
    case storage_class_types::mutable_type:
        attr = "\"mutable_type\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for storage_class_types");
    }
    s << attr << " }";
    return s;
}

} }