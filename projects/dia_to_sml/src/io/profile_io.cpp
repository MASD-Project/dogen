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
#include <boost/io/ios_state.hpp>
#include <ostream>
#include "dogen/dia_to_sml/io/profile_io.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace dia_to_sml {

std::ostream& operator<<(std::ostream& s, const profile& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::dia_to_sml::profile\"" << ", "
      << "\"is_uml_large_package\": " << v.is_uml_large_package() << ", "
      << "\"is_uml_class\": " << v.is_uml_class() << ", "
      << "\"is_uml_generalization\": " << v.is_uml_generalization() << ", "
      << "\"is_uml_association\": " << v.is_uml_association() << ", "
      << "\"is_uml_note\": " << v.is_uml_note() << ", "
      << "\"is_uml_message\": " << v.is_uml_message() << ", "
      << "\"is_uml_realization\": " << v.is_uml_realization() << ", "
      << "\"is_enumeration\": " << v.is_enumeration() << ", "
      << "\"is_exception\": " << v.is_exception() << ", "
      << "\"is_entity\": " << v.is_entity() << ", "
      << "\"is_value\": " << v.is_value() << ", "
      << "\"is_service\": " << v.is_service() << ", "
      << "\"is_non_generatable\": " << v.is_non_generatable() << ", "
      << "\"is_versioned\": " << v.is_versioned() << ", "
      << "\"is_keyed\": " << v.is_keyed() << ", "
      << "\"is_visitable\": " << v.is_visitable() << ", "
      << "\"is_immutable\": " << v.is_immutable() << ", "
      << "\"is_fluent\": " << v.is_fluent() << ", "
      << "\"is_aggregate_root\": " << v.is_aggregate_root() << ", "
      << "\"is_string_table\": " << v.is_string_table() << ", "
      << "\"unknown_stereotypes\": " << v.unknown_stereotypes()
      << " }";
    return(s);
}

} }