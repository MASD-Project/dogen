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
#include "dogen.identification/test_data/entities/logical_id_td.hpp"
#include "dogen.logical/test_data/entities/mapping/fixed_mappable_td.hpp"
#include "dogen.logical/test_data/entities/mapping/element_repository_td.hpp"
#include "dogen.logical/test_data/entities/mapping/extensible_mappable_td.hpp"

namespace {

dogen::identification::entities::logical_id
create_dogen_identification_entities_logical_id(const unsigned int position) {
    return dogen::identification::entities::logical_id_generator::create(position);
}

dogen::logical::entities::mapping::extensible_mappable*
create_dogen_logical_entities_mapping_extensible_mappable_ptr(const unsigned int position) {
    return dogen::logical::entities::mapping::extensible_mappable_generator::create_ptr(position);
}

boost::shared_ptr<dogen::logical::entities::mapping::extensible_mappable>
create_boost_shared_ptr_dogen_logical_entities_mapping_extensible_mappable(unsigned int position) {
    boost::shared_ptr<dogen::logical::entities::mapping::extensible_mappable> r(
        create_dogen_logical_entities_mapping_extensible_mappable_ptr(position));
    return r;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::mapping::extensible_mappable> > create_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_mapping_extensible_mappable(unsigned int position) {
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::mapping::extensible_mappable> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_identification_entities_logical_id(position + i), create_boost_shared_ptr_dogen_logical_entities_mapping_extensible_mappable(position + i)));
    }
    return r;
}

dogen::logical::entities::mapping::fixed_mappable*
create_dogen_logical_entities_mapping_fixed_mappable_ptr(const unsigned int position) {
    return dogen::logical::entities::mapping::fixed_mappable_generator::create_ptr(position);
}

boost::shared_ptr<dogen::logical::entities::mapping::fixed_mappable>
create_boost_shared_ptr_dogen_logical_entities_mapping_fixed_mappable(unsigned int position) {
    boost::shared_ptr<dogen::logical::entities::mapping::fixed_mappable> r(
        create_dogen_logical_entities_mapping_fixed_mappable_ptr(position));
    return r;
}

std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::mapping::fixed_mappable> > create_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_mapping_fixed_mappable(unsigned int position) {
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::mapping::fixed_mappable> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_identification_entities_logical_id(position + i), create_boost_shared_ptr_dogen_logical_entities_mapping_fixed_mappable(position + i)));
    }
    return r;
}

}

namespace dogen::logical::entities::mapping {

element_repository_generator::element_repository_generator() : position_(0) { }

void element_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.extensible_mappables(create_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_mapping_extensible_mappable(position + 0));
    v.fixed_mappables(create_std_unordered_map_dogen_identification_entities_logical_id_boost_shared_ptr_dogen_logical_entities_mapping_fixed_mappable(position + 1));
}

element_repository_generator::result_type
element_repository_generator::create(const unsigned int position) {
    element_repository r;
    element_repository_generator::populate(position, r);
    return r;
}

element_repository_generator::result_type*
element_repository_generator::create_ptr(const unsigned int position) {
    element_repository* p = new element_repository();
    element_repository_generator::populate(position, *p);
    return p;
}

element_repository_generator::result_type
element_repository_generator::operator()() {
    return create(position_++);
}

}
