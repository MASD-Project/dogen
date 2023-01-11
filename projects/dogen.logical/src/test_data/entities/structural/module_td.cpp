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
#include "dogen.logical/test_data/entities/element_td.hpp"
#include "dogen.identification/test_data/entities/logical_id_td.hpp"
#include "dogen.logical/test_data/entities/structural/module_td.hpp"
#include "dogen.logical/test_data/entities/orm/module_properties_td.hpp"

namespace {

dogen::identification::entities::logical_id
create_dogen_identification_entities_logical_id(const unsigned int position) {
    return dogen::identification::entities::logical_id_generator::create(position);
}

std::list<dogen::identification::entities::logical_id> create_std_list_dogen_identification_entities_logical_id(unsigned int position) {
    std::list<dogen::identification::entities::logical_id> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_identification_entities_logical_id(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

dogen::logical::entities::orm::module_properties
create_dogen_logical_entities_orm_module_properties(const unsigned int position) {
    return dogen::logical::entities::orm::module_properties_generator::create(position);
}

boost::optional<dogen::logical::entities::orm::module_properties>
create_boost_optional_dogen_logical_entities_orm_module_properties(unsigned int position) {
    boost::optional<dogen::logical::entities::orm::module_properties> r(
        create_dogen_logical_entities_orm_module_properties(position));
    return r;
}

}

namespace dogen::logical::entities::structural {

module_generator::module_generator() : position_(0) { }

void module_generator::
populate(const unsigned int position, result_type& v) {
    dogen::logical::entities::element_generator::populate(position, v);
    v.contains(create_std_list_dogen_identification_entities_logical_id(position + 0));
    v.is_root(create_bool(position + 1));
    v.is_global_module(create_bool(position + 2));
    v.orm_properties(create_boost_optional_dogen_logical_entities_orm_module_properties(position + 3));
}

module_generator::result_type
module_generator::create(const unsigned int position) {
    module r;
    module_generator::populate(position, r);
    return r;
}

module_generator::result_type*
module_generator::create_ptr(const unsigned int position) {
    module* p = new module();
    module_generator::populate(position, *p);
    return p;
}

module_generator::result_type
module_generator::operator()() {
    return create(position_++);
}

}