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
#include "dogen/stitch/test_data/stitching_settings_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

boost::optional<boost::filesystem::path>
create_boost_optional_boost_filesystem_path(unsigned int position) {
    boost::optional<boost::filesystem::path> r(
        create_boost_filesystem_path(position));
    return r;
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace dogen {
namespace stitch {

stitching_settings_generator::stitching_settings_generator() : position_(0) { }

void stitching_settings_generator::
populate(const unsigned int position, result_type& v) {
    v.stream_variable_name(create_std_string(position + 0));
    v.template_path(create_boost_optional_boost_filesystem_path(position + 1));
    v.output_path(create_boost_optional_boost_filesystem_path(position + 2));
    v.relative_output_directory(create_boost_optional_boost_filesystem_path(position + 3));
    v.inclusion_dependencies(create_std_list_std_string(position + 4));
    v.containing_namespaces(create_std_list_std_string(position + 5));
}

stitching_settings_generator::result_type
stitching_settings_generator::create(const unsigned int position) {
    stitching_settings r;
    stitching_settings_generator::populate(position, r);
    return r;
}
stitching_settings_generator::result_type*
stitching_settings_generator::create_ptr(const unsigned int position) {
    stitching_settings* p = new stitching_settings();
    stitching_settings_generator::populate(position, *p);
    return p;
}

stitching_settings_generator::result_type
stitching_settings_generator::operator()() {
    return create(position_++);
}

} }
