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
#include "dogen/cpp/io/class_info_io.hpp"
#include "dogen/cpp/io/class_types_io.hpp"
#include "dogen/cpp/io/parent_info_io.hpp"
#include "dogen/cpp/io/property_info_io.hpp"


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

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::cpp::property_info>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::cpp::parent_info>& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::pair<std::string, std::string>& v) {
    s << "{ " << "\"__type__\": " << "\"std::pair\"" << ", ";

    s << "\"first\": " << "\"" << tidy_up_string(v.first) << "\"" << ", ";
    s << "\"second\": " << "\"" << tidy_up_string(v.second) << "\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<std::pair<std::string, std::string> >& v) {
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

std::ostream& operator<<(std::ostream& s, const class_info& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::class_info\"" << ", "
      << "\"name\": " << "\"" << tidy_up_string(v.name()) << "\"" << ", "
      << "\"namespaces\": " << v.namespaces() << ", "
      << "\"properties\": " << v.properties() << ", "
      << "\"all_properties\": " << v.all_properties() << ", "
      << "\"has_primitive_properties\": " << v.has_primitive_properties() << ", "
      << "\"requires_stream_manipulators\": " << v.requires_stream_manipulators() << ", "
      << "\"requires_manual_move_constructor\": " << v.requires_manual_move_constructor() << ", "
      << "\"requires_manual_default_constructor\": " << v.requires_manual_default_constructor() << ", "
      << "\"parents\": " << v.parents() << ", "
      << "\"is_parent\": " << v.is_parent() << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(v.documentation()) << "\"" << ", "
      << "\"original_parent_name\": " << "\"" << tidy_up_string(v.original_parent_name()) << "\"" << ", "
      << "\"original_parent_name_qualified\": " << "\"" << tidy_up_string(v.original_parent_name_qualified()) << "\"" << ", "
      << "\"leaves\": " << v.leaves() << ", "
      << "\"implementation_specific_parameters\": " << v.implementation_specific_parameters() << ", "
      << "\"is_comparable\": " << v.is_comparable() << ", "
      << "\"is_visitable\": " << v.is_visitable() << ", "
      << "\"is_immutable\": " << v.is_immutable() << ", "
      << "\"is_original_parent_visitable\": " << v.is_original_parent_visitable() << ", "
      << "\"class_type\": " << v.class_type()
      << " }";
    return(s);
}

} }