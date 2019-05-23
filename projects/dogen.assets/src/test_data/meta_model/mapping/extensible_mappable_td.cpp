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
#include "dogen.assets/test_data/meta_model/element_td.hpp"
#include "dogen.assets/test_data/meta_model/mapping/destination_td.hpp"
#include "dogen.assets/test_data/meta_model/mapping/extensible_mappable_td.hpp"

namespace {

dogen::assets::meta_model::mapping::destination
create_dogen_assets_meta_model_mapping_destination(const unsigned int position) {
    return dogen::assets::meta_model::mapping::destination_generator::create(position);
}

std::list<dogen::assets::meta_model::mapping::destination> create_std_list_dogen_assets_meta_model_mapping_destination(unsigned int position) {
    std::list<dogen::assets::meta_model::mapping::destination> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_assets_meta_model_mapping_destination(position + i));
    }
    return r;
}

}

namespace dogen::assets::meta_model::mapping {

extensible_mappable_generator::extensible_mappable_generator() : position_(0) { }

void extensible_mappable_generator::
populate(const unsigned int position, result_type& v) {
    dogen::assets::meta_model::element_generator::populate(position, v);
    v.destinations(create_std_list_dogen_assets_meta_model_mapping_destination(position + 0));
}

extensible_mappable_generator::result_type
extensible_mappable_generator::create(const unsigned int position) {
    extensible_mappable r;
    extensible_mappable_generator::populate(position, r);
    return r;
}

extensible_mappable_generator::result_type*
extensible_mappable_generator::create_ptr(const unsigned int position) {
    extensible_mappable* p = new extensible_mappable();
    extensible_mappable_generator::populate(position, *p);
    return p;
}

extensible_mappable_generator::result_type
extensible_mappable_generator::operator()() {
    return create(position_++);
}

}
