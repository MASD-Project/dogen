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
#include "masd.dogen.coding/test_data/meta_model/element_td.hpp"
#include "masd.dogen.generation.cpp/test_data/fabric/odb_targets_td.hpp"
#include "masd.dogen.generation.cpp/test_data/fabric/msbuild_targets_td.hpp"

namespace {

masd::dogen::generation::cpp::fabric::odb_targets
create_masd_dogen_generation_cpp_fabric_odb_targets(const unsigned int position) {
    return masd::dogen::generation::cpp::fabric::odb_targets_generator::create(position);
}

}

namespace masd::dogen::generation::cpp::fabric {

msbuild_targets_generator::msbuild_targets_generator() : position_(0) { }

void msbuild_targets_generator::
populate(const unsigned int position, result_type& v) {
    masd::dogen::coding::meta_model::element_generator::populate(position, v);
    v.odb_targets(create_masd_dogen_generation_cpp_fabric_odb_targets(position + 0));
}

msbuild_targets_generator::result_type
msbuild_targets_generator::create(const unsigned int position) {
    msbuild_targets r;
    msbuild_targets_generator::populate(position, r);
    return r;
}

msbuild_targets_generator::result_type*
msbuild_targets_generator::create_ptr(const unsigned int position) {
    msbuild_targets* p = new msbuild_targets();
    msbuild_targets_generator::populate(position, *p);
    return p;
}

msbuild_targets_generator::result_type
msbuild_targets_generator::operator()() {
    return create(position_++);
}

}
