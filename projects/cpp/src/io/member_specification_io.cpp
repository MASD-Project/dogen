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
#include "dogen/cpp/io/access_specifier_types_io.hpp"
#include "dogen/cpp/io/member_declaration_io.hpp"
#include "dogen/cpp/io/member_specification_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::cpp::member_declaration>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace cpp {

std::ostream& operator<<(std::ostream& s, const member_specification& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::member_specification\"" << ", "
      << "\"access\": " << v.access() << ", "
      << "\"member_declaration_list\": " << v.member_declaration_list()
      << " }";
    return(s);
}

} }