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
#include "masd.dogen.generation.csharp/test_data/fabric/assembly_info_td.hpp"

namespace masd::dogen::generation::csharp::fabric {

assembly_info_generator::assembly_info_generator() : position_(0) { }

void assembly_info_generator::
populate(const unsigned int position, result_type& v) {
    masd::dogen::coding::meta_model::element_generator::populate(position, v);
}

assembly_info_generator::result_type
assembly_info_generator::create(const unsigned int position) {
    assembly_info r;
    assembly_info_generator::populate(position, r);
    return r;
}

assembly_info_generator::result_type*
assembly_info_generator::create_ptr(const unsigned int position) {
    assembly_info* p = new assembly_info();
    assembly_info_generator::populate(position, *p);
    return p;
}

assembly_info_generator::result_type
assembly_info_generator::operator()() {
    return create(position_++);
}

}
