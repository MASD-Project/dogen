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
#include "dogen/om/test_data/cmake_set_target_properties_td.hpp"



namespace dogen {
namespace om {

cmake_set_target_properties_generator::cmake_set_target_properties_generator() : position_(0) { }

void cmake_set_target_properties_generator::
populate(const unsigned int position, result_type& v) {
    dogen::om::cmake_feature_generator::populate(position, v);
}

cmake_set_target_properties_generator::result_type
cmake_set_target_properties_generator::create(const unsigned int/*position*/) {
    cmake_set_target_properties r;
    return r;
}
cmake_set_target_properties_generator::result_type*
cmake_set_target_properties_generator::create_ptr(const unsigned int position) {
    cmake_set_target_properties* p = new cmake_set_target_properties();
    cmake_set_target_properties_generator::populate(position, *p);
    return p;
}

cmake_set_target_properties_generator::result_type
cmake_set_target_properties_generator::operator()() {
    return create(position_++);
}

} }
