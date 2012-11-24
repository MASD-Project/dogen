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
#include "dogen/sml/io/category_types_io.hpp"
#include "dogen/sml/io/pod_io.hpp"
#include "dogen/sml/io/pod_types_io.hpp"
#include "dogen/sml/io/property_io.hpp"
#include "dogen/sml/io/qualified_name_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<dogen::sml::property>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::sml::qualified_name>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<empty>\"";
    s<< " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::sml::qualified_name>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace sml {

std::ostream& operator<<(std::ostream& s, const pod& v) {
    boost::io::ios_flags_saver ifs(s);
    s << std::boolalpha;

    s << " { "
      << "\"__type__\": " << "\"pod\"" << ", "
      << "\"name\": " << v.name() << ", "
      << "\"properties\": " << v.properties() << ", "
      << "\"parent_name\": " << v.parent_name() << ", "
      << "\"original_parent_name\": " << v.original_parent_name() << ", "
      << "\"leaves\": " << v.leaves() << ", "
      << "\"generate\": " << v.generate() << ", "
      << "\"is_parent\": " << v.is_parent() << ", "
      << "\"category_type\": " << v.category_type() << ", "
      << "\"pod_type\": " << v.pod_type() << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(v.documentation()) << "\"" << ", "
      << "\"number_of_type_arguments\": " << v.number_of_type_arguments()
      << " }";
    return(s);
}

} }