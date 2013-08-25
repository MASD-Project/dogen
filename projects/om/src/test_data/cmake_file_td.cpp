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
#include "dogen/om/test_data/cmake_feature_td.hpp"
#include "dogen/om/test_data/cmake_file_td.hpp"
#include "dogen/om/test_data/text_file_td.hpp"

namespace {

dogen::om::cmake_feature*
create_dogen_om_cmake_feature_ptr(const unsigned int position) {
    return dogen::om::cmake_feature_generator::create_ptr(position);
}

boost::shared_ptr<dogen::om::cmake_feature>
create_boost_shared_ptr_dogen_om_cmake_feature(unsigned int position) {
    boost::shared_ptr<dogen::om::cmake_feature> r(
        create_dogen_om_cmake_feature_ptr(position));
    return r;
}

std::list<boost::shared_ptr<dogen::om::cmake_feature> > create_std_list_boost_shared_ptr_dogen_om_cmake_feature_(unsigned int position) {
    std::list<boost::shared_ptr<dogen::om::cmake_feature> > r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_boost_shared_ptr_dogen_om_cmake_feature(position + i));
    }
    return r;
}

}

namespace dogen {
namespace om {

cmake_file_generator::cmake_file_generator() : position_(0) { }

void cmake_file_generator::
populate(const unsigned int position, result_type& v) {
    dogen::om::text_file_generator::populate(position, v);
    v.features(create_std_list_boost_shared_ptr_dogen_om_cmake_feature_(position + 0));
}

cmake_file_generator::result_type
cmake_file_generator::create(const unsigned int position) {
    cmake_file r;
    cmake_file_generator::populate(position, r);
    return r;
}
cmake_file_generator::result_type*
cmake_file_generator::create_ptr(const unsigned int position) {
    cmake_file* p = new cmake_file();
    cmake_file_generator::populate(position, *p);
    return p;
}

cmake_file_generator::result_type
cmake_file_generator::operator()() {
    return create(position_++);
}

} }
