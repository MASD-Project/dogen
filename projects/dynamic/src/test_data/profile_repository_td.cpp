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
#include "dogen/dynamic/test_data/profile_td.hpp"
#include "dogen/dynamic/test_data/profile_repository_td.hpp"

namespace {

dogen::dynamic::profile
create_dogen_dynamic_profile(const unsigned int position) {
    return dogen::dynamic::profile_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::unordered_map<std::string, dogen::dynamic::profile> create_std_unordered_map_std_string_dogen_dynamic_profile(unsigned int position) {
    std::unordered_map<std::string, dogen::dynamic::profile> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_dynamic_profile(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace dynamic {

profile_repository_generator::profile_repository_generator() : position_(0) { }

void profile_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.default_profile(create_dogen_dynamic_profile(position + 0));
    v.profiles_by_name(create_std_unordered_map_std_string_dogen_dynamic_profile(position + 1));
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

} }
