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
#include "dogen/om/test_data/cpp_base_td.hpp"
#include "dogen/om/test_data/cpp_class_td.hpp"
#include "dogen/om/test_data/cpp_feature_td.hpp"
#include "dogen/om/test_data/cpp_member_group_td.hpp"
#include "dogen/om/test_data/cpp_representation_types_td.hpp"
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

dogen::om::cpp_representation_types
create_dogen_om_cpp_representation_types(const unsigned int position) {
    return dogen::om::cpp_representation_types_generator::create(position);
}

dogen::om::cpp_base
create_dogen_om_cpp_base(const unsigned int position) {
    return dogen::om::cpp_base_generator::create(position);
}

std::list<dogen::om::cpp_base> create_std_list_dogen_om_cpp_base(unsigned int position) {
    std::list<dogen::om::cpp_base> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_om_cpp_base(position + i));
    }
    return r;
}

dogen::om::cpp_member_group
create_dogen_om_cpp_member_group(const unsigned int position) {
    return dogen::om::cpp_member_group_generator::create(position);
}

std::list<dogen::om::cpp_member_group> create_std_list_dogen_om_cpp_member_group(unsigned int position) {
    std::list<dogen::om::cpp_member_group> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_om_cpp_member_group(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace om {

cpp_class_generator::cpp_class_generator() : position_(0) { }

void cpp_class_generator::
populate(const unsigned int position, result_type& v) {
    dogen::om::cpp_feature_generator::populate(position, v);
    v.commands(create_std_list_dogen_om_doxygen_command(position + 0));
    v.representation_type(create_dogen_om_cpp_representation_types(position + 1));
    v.bases(create_std_list_dogen_om_cpp_base(position + 2));
    v.members(create_std_list_dogen_om_cpp_member_group(position + 3));
    v.is_final(create_bool(position + 4));
    v.is_friend(create_bool(position + 5));
}

cpp_class_generator::result_type
cpp_class_generator::create(const unsigned int position) {
    cpp_class r;
    cpp_class_generator::populate(position, r);
    return r;
}
cpp_class_generator::result_type*
cpp_class_generator::create_ptr(const unsigned int position) {
    cpp_class* p = new cpp_class();
    cpp_class_generator::populate(position, *p);
    return p;
}

cpp_class_generator::result_type
cpp_class_generator::operator()() {
    return create(position_++);
}

} }
