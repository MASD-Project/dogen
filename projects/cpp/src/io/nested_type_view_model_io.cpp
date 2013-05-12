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
#include "dogen/cpp/io/nested_type_view_model_io.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::cpp::nested_type_view_model>& v) {
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
namespace cpp {

std::ostream& operator<<(std::ostream& s, const nested_type_view_model& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::nested_type_view_model\"" << ", "
      << "\"name\": " << "\"" << tidy_up_string(v.name()) << "\"" << ", "
      << "\"identifiable_name\": " << "\"" << tidy_up_string(v.identifiable_name()) << "\"" << ", "
      << "\"complete_name\": " << "\"" << tidy_up_string(v.complete_name()) << "\"" << ", "
      << "\"complete_identifiable_name\": " << "\"" << tidy_up_string(v.complete_identifiable_name()) << "\"" << ", "
      << "\"is_primitive\": " << v.is_primitive() << ", "
      << "\"is_enumeration\": " << v.is_enumeration() << ", "
      << "\"is_string_like\": " << v.is_string_like() << ", "
      << "\"is_char_like\": " << v.is_char_like() << ", "
      << "\"is_int_like\": " << v.is_int_like() << ", "
      << "\"is_sequence_container\": " << v.is_sequence_container() << ", "
      << "\"is_associative_container\": " << v.is_associative_container() << ", "
      << "\"is_smart_pointer\": " << v.is_smart_pointer() << ", "
      << "\"is_optional_like\": " << v.is_optional_like() << ", "
      << "\"is_variant_like\": " << v.is_variant_like() << ", "
      << "\"children\": " << v.children() << ", "
      << "\"namespaces\": " << v.namespaces() << ", "
      << "\"is_filesystem_path\": " << v.is_filesystem_path() << ", "
      << "\"is_date\": " << v.is_date() << ", "
      << "\"is_ptime\": " << v.is_ptime() << ", "
      << "\"is_time_duration\": " << v.is_time_duration() << ", "
      << "\"is_pair\": " << v.is_pair()
      << " }";
    return(s);
}

} }