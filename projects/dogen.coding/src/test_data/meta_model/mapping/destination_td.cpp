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
#include <sstream>
#include "dogen.coding/test_data/meta_model/mapping/action_td.hpp"
#include "dogen.coding/test_data/meta_model/mapping/destination_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::coding::meta_model::mapping::action
create_dogen_coding_meta_model_mapping_action(const unsigned int position) {
    return dogen::coding::meta_model::mapping::action_generator::create(position);
}

}

namespace dogen::coding::meta_model::mapping {

destination_generator::destination_generator() : position_(0) { }

void destination_generator::
populate(const unsigned int position, result_type& v) {
    v.element_id(create_std_string(position + 0));
    v.action(create_dogen_coding_meta_model_mapping_action(position + 1));
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
