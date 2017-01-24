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
#include "dogen/yarn/test_data/mapping_td.hpp"
#include "dogen/yarn/test_data/languages_td.hpp"
#include "dogen/yarn/test_data/mapping_value_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::yarn::languages
create_dogen_yarn_languages(const unsigned int position) {
    return dogen::yarn::languages_generator::create(position);
}

dogen::yarn::mapping_value
create_dogen_yarn_mapping_value(const unsigned int position) {
    return dogen::yarn::mapping_value_generator::create(position);
}

std::unordered_map<dogen::yarn::languages, dogen::yarn::mapping_value> create_std_unordered_map_dogen_yarn_languages_dogen_yarn_mapping_value(unsigned int position) {
    std::unordered_map<dogen::yarn::languages, dogen::yarn::mapping_value> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_yarn_languages(position + i), create_dogen_yarn_mapping_value(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace yarn {

mapping_generator::mapping_generator() : position_(0) { }

void mapping_generator::
populate(const unsigned int position, result_type& v) {
    v.lam_id(create_std_string(position + 0));
    v.by_language(create_std_unordered_map_dogen_yarn_languages_dogen_yarn_mapping_value(position + 1));
}

mapping_generator::result_type
mapping_generator::create(const unsigned int position) {
    mapping r;
    mapping_generator::populate(position, r);
    return r;
}

mapping_generator::result_type*
mapping_generator::create_ptr(const unsigned int position) {
    mapping* p = new mapping();
    mapping_generator::populate(position, *p);
    return p;
}

mapping_generator::result_type
mapping_generator::operator()() {
    return create(position_++);
}

} }
