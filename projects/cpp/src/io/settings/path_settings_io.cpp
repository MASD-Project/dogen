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
#include <ostream>
#include <boost/io/ios_state.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/cpp/io/formatters/file_types_io.hpp"
#include "dogen/cpp/io/settings/path_settings_io.hpp"


inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    return s;
}

namespace dogen {
namespace cpp {
namespace settings {

std::ostream& operator<<(std::ostream& s, const path_settings& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::cpp::settings::path_settings\"" << ", "
      << "\"split_project\": " << v.split_project() << ", "
      << "\"file_type\": " << v.file_type() << ", "
      << "\"facet_directory\": " << "\"" << tidy_up_string(v.facet_directory()) << "\"" << ", "
      << "\"extension\": " << "\"" << tidy_up_string(v.extension()) << "\"" << ", "
      << "\"facet_postfix\": " << "\"" << tidy_up_string(v.facet_postfix()) << "\"" << ", "
      << "\"formatter_postfix\": " << "\"" << tidy_up_string(v.formatter_postfix()) << "\"" << ", "
      << "\"project_directory_path\": " << "\"" << v.project_directory_path().generic_string() << "\"" << ", "
      << "\"source_directory_path\": " << "\"" << v.source_directory_path().generic_string() << "\"" << ", "
      << "\"include_directory_path\": " << "\"" << v.include_directory_path().generic_string() << "\"" << ", "
      << "\"include_directory_name\": " << "\"" << tidy_up_string(v.include_directory_name()) << "\"" << ", "
      << "\"source_directory_name\": " << "\"" << tidy_up_string(v.source_directory_name()) << "\"" << ", "
      << "\"disable_facet_directories\": " << v.disable_facet_directories()
      << " }";
    return(s);
}

} } }