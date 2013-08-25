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
#include "dogen/om/test_data/cpp_include_directive_td.hpp"
#include "dogen/om/test_data/cpp_include_types_td.hpp"

namespace {

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

dogen::om::cpp_include_types
create_dogen_om_cpp_include_types(const unsigned int position) {
    return dogen::om::cpp_include_types_generator::create(position);
}

}

namespace dogen {
namespace om {

cpp_include_directive_generator::cpp_include_directive_generator() : position_(0) { }

void cpp_include_directive_generator::
populate(const unsigned int position, result_type& v) {
    dogen::om::cpp_feature_generator::populate(position, v);
    v.relative_path(create_boost_filesystem_path(position + 0));
    v.type(create_dogen_om_cpp_include_types(position + 1));
}

cpp_include_directive_generator::result_type
cpp_include_directive_generator::create(const unsigned int position) {
    cpp_include_directive r;
    cpp_include_directive_generator::populate(position, r);
    return r;
}
cpp_include_directive_generator::result_type*
cpp_include_directive_generator::create_ptr(const unsigned int position) {
    cpp_include_directive* p = new cpp_include_directive();
    cpp_include_directive_generator::populate(position, *p);
    return p;
}

cpp_include_directive_generator::result_type
cpp_include_directive_generator::operator()() {
    return create(position_++);
}

} }
