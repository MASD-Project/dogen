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
#include "dogen/om/test_data/cpp_feature_td.hpp"
#include "dogen/om/test_data/cpp_header_guard_td.hpp"

namespace {

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

cpp_header_guard_generator::cpp_header_guard_generator() : position_(0) { }

void cpp_header_guard_generator::
populate(const unsigned int position, result_type& v) {
    dogen::om::cpp_feature_generator::populate(position, v);
    v.guard_name(create_std_string(position + 0));
    v.use_pragma_once(create_bool(position + 1));
}

cpp_header_guard_generator::result_type
cpp_header_guard_generator::create(const unsigned int position) {
    cpp_header_guard r;
    cpp_header_guard_generator::populate(position, r);
    return r;
}
cpp_header_guard_generator::result_type*
cpp_header_guard_generator::create_ptr(const unsigned int position) {
    cpp_header_guard* p = new cpp_header_guard();
    cpp_header_guard_generator::populate(position, *p);
    return p;
}

cpp_header_guard_generator::result_type
cpp_header_guard_generator::operator()() {
    return create(position_++);
}

} }
