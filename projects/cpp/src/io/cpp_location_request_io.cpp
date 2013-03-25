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
#include "dogen/config/io/cpp_facet_types_io.hpp"
#include "dogen/cpp/io/cpp_aspect_types_io.hpp"
#include "dogen/cpp/io/cpp_location_request_io.hpp"
#include "dogen/cpp/io/file_types_io.hpp"


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
namespace cpp {

std::ostream& operator<<(std::ostream& s, const cpp_location_request& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::cpp_location_request\"" << ", "
      << "\"facet_type\": " << v.facet_type() << ", "
      << "\"file_type\": " << v.file_type() << ", "
      << "\"aspect_type\": " << v.aspect_type() << ", "
      << "\"model_name\": " << "\"" << tidy_up_string(v.model_name()) << "\"" << ", "
      << "\"external_package_path\": " << v.external_package_path() << ", "
      << "\"package_path\": " << v.package_path() << ", "
      << "\"file_name\": " << "\"" << tidy_up_string(v.file_name()) << "\""
      << " }";
    return(s);
}

} }