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
#include "dogen/yarn/test_data/name_td.hpp"
#include "dogen/yarn/test_data/mapping_context_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::yarn::name
create_dogen_yarn_name(const unsigned int position) {
    return dogen::yarn::name_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::name> create_std_unordered_map_std_string_dogen_yarn_name(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::name> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_name(position + i)));
    }
    return r;
}

std::unordered_set<std::string> create_std_unordered_set_std_string(unsigned int position) {
    std::unordered_set<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_std_string(position + i));
    }
    return r;
}

}

namespace dogen {
namespace yarn {

mapping_context_generator::mapping_context_generator() : position_(0) { }

void mapping_context_generator::
populate(const unsigned int position, result_type& v) {
    v.translations(create_std_unordered_map_std_string_dogen_yarn_name(position + 0));
    v.erasures(create_std_unordered_set_std_string(position + 1));
    v.injections(create_std_unordered_map_std_string_dogen_yarn_name(position + 2));
}

mapping_context_generator::result_type
mapping_context_generator::create(const unsigned int position) {
    mapping_context r;
    mapping_context_generator::populate(position, r);
    return r;
}

mapping_context_generator::result_type*
mapping_context_generator::create_ptr(const unsigned int position) {
    mapping_context* p = new mapping_context();
    mapping_context_generator::populate(position, *p);
    return p;
}

mapping_context_generator::result_type
mapping_context_generator::operator()() {
    return create(position_++);
}

} }
