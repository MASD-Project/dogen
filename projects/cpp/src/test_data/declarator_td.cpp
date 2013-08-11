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
#include "dogen/cpp/test_data/cv_qualifier_types_td.hpp"
#include "dogen/cpp/test_data/declarator_td.hpp"
#include "dogen/cpp/test_data/parameter_declaration_td.hpp"
#include "dogen/cpp/test_data/pointer_types_td.hpp"
#include "dogen/cpp/test_data/qualified_id_td.hpp"

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

std::list<dogen::cpp::qualified_id> create_std_list_dogen_cpp_qualified_id(unsigned int position) {
    std::list<dogen::cpp::qualified_id> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_cpp_qualified_id(position + i));
    }
    return r;
}

dogen::cpp::parameter_declaration
create_dogen_cpp_parameter_declaration(const unsigned int position) {
    return dogen::cpp::parameter_declaration_generator::create(position);
}

std::list<dogen::cpp::parameter_declaration> create_std_list_dogen_cpp_parameter_declaration(unsigned int position) {
    std::list<dogen::cpp::parameter_declaration> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_cpp_parameter_declaration(position + i));
    }
    return r;
}

}

namespace dogen {
namespace cpp {

declarator_generator::declarator_generator() : position_(0) { }

void declarator_generator::
populate(const unsigned int position, result_type& v) {
    v.cv_qualifier(create_dogen_cpp_cv_qualifier_types(position + 0));
    v.pointer_type(create_dogen_cpp_pointer_types(position + 1));
    v.pointer_cv_qualifier(create_dogen_cpp_cv_qualifier_types(position + 2));
    v.declarator_id(create_dogen_cpp_qualified_id(position + 3));
    v.exception_specification(create_std_list_dogen_cpp_qualified_id(position + 4));
    v.parameter_declaration_list(create_std_list_dogen_cpp_parameter_declaration(position + 5));
}

declarator_generator::result_type
declarator_generator::create(const unsigned int position) {
    declarator r;
    declarator_generator::populate(position, r);
    return r;
}
declarator_generator::result_type*
declarator_generator::create_ptr(const unsigned int position) {
    declarator* p = new declarator();
    declarator_generator::populate(position, *p);
    return p;
}

declarator_generator::result_type
declarator_generator::operator()() {
    return create(position_++);
}

} }
