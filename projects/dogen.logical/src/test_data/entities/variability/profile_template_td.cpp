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
#include "dogen.logical/test_data/entities/variability/abstract_profile_td.hpp"
#include "dogen.logical/test_data/entities/variability/profile_template_td.hpp"
#include "dogen.logical/test_data/entities/variability/profile_template_entry_td.hpp"

namespace {

dogen::logical::entities::variability::profile_template_entry
create_dogen_logical_entities_variability_profile_template_entry(const unsigned int position) {
    return dogen::logical::entities::variability::profile_template_entry_generator::create(position);
}

std::list<dogen::logical::entities::variability::profile_template_entry> create_std_list_dogen_logical_entities_variability_profile_template_entry(unsigned int position) {
    std::list<dogen::logical::entities::variability::profile_template_entry> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_logical_entities_variability_profile_template_entry(position + i));
    }
    return r;
}

}

namespace dogen::logical::entities::variability {

profile_template_generator::profile_template_generator() : position_(0) { }

void profile_template_generator::
populate(const unsigned int position, result_type& v) {
    dogen::logical::entities::variability::abstract_profile_generator::populate(position, v);
    v.entries(create_std_list_dogen_logical_entities_variability_profile_template_entry(position + 0));
}

profile_template_generator::result_type
profile_template_generator::create(const unsigned int position) {
    profile_template r;
    profile_template_generator::populate(position, r);
    return r;
}

profile_template_generator::result_type*
profile_template_generator::create_ptr(const unsigned int position) {
    profile_template* p = new profile_template();
    profile_template_generator::populate(position, *p);
    return p;
}

profile_template_generator::result_type
profile_template_generator::operator()() {
    return create(position_++);
}

}