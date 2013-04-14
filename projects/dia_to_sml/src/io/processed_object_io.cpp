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
#include <boost/algorithm/string.hpp>
#include <ostream>
#include "dogen/dia/io/composite_io.hpp"
#include "dogen/dia_to_sml/io/object_types_io.hpp"
#include "dogen/dia_to_sml/io/processed_object_io.hpp"
#include "dogen/dia_to_sml/io/stereotypes_io.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<dogen::dia::composite>& v) {
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
namespace dia_to_sml {

std::ostream& operator<<(std::ostream& s, const processed_object& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::dia_to_sml::processed_object\"" << ", "
      << "\"name\": " << "\"" << tidy_up_string(v.name()) << "\"" << ", "
      << "\"object_type\": " << v.object_type() << ", "
      << "\"stereotype\": " << v.stereotype() << ", "
      << "\"comment\": " << "\"" << tidy_up_string(v.comment()) << "\"" << ", "
      << "\"uml_attributes\": " << v.uml_attributes() << ", "
      << "\"parent_id\": " << "\"" << tidy_up_string(v.parent_id()) << "\""
      << " }";
    return(s);
}

} }