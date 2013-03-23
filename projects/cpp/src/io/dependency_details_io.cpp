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
#include <boost/io/ios_state.hpp>
#include <ostream>
#include "dogen/cpp/io/dependency_details_io.hpp"
#include "dogen/sml/io/qname_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_set<dogen::sml::qname>& v) {
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

std::ostream& operator<<(std::ostream& s, const dependency_details& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::dependency_details\"" << ", "
      << "\"names\": " << v.names() << ", "
      << "\"forward_decls\": " << v.forward_decls() << ", "
      << "\"keys\": " << v.keys() << ", "
      << "\"leaves\": " << v.leaves() << ", "
      << "\"has_std_string\": " << v.has_std_string() << ", "
      << "\"has_variant\": " << v.has_variant() << ", "
      << "\"is_parent_or_child\": " << v.is_parent_or_child() << ", "
      << "\"requires_stream_manipulators\": " << v.requires_stream_manipulators()
      << " }";
    return(s);
}

} }