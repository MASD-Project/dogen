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
#include "masd.dogen.variability/test_data/meta_model/configuration_td.hpp"
#include "masd.dogen.variability/test_data/meta_model/configuration_template_td.hpp"
#include "masd.dogen.variability/test_data/transforms/configuration_processing_td.hpp"

namespace {

masd::dogen::variability::meta_model::configuration_template
create_masd_dogen_variability_meta_model_configuration_template(const unsigned int position) {
    return masd::dogen::variability::meta_model::configuration_template_generator::create(position);
}

masd::dogen::variability::meta_model::configuration
create_masd_dogen_variability_meta_model_configuration(const unsigned int position) {
    return masd::dogen::variability::meta_model::configuration_generator::create(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

}

namespace masd::dogen::variability::transforms {

configuration_processing_generator::configuration_processing_generator() : position_(0) { }

void configuration_processing_generator::
populate(const unsigned int position, result_type& v) {
    v.configuration_template(create_masd_dogen_variability_meta_model_configuration_template(position + 0));
    v.configuration(create_masd_dogen_variability_meta_model_configuration(position + 1));
    v.merged(create_bool(position + 2));
}

configuration_processing_generator::result_type
configuration_processing_generator::create(const unsigned int position) {
    configuration_processing r;
    configuration_processing_generator::populate(position, r);
    return r;
}

configuration_processing_generator::result_type*
configuration_processing_generator::create_ptr(const unsigned int position) {
    configuration_processing* p = new configuration_processing();
    configuration_processing_generator::populate(position, *p);
    return p;
}

configuration_processing_generator::result_type
configuration_processing_generator::operator()() {
    return create(position_++);
}

}
