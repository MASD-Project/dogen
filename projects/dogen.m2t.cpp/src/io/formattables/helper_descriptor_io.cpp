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
#include "dogen.m2t.cpp/io/formattables/helper_descriptor_io.hpp"
#include "dogen.m2t.cpp/io/formattables/streaming_properties_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
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

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::m2t::cpp::formattables::streaming_properties>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace dogen::m2t::cpp::formattables {

std::ostream& operator<<(std::ostream& s, const helper_descriptor& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::m2t::cpp::formattables::helper_descriptor\"" << ", "
      << "\"family\": " << "\"" << tidy_up_string(v.family()) << "\"" << ", "
      << "\"namespaces\": " << v.namespaces() << ", "
      << "\"name_identifiable\": " << "\"" << tidy_up_string(v.name_identifiable()) << "\"" << ", "
      << "\"name_qualified\": " << "\"" << tidy_up_string(v.name_qualified()) << "\"" << ", "
      << "\"name_tree_qualified\": " << "\"" << tidy_up_string(v.name_tree_qualified()) << "\"" << ", "
      << "\"name_tree_identifiable\": " << "\"" << tidy_up_string(v.name_tree_identifiable()) << "\"" << ", "
      << "\"streaming_properties\": " << v.streaming_properties() << ", "
      << "\"is_simple_type\": " << v.is_simple_type() << ", "
      << "\"requires_hashing_helper\": " << v.requires_hashing_helper() << ", "
      << "\"is_circular_dependency\": " << v.is_circular_dependency() << ", "
      << "\"is_pointer\": " << v.is_pointer()
      << " }";
    return(s);
}

}
