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
#include "dogen/quilt.cpp/io/formatters/file_types_io.hpp"
#include "dogen/quilt.cpp/io/annotations/path_annotations_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace quilt {
namespace cpp {
namespace annotations {

std::ostream& operator<<(std::ostream& s, const path_annotations& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::annotations::path_annotations\"" << ", "
      << "\"file_type\": " << v.file_type() << ", "
      << "\"facet_directory\": " << "\"" << tidy_up_string(v.facet_directory()) << "\"" << ", "
      << "\"facet_postfix\": " << "\"" << tidy_up_string(v.facet_postfix()) << "\"" << ", "
      << "\"formatter_postfix\": " << "\"" << tidy_up_string(v.formatter_postfix()) << "\"" << ", "
      << "\"include_directory_name\": " << "\"" << tidy_up_string(v.include_directory_name()) << "\"" << ", "
      << "\"source_directory_name\": " << "\"" << tidy_up_string(v.source_directory_name()) << "\"" << ", "
      << "\"disable_facet_directories\": " << v.disable_facet_directories() << ", "
      << "\"header_file_extension\": " << "\"" << tidy_up_string(v.header_file_extension()) << "\"" << ", "
      << "\"implementation_file_extension\": " << "\"" << tidy_up_string(v.implementation_file_extension()) << "\""
      << " }";
    return(s);
}

} } } }
