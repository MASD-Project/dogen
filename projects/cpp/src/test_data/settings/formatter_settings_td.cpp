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
#include "dogen/cpp/test_data/settings/formatter_settings_td.hpp"
#include "dogen/cpp/test_data/settings/inclusion_delimiter_types_td.hpp"
#include "dogen/cpp/test_data/settings/inclusion_td.hpp"

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

dogen::cpp::settings::inclusion_delimiter_types
create_dogen_cpp_settings_inclusion_delimiter_types(const unsigned int position) {
    return dogen::cpp::settings::inclusion_delimiter_types_generator::create(position);
}

dogen::cpp::settings::inclusion
create_dogen_cpp_settings_inclusion(const unsigned int position) {
    return dogen::cpp::settings::inclusion_generator::create(position);
}

std::list<dogen::cpp::settings::inclusion> create_std_list_dogen_cpp_settings_inclusion(unsigned int position) {
    std::list<dogen::cpp::settings::inclusion> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_cpp_settings_inclusion(position + i));
    }
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::set<std::string> create_std_set_std_string(unsigned int position) {
    std::set<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_std_string(position + i));
    }
    return r;
}

}

namespace dogen {
namespace cpp {
namespace settings {

formatter_settings_generator::formatter_settings_generator() : position_(0) { }

void formatter_settings_generator::
populate(const unsigned int position, result_type& v) {
    v.enabled(create_bool(position + 0));
    v.supported(create_bool(position + 1));
    v.file_path(create_boost_filesystem_path(position + 2));
    v.inclusion_required(create_bool(position + 3));
    v.inclusion_path(create_boost_filesystem_path(position + 4));
    v.inclusion_delimiter_type(create_dogen_cpp_settings_inclusion_delimiter_types(position + 5));
    v.inclusion_dependencies(create_std_list_dogen_cpp_settings_inclusion(position + 6));
    v.integrated_facets(create_std_set_std_string(position + 7));
}

formatter_settings_generator::result_type
formatter_settings_generator::create(const unsigned int position) {
    formatter_settings r;
    formatter_settings_generator::populate(position, r);
    return r;
}
formatter_settings_generator::result_type*
formatter_settings_generator::create_ptr(const unsigned int position) {
    formatter_settings* p = new formatter_settings();
    formatter_settings_generator::populate(position, *p);
    return p;
}

formatter_settings_generator::result_type
formatter_settings_generator::operator()() {
    return create(position_++);
}

} } }
