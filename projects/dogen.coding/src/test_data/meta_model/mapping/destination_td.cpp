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
#include "dogen.coding/test_data/meta_model/name_td.hpp"
#include "dogen.coding/test_data/meta_model/technical_space_td.hpp"
#include "dogen.coding/test_data/meta_model/mapping/destination_td.hpp"

namespace {

dogen::coding::meta_model::name
create_dogen_coding_meta_model_name(const unsigned int position) {
    return dogen::coding::meta_model::name_generator::create(position);
}

dogen::coding::meta_model::technical_space
create_dogen_coding_meta_model_technical_space(const unsigned int position) {
    return dogen::coding::meta_model::technical_space_generator::create(position);
}

}

namespace dogen::coding::meta_model::mapping {

destination_generator::destination_generator() : position_(0) { }

void destination_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_dogen_coding_meta_model_name(position + 0));
    v.technical_space(create_dogen_coding_meta_model_technical_space(position + 1));
}

destination_generator::result_type
destination_generator::create(const unsigned int position) {
    destination r;
    destination_generator::populate(position, r);
    return r;
}

destination_generator::result_type*
destination_generator::create_ptr(const unsigned int position) {
    destination* p = new destination();
    destination_generator::populate(position, *p);
    return p;
}

destination_generator::result_type
destination_generator::operator()() {
    return create(position_++);
}

}
