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
#include "dogen/om/test_data/cpp_feature_td.hpp"
#include "dogen/om/test_data/cpp_typedef_td.hpp"
#include "dogen/om/test_data/cpp_typeref_td.hpp"
#include "dogen/om/test_data/doxygen_command_td.hpp"

namespace {

dogen::om::doxygen_command
create_dogen_om_doxygen_command(const unsigned int position) {
    return dogen::om::doxygen_command_generator::create(position);
}

std::list<dogen::om::doxygen_command> create_std_list_dogen_om_doxygen_command(unsigned int position) {
    std::list<dogen::om::doxygen_command> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_om_doxygen_command(position + i));
    }
    return r;
}

dogen::om::cpp_typeref
create_dogen_om_cpp_typeref(const unsigned int position) {
    return dogen::om::cpp_typeref_generator::create(position);
}

}

namespace dogen {
namespace om {

cpp_typedef_generator::cpp_typedef_generator() : position_(0) { }

void cpp_typedef_generator::
populate(const unsigned int position, result_type& v) {
    dogen::om::cpp_feature_generator::populate(position, v);
    v.commands(create_std_list_dogen_om_doxygen_command(position + 0));
    v.type(create_dogen_om_cpp_typeref(position + 1));
}

cpp_typedef_generator::result_type
cpp_typedef_generator::create(const unsigned int position) {
    cpp_typedef r;
    cpp_typedef_generator::populate(position, r);
    return r;
}
cpp_typedef_generator::result_type*
cpp_typedef_generator::create_ptr(const unsigned int position) {
    cpp_typedef* p = new cpp_typedef();
    cpp_typedef_generator::populate(position, *p);
    return p;
}

cpp_typedef_generator::result_type
cpp_typedef_generator::operator()() {
    return create(position_++);
}

} }
