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
#include "dogen.assets/test_data/meta_model/extraction_properties_td.hpp"

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

std::unordered_set<std::string> create_std_unordered_set_std_string(unsigned int position) {
    std::unordered_set<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_std_string(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

}

namespace dogen::assets::meta_model {

extraction_properties_generator::extraction_properties_generator() : position_(0) { }

void extraction_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.cpp_headers_output_directory(create_boost_filesystem_path(position + 0));
    v.enabled_backends(create_std_unordered_set_std_string(position + 1));
    v.enable_backend_directories(create_bool(position + 2));
}

extraction_properties_generator::result_type
extraction_properties_generator::create(const unsigned int position) {
    extraction_properties r;
    extraction_properties_generator::populate(position, r);
    return r;
}

extraction_properties_generator::result_type*
extraction_properties_generator::create_ptr(const unsigned int position) {
    extraction_properties* p = new extraction_properties();
    extraction_properties_generator::populate(position, *p);
    return p;
}

extraction_properties_generator::result_type
extraction_properties_generator::operator()() {
    return create(position_++);
}

}
