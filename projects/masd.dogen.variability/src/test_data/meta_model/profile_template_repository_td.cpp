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
#include "masd.dogen.variability/test_data/meta_model/profile_template_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/profile_template_repository_td.hpp"

namespace {

masd::dogen::variability::meta_model::profile_template
create_masd_dogen_variability_meta_model_profile_template(const unsigned int position) {
    return masd::dogen::variability::meta_model::profile_template_generator::create(position);
}

std::list<masd::dogen::variability::meta_model::profile_template> create_std_list_masd_dogen_variability_meta_model_profile_template(unsigned int position) {
    std::list<masd::dogen::variability::meta_model::profile_template> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_variability_meta_model_profile_template(position + i));
    }
    return r;
}

}

namespace masd::dogen::variability::meta_model {

profile_template_repository_generator::profile_template_repository_generator() : position_(0) { }

void profile_template_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.templates(create_std_list_masd_dogen_variability_meta_model_profile_template(position + 0));
}

profile_template_repository_generator::result_type
profile_template_repository_generator::create(const unsigned int position) {
    profile_template_repository r;
    profile_template_repository_generator::populate(position, r);
    return r;
}

profile_template_repository_generator::result_type*
profile_template_repository_generator::create_ptr(const unsigned int position) {
    profile_template_repository* p = new profile_template_repository();
    profile_template_repository_generator::populate(position, *p);
    return p;
}

profile_template_repository_generator::result_type
profile_template_repository_generator::operator()() {
    return create(position_++);
}

}
