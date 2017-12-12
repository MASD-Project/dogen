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
#include "dogen/test_models/boost_model/test_data/class_g_td.hpp"

namespace {

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

std::list<boost::filesystem::path> create_std_list_boost_filesystem_path(unsigned int position) {
    std::list<boost::filesystem::path> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_filesystem_path(position + i));
    }
    return r;
}

}

namespace dogen {
namespace test_models {
namespace boost_model {

class_g_generator::class_g_generator() : position_(0) { }

void class_g_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_boost_filesystem_path(position + 0));
    v.prop_1(create_std_list_boost_filesystem_path(position + 1));
}

class_g_generator::result_type
class_g_generator::create(const unsigned int position) {
    class_g r;
    class_g_generator::populate(position, r);
    return r;
}

class_g_generator::result_type*
class_g_generator::create_ptr(const unsigned int position) {
    class_g* p = new class_g();
    class_g_generator::populate(position, *p);
    return p;
}

class_g_generator::result_type
class_g_generator::operator()() {
    return create(position_++);
}

} } }
