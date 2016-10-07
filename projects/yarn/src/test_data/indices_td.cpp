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
#include "dogen/yarn/test_data/indices_td.hpp"
#include "dogen/dynamic/test_data/raw_aggregate_td.hpp"

namespace {

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

dogen::dynamic::raw_aggregate
create_dogen_dynamic_raw_aggregate(const unsigned int position) {
    return dogen::dynamic::raw_aggregate_generator::create(position);
}

std::unordered_map<std::string, dogen::dynamic::raw_aggregate> create_std_unordered_map_std_string_dogen_dynamic_raw_aggregate(unsigned int position) {
    std::unordered_map<std::string, dogen::dynamic::raw_aggregate> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_dynamic_raw_aggregate(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace yarn {

indices_generator::indices_generator() : position_(0) { }

void indices_generator::
populate(const unsigned int position, result_type& v) {
    v.objects_always_in_heap(create_std_unordered_set_std_string(position + 0));
    v.elements_referable_by_attributes(create_std_unordered_set_std_string(position + 1));
    v.raw_aggregates(create_std_unordered_map_std_string_dogen_dynamic_raw_aggregate(position + 2));
}

indices_generator::result_type
indices_generator::create(const unsigned int position) {
    indices r;
    indices_generator::populate(position, r);
    return r;
}

indices_generator::result_type*
indices_generator::create_ptr(const unsigned int position) {
    indices* p = new indices();
    indices_generator::populate(position, *p);
    return p;
}

indices_generator::result_type
indices_generator::operator()() {
    return create(position_++);
}

} }
