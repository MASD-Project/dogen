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
#include "dogen/test_models/cpp_model/test_data/base_object_template_instance_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

}

namespace dogen {
namespace test_models {
namespace cpp_model {

base_object_template_instance_generator::base_object_template_instance_generator() : position_(0) { }

void base_object_template_instance_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_int(position + 0));
}

base_object_template_instance_generator::result_type
base_object_template_instance_generator::create(const unsigned int position) {
    base_object_template_instance r;
    base_object_template_instance_generator::populate(position, r);
    return r;
}

base_object_template_instance_generator::result_type*
base_object_template_instance_generator::create_ptr(const unsigned int position) {
    base_object_template_instance* p = new base_object_template_instance();
    base_object_template_instance_generator::populate(position, *p);
    return p;
}

base_object_template_instance_generator::result_type
base_object_template_instance_generator::operator()() {
    return create(position_++);
}

} } }
