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
#include "dogen.coding/test_data/helpers/mapping_value_td.hpp"
#include "dogen.coding/test_data/helpers/mapping_actions_td.hpp"

namespace {

dogen::coding::helpers::mapping_actions
create_dogen_coding_helpers_mapping_actions(const unsigned int position) {
    return dogen::coding::helpers::mapping_actions_generator::create(position);
}

dogen::coding::meta_model::name
create_dogen_coding_meta_model_name(const unsigned int position) {
    return dogen::coding::meta_model::name_generator::create(position);
}

boost::optional<dogen::coding::meta_model::name>
create_boost_optional_dogen_coding_meta_model_name(unsigned int position) {
    boost::optional<dogen::coding::meta_model::name> r(
        create_dogen_coding_meta_model_name(position));
    return r;
}

}

namespace dogen::coding::helpers {

mapping_value_generator::mapping_value_generator() : position_(0) { }

void mapping_value_generator::
populate(const unsigned int position, result_type& v) {
    v.mapping_action(create_dogen_coding_helpers_mapping_actions(position + 0));
    v.default_name(create_boost_optional_dogen_coding_meta_model_name(position + 1));
}

mapping_value_generator::result_type
mapping_value_generator::create(const unsigned int position) {
    mapping_value r;
    mapping_value_generator::populate(position, r);
    return r;
}

mapping_value_generator::result_type*
mapping_value_generator::create_ptr(const unsigned int position) {
    mapping_value* p = new mapping_value();
    mapping_value_generator::populate(position, *p);
    return p;
}

mapping_value_generator::result_type
mapping_value_generator::operator()() {
    return create(position_++);
}

}
