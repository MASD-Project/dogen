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
#include <sstream>
#include "dogen/config/test_data/cpp_facet_types_td.hpp"
#include "dogen/config/test_data/cpp_settings_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

dogen::config::cpp_facet_types
create_dogen_config_cpp_facet_types(const unsigned int position) {
    return dogen::config::cpp_facet_types_generator::create(position);
}

std::set<dogen::config::cpp_facet_types> create_std_set_dogen_config_cpp_facet_types(unsigned int position) {
    std::set<dogen::config::cpp_facet_types> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_dogen_config_cpp_facet_types(position + i));
    }
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace config {

cpp_settings_generator::cpp_settings_generator() : position_(0) { }

void cpp_settings_generator::
populate(const unsigned int position, result_type& v) {
    v.verbose(create_bool(position + 0));
    v.split_project(create_bool(position + 1));
    v.project_directory(create_boost_filesystem_path(position + 2));
    v.source_directory(create_boost_filesystem_path(position + 3));
    v.include_directory(create_boost_filesystem_path(position + 4));
    v.disable_backend(create_bool(position + 5));
    v.disable_cmakelists(create_bool(position + 6));
    v.enabled_facets(create_std_set_dogen_config_cpp_facet_types(position + 7));
    v.header_extension(create_std_string(position + 8));
    v.source_extension(create_std_string(position + 9));
    v.disable_complete_constructor(create_bool(position + 10));
    v.disable_facet_includers(create_bool(position + 11));
    v.disable_facet_folders(create_bool(position + 12));
    v.disable_unique_file_names(create_bool(position + 13));
    v.domain_facet_folder(create_std_string(position + 14));
    v.hash_facet_folder(create_std_string(position + 15));
    v.io_facet_folder(create_std_string(position + 16));
    v.serialization_facet_folder(create_std_string(position + 17));
    v.test_data_facet_folder(create_std_string(position + 18));
    v.odb_facet_folder(create_std_string(position + 19));
    v.disable_xml_serialization(create_bool(position + 20));
    v.use_integrated_io(create_bool(position + 21));
    v.disable_eos_serialization(create_bool(position + 22));
}

cpp_settings_generator::result_type
cpp_settings_generator::create(const unsigned int position) {
    cpp_settings r;
    cpp_settings_generator::populate(position, r);
    return r;
}
cpp_settings_generator::result_type*
cpp_settings_generator::create_ptr(const unsigned int position) {
    cpp_settings* p = new cpp_settings();
    cpp_settings_generator::populate(position, *p);
    return p;
}

cpp_settings_generator::result_type
cpp_settings_generator::operator()() {
    return create(position_++);
}

} }
