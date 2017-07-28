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
#include "dogen/annotations/test_data/archetype_location_repository_td.hpp"

namespace {

dogen::annotations::archetype_location
create_dogen_annotations_archetype_location(const unsigned int position) {
    return dogen::annotations::archetype_location_generator::create(position);
}

std::list<dogen::annotations::archetype_location> create_std_list_dogen_annotations_archetype_location(unsigned int position) {
    std::list<dogen::annotations::archetype_location> r;
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

std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> > create_std_unordered_map_std_string_std_list_dogen_annotations_archetype_location(unsigned int position) {
    std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_list_dogen_annotations_archetype_location(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace annotations {

archetype_location_repository_generator::archetype_location_repository_generator() : position_(0) { }

void archetype_location_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.archetype_locations(create_std_list_dogen_annotations_archetype_location(position + 0));
    v.facet_names_by_kernel_name(create_std_unordered_map_std_string_std_unordered_set_std_string(position + 1));
    v.formatter_names_by_kernel_name(create_std_unordered_map_std_string_std_unordered_set_std_string(position + 2));
    v.archetype_locations_by_meta_name(create_std_unordered_map_std_string_std_list_dogen_annotations_archetype_location(position + 3));
}

archetype_location_repository_generator::result_type
archetype_location_repository_generator::create(const unsigned int position) {
    archetype_location_repository r;
    archetype_location_repository_generator::populate(position, r);
    return r;
}

archetype_location_repository_generator::result_type*
archetype_location_repository_generator::create_ptr(const unsigned int position) {
    archetype_location_repository* p = new archetype_location_repository();
    archetype_location_repository_generator::populate(position, *p);
    return p;
}

archetype_location_repository_generator::result_type
archetype_location_repository_generator::operator()() {
    return create(position_++);
}

} }
