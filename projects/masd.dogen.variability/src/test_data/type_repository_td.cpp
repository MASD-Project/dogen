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
#include "masd.dogen.variability/test_data/type_td.hpp"
#include "masd.dogen.variability/test_data/type_repository_td.hpp"

namespace {

masd::dogen::variability::type
create_masd_dogen_variability_type(const unsigned int position) {
    return masd::dogen::variability::type_generator::create(position);
}

std::list<masd::dogen::variability::type> create_std_list_masd_dogen_variability_type(unsigned int position) {
    std::list<masd::dogen::variability::type> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_variability_type(position + i));
    }
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::unordered_map<std::string, masd::dogen::variability::type> create_std_unordered_map_std_string_masd_dogen_variability_type(unsigned int position) {
    std::unordered_map<std::string, masd::dogen::variability::type> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_masd_dogen_variability_type(position + i)));
    }
    return r;
}

std::unordered_map<std::string, std::list<masd::dogen::variability::type> > create_std_unordered_map_std_string_std_list_masd_dogen_variability_type(unsigned int position) {
    std::unordered_map<std::string, std::list<masd::dogen::variability::type> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_list_masd_dogen_variability_type(position + i)));
    }
    return r;
}

}

namespace masd::dogen::variability {

type_repository_generator::type_repository_generator() : position_(0) { }

void type_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.all_types(create_std_list_masd_dogen_variability_type(position + 0));
    v.types_by_name(create_std_unordered_map_std_string_masd_dogen_variability_type(position + 1));
    v.types_by_facet_name(create_std_unordered_map_std_string_std_list_masd_dogen_variability_type(position + 2));
    v.types_by_formatter_name(create_std_unordered_map_std_string_std_list_masd_dogen_variability_type(position + 3));
    v.types_by_backend_name(create_std_unordered_map_std_string_std_list_masd_dogen_variability_type(position + 4));
    v.partially_matchable_types(create_std_unordered_map_std_string_masd_dogen_variability_type(position + 5));
}

type_repository_generator::result_type
type_repository_generator::create(const unsigned int position) {
    type_repository r;
    type_repository_generator::populate(position, r);
    return r;
}

type_repository_generator::result_type*
type_repository_generator::create_ptr(const unsigned int position) {
    type_repository* p = new type_repository();
    type_repository_generator::populate(position, *p);
    return p;
}

type_repository_generator::result_type
type_repository_generator::operator()() {
    return create(position_++);
}

}
