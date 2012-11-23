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
#include "dogen/sml/io/meta_types_io.hpp"
#include "dogen/sml/io/qualified_name_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << *i << "\"";
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace sml {

std::ostream& operator<<(std::ostream& s, const qualified_name& v) {
    s << " { "
      << "\"__type__\": " << "\"qualified_name\"" << ", "
      << "\"model_name\": " << "\"" << v.model_name() << "\"" << ", "
      << "\"external_package_path\": " << v.external_package_path() << ", "
      << "\"package_path\": " << v.package_path() << ", "
      << "\"type_name\": " << "\"" << v.type_name() << "\"" << ", "
      << "\"meta_type\": " << v.meta_type()
      << " }";
    return(s);
}

} }