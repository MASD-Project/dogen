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
#include "dogen/cpp/test_data/includes_td.hpp"
#include "dogen/cpp/test_data/path_spec_details_td.hpp"

namespace {

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

dogen::cpp::includes
create_dogen_cpp_includes(const unsigned int position) {
    return dogen::cpp::includes_generator::create(position);
}

}

namespace dogen {
namespace cpp {

path_spec_details_generator::path_spec_details_generator() : position_(0) { }

void path_spec_details_generator::
populate(const unsigned int position, result_type& v) {
    v.relative_path(create_boost_filesystem_path(position + 0));
    v.includes(create_dogen_cpp_includes(position + 1));
}

path_spec_details_generator::result_type
path_spec_details_generator::create(const unsigned int position) {
    path_spec_details r;
    path_spec_details_generator::populate(position, r);
    return r;
}
path_spec_details_generator::result_type*
path_spec_details_generator::create_ptr(const unsigned int position) {
    path_spec_details* p = new path_spec_details();
    path_spec_details_generator::populate(position, *p);
    return p;
}

path_spec_details_generator::result_type
path_spec_details_generator::operator()() {
    return create(position_++);
}

} }
