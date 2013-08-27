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
#include "dogen/om_formatters/test_data/formatted_file_td.hpp"

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

}

namespace dogen {
namespace om_formatters {

formatted_file_generator::formatted_file_generator() : position_(0) { }

void formatted_file_generator::
populate(const unsigned int position, result_type& v) {
    v.full_path(create_boost_filesystem_path(position + 0));
    v.contents(create_std_string(position + 1));
}

formatted_file_generator::result_type
formatted_file_generator::create(const unsigned int position) {
    formatted_file r;
    formatted_file_generator::populate(position, r);
    return r;
}
formatted_file_generator::result_type*
formatted_file_generator::create_ptr(const unsigned int position) {
    formatted_file* p = new formatted_file();
    formatted_file_generator::populate(position, *p);
    return p;
}

formatted_file_generator::result_type
formatted_file_generator::operator()() {
    return create(position_++);
}

} }
