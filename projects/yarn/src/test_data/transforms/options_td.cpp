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
#include <sstream>
#include "dogen/yarn/test_data/transforms/options_td.hpp"

namespace {

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

std::vector<std::string> create_std_vector_std_string(unsigned int position) {
    std::vector<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace dogen {
namespace yarn {
namespace transforms {

options_generator::options_generator() : position_(0) { }

void options_generator::
populate(const unsigned int position, result_type& v) {
    v.log_file(create_boost_filesystem_path(position + 0));
    v.log_level(create_std_string(position + 1));
    v.target(create_boost_filesystem_path(position + 2));
    v.delete_extra_files(create_bool(position + 3));
    v.force_write(create_bool(position + 4));
    v.ignore_patterns(create_std_vector_std_string(position + 5));
    v.output_directory_path(create_boost_filesystem_path(position + 6));
    v.cpp_headers_output_directory_path(create_boost_filesystem_path(position + 7));
    v.compatibility_mode(create_bool(position + 8));
    v.probe_stats(create_bool(position + 9));
    v.probe_stats_disable_guids(create_bool(position + 10));
    v.probe_stats_org_mode(create_bool(position + 11));
    v.probe_all(create_bool(position + 12));
    v.probe_directory(create_boost_filesystem_path(position + 13));
    v.probe_use_short_names(create_bool(position + 14));
}

options_generator::result_type
options_generator::create(const unsigned int position) {
    options r;
    options_generator::populate(position, r);
    return r;
}

options_generator::result_type*
options_generator::create_ptr(const unsigned int position) {
    options* p = new options();
    options_generator::populate(position, *p);
    return p;
}

options_generator::result_type
options_generator::operator()() {
    return create(position_++);
}

} } }
