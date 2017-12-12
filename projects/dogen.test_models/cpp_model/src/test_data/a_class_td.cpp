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
#include "dogen/test_models/cpp_model/test_data/a_class_td.hpp"
#include "dogen/test_models/cpp_model/test_data/book_types_td.hpp"
#include "dogen/test_models/cpp_model/test_data/colour_types_td.hpp"
#include "dogen/test_models/cpp_model/test_data/package_4/shape_types_td.hpp"

namespace {

dogen::test_models::cpp_model::colour_types
create_dogen_test_models_cpp_model_colour_types(const unsigned int position) {
    return dogen::test_models::cpp_model::colour_types_generator::create(position);
}

dogen::test_models::cpp_model::book_types
create_dogen_test_models_cpp_model_book_types(const unsigned int position) {
    return dogen::test_models::cpp_model::book_types_generator::create(position);
}

dogen::test_models::cpp_model::package_4::shape_types
create_dogen_test_models_cpp_model_package_4_shape_types(const unsigned int position) {
    return dogen::test_models::cpp_model::package_4::shape_types_generator::create(position);
}

}

namespace dogen {
namespace test_models {
namespace cpp_model {

a_class_generator::a_class_generator() : position_(0) { }

void a_class_generator::
populate(const unsigned int position, result_type& v) {
    v.colour_type(create_dogen_test_models_cpp_model_colour_types(position + 0));
    v.book_type(create_dogen_test_models_cpp_model_book_types(position + 1));
    v.shape_type(create_dogen_test_models_cpp_model_package_4_shape_types(position + 2));
}

a_class_generator::result_type
a_class_generator::create(const unsigned int position) {
    a_class r;
    a_class_generator::populate(position, r);
    return r;
}

a_class_generator::result_type*
a_class_generator::create_ptr(const unsigned int position) {
    a_class* p = new a_class();
    a_class_generator::populate(position, *p);
    return p;
}

a_class_generator::result_type
a_class_generator::operator()() {
    return create(position_++);
}

} } }
