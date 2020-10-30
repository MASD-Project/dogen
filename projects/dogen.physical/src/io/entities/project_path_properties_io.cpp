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
#include "dogen.physical/io/entities/project_path_properties_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace dogen::physical::entities {

std::ostream& operator<<(std::ostream& s, const project_path_properties& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::physical::entities::project_path_properties\"" << ", "
      << "\"include_directory_name\": " << "\"" << tidy_up_string(v.include_directory_name()) << "\"" << ", "
      << "\"source_directory_name\": " << "\"" << tidy_up_string(v.source_directory_name()) << "\"" << ", "
      << "\"disable_facet_directories\": " << v.disable_facet_directories() << ", "
      << "\"header_file_extension\": " << "\"" << tidy_up_string(v.header_file_extension()) << "\"" << ", "
      << "\"implementation_file_extension\": " << "\"" << tidy_up_string(v.implementation_file_extension()) << "\"" << ", "
      << "\"tests_directory_name\": " << "\"" << tidy_up_string(v.tests_directory_name()) << "\"" << ", "
      << "\"templates_directory_name\": " << "\"" << tidy_up_string(v.templates_directory_name()) << "\"" << ", "
      << "\"templates_file_extension\": " << "\"" << tidy_up_string(v.templates_file_extension()) << "\"" << ", "
      << "\"enable_unique_file_names\": " << v.enable_unique_file_names() << ", "
      << "\"headers_output_directory\": " << "\"" << tidy_up_string(v.headers_output_directory()) << "\"" << ", "
      << "\"enable_backend_directories\": " << v.enable_backend_directories() << ", "
      << "\"implementation_directory_full_path\": " << "\"" << v.implementation_directory_full_path().generic_string() << "\"" << ", "
      << "\"include_directory_full_path\": " << "\"" << v.include_directory_full_path().generic_string() << "\"" << ", "
      << "\"templates_directory_full_path\": " << "\"" << v.templates_directory_full_path().generic_string() << "\""
      << " }";
    return(s);
}

}
