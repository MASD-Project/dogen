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
#include "dogen/yarn/test_data/type_parameters_settings_td.hpp"
#include "dogen/yarn/test_data/type_parameterisation_styles_td.hpp"

namespace {

dogen::yarn::type_parameterisation_styles
create_dogen_yarn_type_parameterisation_styles(const unsigned int position) {
    return dogen::yarn::type_parameterisation_styles_generator::create(position);
}

unsigned int create_unsigned_int(const unsigned int position) {
    return static_cast<unsigned int>(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace yarn {

type_parameters_settings_generator::type_parameters_settings_generator() : position_(0) { }

void type_parameters_settings_generator::
populate(const unsigned int position, result_type& v) {
    v.style(create_dogen_yarn_type_parameterisation_styles(position + 0));
    v.count(create_unsigned_int(position + 1));
    v.always_in_heap(create_bool(position + 2));
}

type_parameters_settings_generator::result_type
type_parameters_settings_generator::create(const unsigned int position) {
    type_parameters_settings r;
    type_parameters_settings_generator::populate(position, r);
    return r;
}

type_parameters_settings_generator::result_type*
type_parameters_settings_generator::create_ptr(const unsigned int position) {
    type_parameters_settings* p = new type_parameters_settings();
    type_parameters_settings_generator::populate(position, *p);
    return p;
}

type_parameters_settings_generator::result_type
type_parameters_settings_generator::operator()() {
    return create(position_++);
}

} }
