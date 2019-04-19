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
#include "masd.dogen.variability/test_data/meta_model/name_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/element_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/feature_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/profile_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/configuration_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/feature_template_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/profile_template_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/configuration_point_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/configuration_point_template_td.hpp"

namespace {

masd::dogen::variability::meta_model::name
create_masd_dogen_variability_meta_model_name(const unsigned int position) {
    return masd::dogen::variability::meta_model::name_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace masd::dogen::variability::meta_model {

void element_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_masd_dogen_variability_meta_model_name(position + 0));
    v.description(create_std_string(position + 1));
}

element_generator::result_type*
element_generator::create_ptr(const unsigned int position) {
    if ((position % 6) == 0)
        return masd::dogen::variability::meta_model::configuration_point_generator::create_ptr(position);
    if ((position % 6) == 1)
        return masd::dogen::variability::meta_model::configuration_point_template_generator::create_ptr(position);
    if ((position % 6) == 2)
        return masd::dogen::variability::meta_model::feature_generator::create_ptr(position);
    if ((position % 6) == 3)
        return masd::dogen::variability::meta_model::feature_template_generator::create_ptr(position);
    if ((position % 6) == 4)
        return masd::dogen::variability::meta_model::profile_generator::create_ptr(position);
    if ((position % 6) == 5)
        return masd::dogen::variability::meta_model::profile_template_generator::create_ptr(position);
    return masd::dogen::variability::meta_model::configuration_generator::create_ptr(position);
}

}
