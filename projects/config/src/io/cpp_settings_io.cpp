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
#include "dogen/config/io/cpp_facet_types_io.hpp"
#include "dogen/config/io/cpp_settings_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::set<dogen::config::cpp_facet_types>& v) {
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
namespace config {

std::ostream& operator<<(std::ostream& s, const cpp_settings& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::config::cpp_settings\"" << ", "
      << "\"verbose\": " << v.verbose() << ", "
      << "\"split_project\": " << v.split_project() << ", "
      << "\"project_directory\": " << "\"" << v.project_directory().generic_string() << "\"" << ", "
      << "\"source_directory\": " << "\"" << v.source_directory().generic_string() << "\"" << ", "
      << "\"include_directory\": " << "\"" << v.include_directory().generic_string() << "\"" << ", "
      << "\"disable_backend\": " << v.disable_backend() << ", "
      << "\"disable_cmakelists\": " << v.disable_cmakelists() << ", "
      << "\"enabled_facets\": " << v.enabled_facets() << ", "
      << "\"header_extension\": " << "\"" << tidy_up_string(v.header_extension()) << "\"" << ", "
      << "\"source_extension\": " << "\"" << tidy_up_string(v.source_extension()) << "\"" << ", "
      << "\"disable_complete_constructor\": " << v.disable_complete_constructor() << ", "
      << "\"disable_facet_includers\": " << v.disable_facet_includers() << ", "
      << "\"disable_facet_folders\": " << v.disable_facet_folders() << ", "
      << "\"disable_unique_file_names\": " << v.disable_unique_file_names() << ", "
      << "\"domain_facet_folder\": " << "\"" << tidy_up_string(v.domain_facet_folder()) << "\"" << ", "
      << "\"hash_facet_folder\": " << "\"" << tidy_up_string(v.hash_facet_folder()) << "\"" << ", "
      << "\"io_facet_folder\": " << "\"" << tidy_up_string(v.io_facet_folder()) << "\"" << ", "
      << "\"serialization_facet_folder\": " << "\"" << tidy_up_string(v.serialization_facet_folder()) << "\"" << ", "
      << "\"test_data_facet_folder\": " << "\"" << tidy_up_string(v.test_data_facet_folder()) << "\"" << ", "
      << "\"odb_facet_folder\": " << "\"" << tidy_up_string(v.odb_facet_folder()) << "\"" << ", "
      << "\"disable_xml_serialization\": " << v.disable_xml_serialization() << ", "
      << "\"use_integrated_io\": " << v.use_integrated_io()
      << " }";
    return(s);
}

} }