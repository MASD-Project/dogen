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
#include "masd.dogen.variability/test_data/meta_model/value_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/key_value_pair_td.hpp"

namespace {

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

namespace masd::dogen::variability::meta_model {

key_value_pair_generator::key_value_pair_generator() : position_(0) { }

void key_value_pair_generator::
populate(const unsigned int position, result_type& v) {
    masd::dogen::variability::meta_model::value_generator::populate(position, v);
    v.content(create_std_unordered_map_std_string_std_string(position + 0));
}

key_value_pair_generator::result_type
key_value_pair_generator::create(const unsigned int position) {
    key_value_pair r;
    key_value_pair_generator::populate(position, r);
    return r;
}

key_value_pair_generator::result_type*
key_value_pair_generator::create_ptr(const unsigned int position) {
    key_value_pair* p = new key_value_pair();
    key_value_pair_generator::populate(position, *p);
    return p;
}

key_value_pair_generator::result_type
key_value_pair_generator::operator()() {
    return create(position_++);
}

}
