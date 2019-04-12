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
#include "masd.dogen.variability/test_data/profile_td.hpp"
#include "masd.dogen.variability/test_data/configuration_templates_repository_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

masd::dogen::variability::profile
create_masd_dogen_variability_profile(const unsigned int position) {
    return masd::dogen::variability::profile_generator::create(position);
}

std::unordered_map<std::string, masd::dogen::variability::profile> create_std_unordered_map_std_string_masd_dogen_variability_profile(unsigned int position) {
    std::unordered_map<std::string, masd::dogen::variability::profile> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_masd_dogen_variability_profile(position + i)));
    }
    return r;
}

}

namespace masd::dogen::variability {

configuration_templates_repository_generator::configuration_templates_repository_generator() : position_(0) { }

void configuration_templates_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.by_name(create_std_unordered_map_std_string_masd_dogen_variability_profile(position + 0));
}

configuration_templates_repository_generator::result_type
configuration_templates_repository_generator::create(const unsigned int position) {
    configuration_templates_repository r;
    configuration_templates_repository_generator::populate(position, r);
    return r;
}

configuration_templates_repository_generator::result_type*
configuration_templates_repository_generator::create_ptr(const unsigned int position) {
    configuration_templates_repository* p = new configuration_templates_repository();
    configuration_templates_repository_generator::populate(position, *p);
    return p;
}

configuration_templates_repository_generator::result_type
configuration_templates_repository_generator::operator()() {
    return create(position_++);
}

}
