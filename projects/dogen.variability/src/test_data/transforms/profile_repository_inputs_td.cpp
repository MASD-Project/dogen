/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * These files are code-generated via overrides to test dogen. Do not commit them.
 *
 * Generation timestamp: 2022-10-20T10:20:30
 * WARNING: do not edit this file manually.
 * Generated by MASD Dogen v1.0.33
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
#include "dogen.variability/test_data/entities/profile_td.hpp"
#include "dogen.variability/test_data/entities/profile_template_td.hpp"
#include "dogen.variability/test_data/transforms/profile_repository_inputs_td.hpp"

namespace {

dogen::variability::entities::profile
create_dogen_variability_entities_profile(const unsigned int position) {
    return dogen::variability::entities::profile_generator::create(position);
}

std::list<dogen::variability::entities::profile> create_std_list_dogen_variability_entities_profile(unsigned int position) {
    std::list<dogen::variability::entities::profile> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_variability_entities_profile(position + i));
    }
    return r;
}

dogen::variability::entities::profile_template
create_dogen_variability_entities_profile_template(const unsigned int position) {
    return dogen::variability::entities::profile_template_generator::create(position);
}

std::list<dogen::variability::entities::profile_template> create_std_list_dogen_variability_entities_profile_template(unsigned int position) {
    std::list<dogen::variability::entities::profile_template> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_variability_entities_profile_template(position + i));
    }
    return r;
}

}

namespace dogen::variability::transforms {

profile_repository_inputs_generator::profile_repository_inputs_generator() : position_(0) { }

void profile_repository_inputs_generator::
populate(const unsigned int position, result_type& v) {
    v.profiles(create_std_list_dogen_variability_entities_profile(position + 0));
    v.templates(create_std_list_dogen_variability_entities_profile_template(position + 1));
}

profile_repository_inputs_generator::result_type
profile_repository_inputs_generator::create(const unsigned int position) {
    profile_repository_inputs r;
    profile_repository_inputs_generator::populate(position, r);
    return r;
}

profile_repository_inputs_generator::result_type*
profile_repository_inputs_generator::create_ptr(const unsigned int position) {
    profile_repository_inputs* p = new profile_repository_inputs();
    profile_repository_inputs_generator::populate(position, *p);
    return p;
}

profile_repository_inputs_generator::result_type
profile_repository_inputs_generator::operator()() {
    return create(position_++);
}

}