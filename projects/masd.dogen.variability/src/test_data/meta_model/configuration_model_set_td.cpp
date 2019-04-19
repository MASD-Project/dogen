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
#include "masd.dogen.variability/test_data/meta_model/configuration_model_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/configuration_model_set_td.hpp"

namespace {

masd::dogen::variability::meta_model::configuration_model
create_masd_dogen_variability_meta_model_configuration_model(const unsigned int position) {
    return masd::dogen::variability::meta_model::configuration_model_generator::create(position);
}

std::list<masd::dogen::variability::meta_model::configuration_model> create_std_list_masd_dogen_variability_meta_model_configuration_model(unsigned int position) {
    std::list<masd::dogen::variability::meta_model::configuration_model> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_variability_meta_model_configuration_model(position + i));
    }
    return r;
}

}

namespace masd::dogen::variability::meta_model {

configuration_model_set_generator::configuration_model_set_generator() : position_(0) { }

void configuration_model_set_generator::
populate(const unsigned int position, result_type& v) {
    v.models(create_std_list_masd_dogen_variability_meta_model_configuration_model(position + 0));
}

configuration_model_set_generator::result_type
configuration_model_set_generator::create(const unsigned int position) {
    configuration_model_set r;
    configuration_model_set_generator::populate(position, r);
    return r;
}

configuration_model_set_generator::result_type*
configuration_model_set_generator::create_ptr(const unsigned int position) {
    configuration_model_set* p = new configuration_model_set();
    configuration_model_set_generator::populate(position, *p);
    return p;
}

configuration_model_set_generator::result_type
configuration_model_set_generator::operator()() {
    return create(position_++);
}

}
