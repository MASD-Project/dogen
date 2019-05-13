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
#include "dogen.variability/test_data/meta_model/profile_td.hpp"
#include "dogen.variability/test_data/meta_model/profile_repository_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::variability::meta_model::profile
create_dogen_variability_meta_model_profile(const unsigned int position) {
    return dogen::variability::meta_model::profile_generator::create(position);
}

std::unordered_map<std::string, dogen::variability::meta_model::profile> create_std_unordered_map_std_string_dogen_variability_meta_model_profile(unsigned int position) {
    std::unordered_map<std::string, dogen::variability::meta_model::profile> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_variability_meta_model_profile(position + i)));
    }
    return r;
}

}

namespace dogen::variability::meta_model {

profile_repository_generator::profile_repository_generator() : position_(0) { }

void profile_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.by_name(create_std_unordered_map_std_string_dogen_variability_meta_model_profile(position + 0));
    v.by_labels(create_std_unordered_map_std_string_dogen_variability_meta_model_profile(position + 1));
}

profile_repository_generator::result_type
profile_repository_generator::create(const unsigned int position) {
    profile_repository r;
    profile_repository_generator::populate(position, r);
    return r;
}

profile_repository_generator::result_type*
profile_repository_generator::create_ptr(const unsigned int position) {
    profile_repository* p = new profile_repository();
    profile_repository_generator::populate(position, *p);
    return p;
}

profile_repository_generator::result_type
profile_repository_generator::operator()() {
    return create(position_++);
}

}
