/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#include "dogen.logical/test_data/helpers/mapping_value_td.hpp"
#include "dogen.logical/test_data/helpers/mapping_actions_td.hpp"
#include "dogen.identification/test_data/entities/logical_name_td.hpp"

namespace {

dogen::logical::helpers::mapping_actions
create_dogen_logical_helpers_mapping_actions(const unsigned int position) {
    return dogen::logical::helpers::mapping_actions_generator::create(position);
}

dogen::identification::entities::logical_name
create_dogen_identification_entities_logical_name(const unsigned int position) {
    return dogen::identification::entities::logical_name_generator::create(position);
}

boost::optional<dogen::identification::entities::logical_name>
create_boost_optional_dogen_identification_entities_logical_name(unsigned int position) {
    boost::optional<dogen::identification::entities::logical_name> r(
        create_dogen_identification_entities_logical_name(position));
    return r;
}

}

namespace dogen::logical::helpers {

mapping_value_generator::mapping_value_generator() : position_(0) { }

void mapping_value_generator::
populate(const unsigned int position, result_type& v) {
    v.mapping_action(create_dogen_logical_helpers_mapping_actions(position + 0));
    v.default_name(create_boost_optional_dogen_identification_entities_logical_name(position + 1));
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
