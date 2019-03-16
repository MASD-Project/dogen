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
#include "masd.dogen/test_data/model_processing_configuration_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

}

namespace masd::dogen {

model_processing_configuration_generator::model_processing_configuration_generator() : position_(0) { }

void model_processing_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.compatibility_mode_enabled(create_bool(position + 0));
    v.dry_run_mode_enabled(create_bool(position + 1));
}

model_processing_configuration_generator::result_type
model_processing_configuration_generator::create(const unsigned int position) {
    model_processing_configuration r;
    model_processing_configuration_generator::populate(position, r);
    return r;
}

model_processing_configuration_generator::result_type*
model_processing_configuration_generator::create_ptr(const unsigned int position) {
    model_processing_configuration* p = new model_processing_configuration();
    model_processing_configuration_generator::populate(position, *p);
    return p;
}

model_processing_configuration_generator::result_type
model_processing_configuration_generator::operator()() {
    return create(position_++);
}

}
