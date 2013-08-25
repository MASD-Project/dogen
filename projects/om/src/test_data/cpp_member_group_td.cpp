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
#include "dogen/om/test_data/cpp_access_specifier_types_td.hpp"
#include "dogen/om/test_data/cpp_feature_td.hpp"
#include "dogen/om/test_data/cpp_member_group_td.hpp"

namespace {

dogen::om::cpp_access_specifier_types
create_dogen_om_cpp_access_specifier_types(const unsigned int position) {
    return dogen::om::cpp_access_specifier_types_generator::create(position);
}

dogen::om::cpp_feature*
create_dogen_om_cpp_feature_ptr(const unsigned int position) {
    return dogen::om::cpp_feature_generator::create_ptr(position);
}

boost::shared_ptr<dogen::om::cpp_feature>
create_boost_shared_ptr_dogen_om_cpp_feature(unsigned int position) {
    boost::shared_ptr<dogen::om::cpp_feature> r(
        create_dogen_om_cpp_feature_ptr(position));
    return r;
}

std::list<boost::shared_ptr<dogen::om::cpp_feature> > create_std_list_boost_shared_ptr_dogen_om_cpp_feature_(unsigned int position) {
    std::list<boost::shared_ptr<dogen::om::cpp_feature> > r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_boost_shared_ptr_dogen_om_cpp_feature(position + i));
    }
    return r;
}

}

namespace dogen {
namespace om {

cpp_member_group_generator::cpp_member_group_generator() : position_(0) { }

void cpp_member_group_generator::
populate(const unsigned int position, result_type& v) {
    v.type(create_dogen_om_cpp_access_specifier_types(position + 0));
    v.features(create_std_list_boost_shared_ptr_dogen_om_cpp_feature_(position + 1));
}

cpp_member_group_generator::result_type
cpp_member_group_generator::create(const unsigned int position) {
    cpp_member_group r;
    cpp_member_group_generator::populate(position, r);
    return r;
}
cpp_member_group_generator::result_type*
cpp_member_group_generator::create_ptr(const unsigned int position) {
    cpp_member_group* p = new cpp_member_group();
    cpp_member_group_generator::populate(position, *p);
    return p;
}

cpp_member_group_generator::result_type
cpp_member_group_generator::operator()() {
    return create(position_++);
}

} }
