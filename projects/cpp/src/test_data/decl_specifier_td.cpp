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
#include "dogen/cpp/test_data/decl_specifier_td.hpp"
#include "dogen/cpp/test_data/function_specifier_types_td.hpp"
#include "dogen/cpp/test_data/storage_class_types_td.hpp"
#include "dogen/cpp/test_data/type_specifier_td.hpp"

namespace {

dogen::cpp::storage_class_types
create_dogen_cpp_storage_class_types(const unsigned int position) {
    return dogen::cpp::storage_class_types_generator::create(position);
}

dogen::cpp::type_specifier
create_dogen_cpp_type_specifier(const unsigned int position) {
    return dogen::cpp::type_specifier_generator::create(position);
}

dogen::cpp::function_specifier_types
create_dogen_cpp_function_specifier_types(const unsigned int position) {
    return dogen::cpp::function_specifier_types_generator::create(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace cpp {

decl_specifier_generator::decl_specifier_generator() : position_(0) { }

void decl_specifier_generator::
populate(const unsigned int position, result_type& v) {
    v.storage_class_type(create_dogen_cpp_storage_class_types(position + 0));
    v.type_specifier(create_dogen_cpp_type_specifier(position + 1));
    v.function_specifier(create_dogen_cpp_function_specifier_types(position + 2));
    v.is_friend(create_bool(position + 3));
    v.is_typedef(create_bool(position + 4));
}

decl_specifier_generator::result_type
decl_specifier_generator::create(const unsigned int position) {
    decl_specifier r;
    decl_specifier_generator::populate(position, r);
    return r;
}
decl_specifier_generator::result_type*
decl_specifier_generator::create_ptr(const unsigned int position) {
    decl_specifier* p = new decl_specifier();
    decl_specifier_generator::populate(position, *p);
    return p;
}

decl_specifier_generator::result_type
decl_specifier_generator::operator()() {
    return create(position_++);
}

} }
