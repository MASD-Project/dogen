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
#include "dogen/test_models/cpp_model/test_data/value_td.hpp"
#include "dogen/test_models/cpp_model/test_data/simple_object_template_instance_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

dogen::test_models::cpp_model::value
create_dogen_test_models_cpp_model_value(const unsigned int position) {
    return dogen::test_models::cpp_model::value_generator::create(position);
}

}

namespace dogen {
namespace test_models {
namespace cpp_model {

simple_object_template_instance_generator::simple_object_template_instance_generator() : position_(0) { }

void simple_object_template_instance_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_int(position + 0));
    v.prop_1(create_dogen_test_models_cpp_model_value(position + 1));
    v.prop_10(create_int(position + 2));
}

simple_object_template_instance_generator::result_type
simple_object_template_instance_generator::create(const unsigned int position) {
    simple_object_template_instance r;
    simple_object_template_instance_generator::populate(position, r);
    return r;
}

simple_object_template_instance_generator::result_type*
simple_object_template_instance_generator::create_ptr(const unsigned int position) {
    simple_object_template_instance* p = new simple_object_template_instance();
    simple_object_template_instance_generator::populate(position, *p);
    return p;
}

simple_object_template_instance_generator::result_type
simple_object_template_instance_generator::operator()() {
    return create(position_++);
}

} } }
