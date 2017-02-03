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
#include "dogen/test_models/std_model/test_data/class_k_td.hpp"
#include "dogen/test_models/std_model/test_data/string_primitive_td.hpp"

namespace {

dogen::test_models::std_model::string_primitive
create_dogen_test_models_std_model_string_primitive(const unsigned int position) {
    return dogen::test_models::std_model::string_primitive_generator::create(position);
}

}

namespace dogen {
namespace test_models {
namespace std_model {

class_k_generator::class_k_generator() : position_(0) { }

void class_k_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_dogen_test_models_std_model_string_primitive(position + 0));
}

class_k_generator::result_type
class_k_generator::create(const unsigned int position) {
    class_k r;
    class_k_generator::populate(position, r);
    return r;
}

class_k_generator::result_type*
class_k_generator::create_ptr(const unsigned int position) {
    class_k* p = new class_k();
    class_k_generator::populate(position, *p);
    return p;
}

class_k_generator::result_type
class_k_generator::operator()() {
    return create(position_++);
}

} } }
