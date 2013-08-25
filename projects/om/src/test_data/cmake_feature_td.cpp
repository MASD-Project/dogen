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
#include "dogen/om/test_data/cmake_add_library_td.hpp"
#include "dogen/om/test_data/cmake_feature_td.hpp"
#include "dogen/om/test_data/cmake_install_td.hpp"
#include "dogen/om/test_data/cmake_set_target_properties_td.hpp"



namespace dogen {
namespace om {


void cmake_feature_generator::
populate(const unsigned int /*position*/, result_type& /*v*/) {
}

cmake_feature_generator::result_type*
cmake_feature_generator::create_ptr(const unsigned int position) {
    if ((position % 2) == 0)
        return dogen::om::cmake_set_target_properties_generator::create_ptr(position);
    if ((position % 2) == 1)
        return dogen::om::cmake_install_generator::create_ptr(position);
    return dogen::om::cmake_add_library_generator::create_ptr(position);
}


} }
