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
#include "dogen/test_models/cpp_model/test_data/class_1_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_2/class_1_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_2/class_2_td.hpp"

namespace {

dogen::test_models::cpp_model::package_2::class_1
create_dogen_test_models_cpp_model_package_2_class_1(const unsigned int position) {
    return dogen::test_models::cpp_model::package_2::class_1_generator::create(position);
}

dogen::test_models::cpp_model::class_1
create_dogen_test_models_cpp_model_class_1(const unsigned int position) {
    return dogen::test_models::cpp_model::class_1_generator::create(position);
}

}

namespace dogen {
namespace test_models {
namespace cpp_model {
namespace package_2 {

class_2_generator::class_2_generator() : position_(0) { }

void class_2_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_dogen_test_models_cpp_model_package_2_class_1(position + 0));
    v.prop_1(create_dogen_test_models_cpp_model_class_1(position + 1));
}

class_2_generator::result_type
class_2_generator::create(const unsigned int position) {
    class_2 r;
    class_2_generator::populate(position, r);
    return r;
}

class_2_generator::result_type*
class_2_generator::create_ptr(const unsigned int position) {
    class_2* p = new class_2();
    class_2_generator::populate(position, *p);
    return p;
}

class_2_generator::result_type
class_2_generator::operator()() {
    return create(position_++);
}

} } } }
