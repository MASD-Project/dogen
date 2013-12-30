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
#include "dogen/om/test_data/file_td.hpp"

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
    return (position % 2) == 0;
}

}

namespace dogen {
namespace om {

file_generator::file_generator() : position_(0) { }

void file_generator::
populate(const unsigned int position, result_type& v) {
    v.relative_path(create_boost_filesystem_path(position + 0));
    v.absolute_path(create_boost_filesystem_path(position + 1));
    v.contents(create_std_string(position + 2));
    v.overwrite(create_bool(position + 3));
}

file_generator::result_type
file_generator::create(const unsigned int position) {
    file r;
    file_generator::populate(position, r);
    return r;
}
file_generator::result_type*
file_generator::create_ptr(const unsigned int position) {
    file* p = new file();
    file_generator::populate(position, *p);
    return p;
}

file_generator::result_type
file_generator::operator()() {
    return create(position_++);
}

} }
