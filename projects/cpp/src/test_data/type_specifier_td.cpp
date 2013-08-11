/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/cpp/test_data/class_key_types_td.hpp"
#include "dogen/cpp/test_data/cv_qualifier_types_td.hpp"
#include "dogen/cpp/test_data/pointer_types_td.hpp"
#include "dogen/cpp/test_data/qualified_id_td.hpp"
#include "dogen/cpp/test_data/template_id_td.hpp"
#include "dogen/cpp/test_data/type_specifier_td.hpp"

namespace {

dogen::cpp::cv_qualifier_types
create_dogen_cpp_cv_qualifier_types(const unsigned int position) {
    return dogen::cpp::cv_qualifier_types_generator::create(position);
}

dogen::cpp::pointer_types
create_dogen_cpp_pointer_types(const unsigned int position) {
    return dogen::cpp::pointer_types_generator::create(position);
}

dogen::cpp::qualified_id
create_dogen_cpp_qualified_id(const unsigned int position) {
    return dogen::cpp::qualified_id_generator::create(position);
}

dogen::cpp::class_key_types
create_dogen_cpp_class_key_types(const unsigned int position) {
    return dogen::cpp::class_key_types_generator::create(position);
}

dogen::cpp::template_id
create_dogen_cpp_template_id(const unsigned int position) {
    return dogen::cpp::template_id_generator::create(position);
}

}

namespace dogen {
namespace cpp {

type_specifier_generator::type_specifier_generator() : position_(0) { }

void type_specifier_generator::
populate(const unsigned int position, result_type& v) {
    v.cv_qualifier(create_dogen_cpp_cv_qualifier_types(position + 0));
    v.pointer_type(create_dogen_cpp_pointer_types(position + 1));
    v.qualified_id(create_dogen_cpp_qualified_id(position + 2));
    v.class_key(create_dogen_cpp_class_key_types(position + 3));
    v.template_id(create_dogen_cpp_template_id(position + 4));
}

type_specifier_generator::result_type
type_specifier_generator::create(const unsigned int position) {
    type_specifier r;
    type_specifier_generator::populate(position, r);
    return r;
}
type_specifier_generator::result_type*
type_specifier_generator::create_ptr(const unsigned int position) {
    type_specifier* p = new type_specifier();
    type_specifier_generator::populate(position, *p);
    return p;
}

type_specifier_generator::result_type
type_specifier_generator::operator()() {
    return create(position_++);
}

} }
