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
#include "dogen/annotations/test_data/archetype_location_td.hpp"
#include "dogen/annotations/test_data/ownership_hierarchy_repository_td.hpp"

namespace {

dogen::annotations::archetype_location
create_dogen_annotations_archetype_location(const unsigned int position) {
    return dogen::annotations::archetype_location_generator::create(position);
}

std::vector<dogen::annotations::archetype_location> create_std_vector_dogen_annotations_archetype_location(unsigned int position) {
    std::vector<dogen::annotations::archetype_location> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_annotations_archetype_location(position + i));
    }
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::unordered_set<std::string> create_std_unordered_set_std_string(unsigned int position) {
    std::unordered_set<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_std_string(position + i));
    }
    return r;
}

std::unordered_map<std::string, std::unordered_set<std::string> > create_std_unordered_map_std_string_std_unordered_set_std_string(unsigned int position) {
    std::unordered_map<std::string, std::unordered_set<std::string> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_unordered_set_std_string(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace annotations {

ownership_hierarchy_repository_generator::ownership_hierarchy_repository_generator() : position_(0) { }

void ownership_hierarchy_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.ownership_hierarchies(create_std_vector_dogen_annotations_archetype_location(position + 0));
    v.facet_names_by_model_name(create_std_unordered_map_std_string_std_unordered_set_std_string(position + 1));
    v.formatter_names_by_model_name(create_std_unordered_map_std_string_std_unordered_set_std_string(position + 2));
}

ownership_hierarchy_repository_generator::result_type
ownership_hierarchy_repository_generator::create(const unsigned int position) {
    ownership_hierarchy_repository r;
    ownership_hierarchy_repository_generator::populate(position, r);
    return r;
}

ownership_hierarchy_repository_generator::result_type*
ownership_hierarchy_repository_generator::create_ptr(const unsigned int position) {
    ownership_hierarchy_repository* p = new ownership_hierarchy_repository();
    ownership_hierarchy_repository_generator::populate(position, *p);
    return p;
}

ownership_hierarchy_repository_generator::result_type
ownership_hierarchy_repository_generator::operator()() {
    return create(position_++);
}

} }
