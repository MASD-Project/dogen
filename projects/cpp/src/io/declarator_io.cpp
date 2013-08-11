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
#include "dogen/cpp/io/cv_qualifier_types_io.hpp"
#include "dogen/cpp/io/declarator_io.hpp"
#include "dogen/cpp/io/parameter_declaration_io.hpp"
#include "dogen/cpp/io/pointer_types_io.hpp"
#include "dogen/cpp/io/qualified_id_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::cpp::qualified_id>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::cpp::parameter_declaration>& v) {
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

std::ostream& operator<<(std::ostream& s, const declarator& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::declarator\"" << ", "
      << "\"cv_qualifier\": " << v.cv_qualifier() << ", "
      << "\"pointer_type\": " << v.pointer_type() << ", "
      << "\"pointer_cv_qualifier\": " << v.pointer_cv_qualifier() << ", "
      << "\"declarator_id\": " << v.declarator_id() << ", "
      << "\"exception_specification\": " << v.exception_specification() << ", "
      << "\"parameter_declaration_list\": " << v.parameter_declaration_list()
      << " }";
    return(s);
}

} }