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
#include "dogen/formatters/io/code_generation_marker_property_sheet_io.hpp"
#include "dogen/formatters/io/general_property_sheet_io.hpp"


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
namespace formatters {

std::ostream& operator<<(std::ostream& s, const general_property_sheet& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::formatters::general_property_sheet\"" << ", "
      << "\"enabled\": " << v.enabled() << ", "
      << "\"generate_preamble\": " << v.generate_preamble() << ", "
      << "\"copyright\": " << v.copyright() << ", "
      << "\"licence_name\": " << "\"" << tidy_up_string(v.licence_name()) << "\"" << ", "
      << "\"modeline_group_name\": " << "\"" << tidy_up_string(v.modeline_group_name()) << "\"" << ", "
      << "\"code_generation_marker\": " << v.code_generation_marker() << ", "
      << "\"feature_directory_name\": " << "\"" << tidy_up_string(v.feature_directory_name()) << "\"" << ", "
      << "\"enable_facet_directories\": " << v.enable_facet_directories() << ", "
      << "\"facet_directory_name\": " << "\"" << tidy_up_string(v.facet_directory_name()) << "\"" << ", "
      << "\"facet_postfix\": " << "\"" << tidy_up_string(v.facet_postfix()) << "\"" << ", "
      << "\"overwrite\": " << v.overwrite() << ", "
      << "\"file_name\": " << "\"" << tidy_up_string(v.file_name()) << "\"" << ", "
      << "\"file_postfix\": " << "\"" << tidy_up_string(v.file_postfix()) << "\"" << ", "
      << "\"extension\": " << "\"" << tidy_up_string(v.extension()) << "\"" << ", "
      << "\"enable_unique_file_names\": " << v.enable_unique_file_names()
      << " }";
    return(s);
}

} }