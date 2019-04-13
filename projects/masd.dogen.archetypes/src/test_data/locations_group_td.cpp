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
#include "masd.dogen.archetypes/test_data/location_td.hpp"
#include "masd.dogen.archetypes/test_data/locations_group_td.hpp"

namespace {

masd::dogen::archetypes::location
create_masd_dogen_archetypes_location(const unsigned int position) {
    return masd::dogen::archetypes::location_generator::create(position);
}

std::list<masd::dogen::archetypes::location> create_std_list_masd_dogen_archetypes_location(unsigned int position) {
    std::list<masd::dogen::archetypes::location> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_archetypes_location(position + i));
    }
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::unordered_map<std::string, std::string> create_std_unordered_map_std_string_std_string(unsigned int position) {
    std::unordered_map<std::string, std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_string(position + i)));
    }
    return r;
}

}

namespace masd::dogen::archetypes {

locations_group_generator::locations_group_generator() : position_(0) { }

void locations_group_generator::
populate(const unsigned int position, result_type& v) {
    v.locations(create_std_list_masd_dogen_archetypes_location(position + 0));
    v.canonical_locations(create_std_unordered_map_std_string_std_string(position + 1));
}

locations_group_generator::result_type
locations_group_generator::create(const unsigned int position) {
    locations_group r;
    locations_group_generator::populate(position, r);
    return r;
}

locations_group_generator::result_type*
locations_group_generator::create_ptr(const unsigned int position) {
    locations_group* p = new locations_group();
    locations_group_generator::populate(position, *p);
    return p;
}

locations_group_generator::result_type
locations_group_generator::operator()() {
    return create(position_++);
}

}
