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
#include <sstream>
#include "dogen.physical/test_data/entities/part_td.hpp"
#include "dogen.physical/test_data/entities/facet_td.hpp"
#include "dogen.physical/test_data/entities/archetype_td.hpp"
#include "dogen.identification/test_data/entities/label_td.hpp"
#include "dogen.physical/test_data/entities/path_configuration_td.hpp"
#include "dogen.identification/test_data/entities/physical_meta_id_td.hpp"
#include "dogen.identification/test_data/entities/physical_meta_name_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::identification::entities::physical_meta_name
create_dogen_identification_entities_physical_meta_name(const unsigned int position) {
    return dogen::identification::entities::physical_meta_name_generator::create(position);
}

dogen::identification::entities::label
create_dogen_identification_entities_label(const unsigned int position) {
    return dogen::identification::entities::label_generator::create(position);
}

std::list<dogen::identification::entities::label> create_std_list_dogen_identification_entities_label(unsigned int position) {
    std::list<dogen::identification::entities::label> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_identification_entities_label(position + i));
    }
    return r;
}

dogen::physical::entities::path_configuration
create_dogen_physical_entities_path_configuration(const unsigned int position) {
    return dogen::physical::entities::path_configuration_generator::create(position);
}

dogen::identification::entities::physical_meta_id
create_dogen_identification_entities_physical_meta_id(const unsigned int position) {
    return dogen::identification::entities::physical_meta_id_generator::create(position);
}

dogen::physical::entities::facet
create_dogen_physical_entities_facet(const unsigned int position) {
    return dogen::physical::entities::facet_generator::create(position);
}

std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet> create_std_unordered_map_dogen_identification_entities_physical_meta_id_dogen_physical_entities_facet(unsigned int position) {
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::facet> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_identification_entities_physical_meta_id(position + i), create_dogen_physical_entities_facet(position + i)));
    }
    return r;
}

dogen::physical::entities::archetype
create_dogen_physical_entities_archetype(const unsigned int position) {
    return dogen::physical::entities::archetype_generator::create(position);
}

std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype> create_std_unordered_map_dogen_identification_entities_physical_meta_id_dogen_physical_entities_archetype(unsigned int position) {
    std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::physical::entities::archetype> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_identification_entities_physical_meta_id(position + i), create_dogen_physical_entities_archetype(position + i)));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

}

namespace dogen::physical::entities {

part_generator::part_generator() : position_(0) { }

void part_generator::
populate(const unsigned int position, result_type& v) {
    v.directory_name(create_std_string(position + 0));
    v.description(create_std_string(position + 1));
    v.meta_name(create_dogen_identification_entities_physical_meta_name(position + 2));
    v.labels(create_std_list_dogen_identification_entities_label(position + 3));
    v.path_configuration(create_dogen_physical_entities_path_configuration(position + 4));
    v.facets(create_std_unordered_map_dogen_identification_entities_physical_meta_id_dogen_physical_entities_facet(position + 5));
    v.archetypes(create_std_unordered_map_dogen_identification_entities_physical_meta_id_dogen_physical_entities_archetype(position + 6));
    v.requires_relative_path(create_bool(position + 7));
}

part_generator::result_type
part_generator::create(const unsigned int position) {
    part r;
    part_generator::populate(position, r);
    return r;
}

part_generator::result_type*
part_generator::create_ptr(const unsigned int position) {
    part* p = new part();
    part_generator::populate(position, *p);
    return p;
}

part_generator::result_type
part_generator::operator()() {
    return create(position_++);
}

}