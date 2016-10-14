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
#include <boost/io/ios_state.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/yarn.dia/io/profile_io.hpp"

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
namespace yarn {
namespace dia {

std::ostream& operator<<(std::ostream& s, const profile& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::dia::profile\"" << ", "
      << "\"is_uml_large_package\": " << v.is_uml_large_package() << ", "
      << "\"is_uml_class\": " << v.is_uml_class() << ", "
      << "\"is_uml_generalization\": " << v.is_uml_generalization() << ", "
      << "\"is_uml_association\": " << v.is_uml_association() << ", "
      << "\"is_uml_note\": " << v.is_uml_note() << ", "
      << "\"is_uml_message\": " << v.is_uml_message() << ", "
      << "\"is_uml_realization\": " << v.is_uml_realization() << ", "
      << "\"is_enumeration\": " << v.is_enumeration() << ", "
      << "\"is_exception\": " << v.is_exception() << ", "
      << "\"is_concept\": " << v.is_concept() << ", "
      << "\"is_value_object\": " << v.is_value_object() << ", "
      << "\"is_service\": " << v.is_service() << ", "
      << "\"is_non_generatable\": " << v.is_non_generatable() << ", "
      << "\"unknown_stereotypes\": " << v.unknown_stereotypes()
      << " }";
    return(s);
}

} } }
