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
#include <sstream>
#include "dogen.variability/test_data/entities/configuration_td.hpp"
#include "dogen.identification/test_data/entities/logical_name_td.hpp"
#include "dogen.logical/test_data/entities/variability/profile_entry_td.hpp"
#include "dogen.logical/test_data/entities/variability/abstract_profile_entry_td.hpp"
#include "dogen.logical/test_data/entities/variability/profile_template_entry_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::variability::entities::configuration*
create_dogen_variability_entities_configuration_ptr(const unsigned int position) {
    return dogen::variability::entities::configuration_generator::create_ptr(position);
}

boost::shared_ptr<dogen::variability::entities::configuration>
create_boost_shared_ptr_dogen_variability_entities_configuration(unsigned int position) {
    boost::shared_ptr<dogen::variability::entities::configuration> r(
        create_dogen_variability_entities_configuration_ptr(position));
    return r;
}

dogen::identification::entities::logical_name
create_dogen_identification_entities_logical_name(const unsigned int position) {
    return dogen::identification::entities::logical_name_generator::create(position);
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace dogen::logical::entities::variability {

void abstract_profile_entry_generator::
populate(const unsigned int position, result_type& v) {
    v.documentation(create_std_string(position + 0));
    v.configuration(create_boost_shared_ptr_dogen_variability_entities_configuration(position + 1));
    v.name(create_dogen_identification_entities_logical_name(position + 2));
    v.original_key(create_std_string(position + 3));
    v.key(create_std_string(position + 4));
    v.value(create_std_list_std_string(position + 5));
}

abstract_profile_entry_generator::result_type*
abstract_profile_entry_generator::create_ptr(const unsigned int position) {
    if ((position % 1) == 0)
        return dogen::logical::entities::variability::profile_template_entry_generator::create_ptr(position);
    return dogen::logical::entities::variability::profile_entry_generator::create_ptr(position);
}

}
