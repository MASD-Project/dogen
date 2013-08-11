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
#include <sstream>
#include "dogen/cpp/test_data/decl_specifier_td.hpp"
#include "dogen/cpp/test_data/declarator_td.hpp"
#include "dogen/cpp/test_data/function_types_td.hpp"
#include "dogen/cpp/test_data/member_declaration_td.hpp"

namespace {

dogen::cpp::decl_specifier
create_dogen_cpp_decl_specifier(const unsigned int position) {
    return dogen::cpp::decl_specifier_generator::create(position);
}

std::list<dogen::cpp::decl_specifier> create_std_list_dogen_cpp_decl_specifier(unsigned int position) {
    std::list<dogen::cpp::decl_specifier> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_cpp_decl_specifier(position + i));
    }
    return r;
}

dogen::cpp::declarator
create_dogen_cpp_declarator(const unsigned int position) {
    return dogen::cpp::declarator_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::cpp::function_types
create_dogen_cpp_function_types(const unsigned int position) {
    return dogen::cpp::function_types_generator::create(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace cpp {

member_declaration_generator::member_declaration_generator() : position_(0) { }

void member_declaration_generator::
populate(const unsigned int position, result_type& v) {
    v.decl_specifier_seq(create_std_list_dogen_cpp_decl_specifier(position + 0));
    v.declarator(create_dogen_cpp_declarator(position + 1));
    v.constant_initialiser(create_std_string(position + 2));
    v.function_type(create_dogen_cpp_function_types(position + 3));
    v.is_pure(create_bool(position + 4));
    v.is_override(create_bool(position + 5));
    v.is_default(create_bool(position + 6));
}

member_declaration_generator::result_type
member_declaration_generator::create(const unsigned int position) {
    member_declaration r;
    member_declaration_generator::populate(position, r);
    return r;
}
member_declaration_generator::result_type*
member_declaration_generator::create_ptr(const unsigned int position) {
    member_declaration* p = new member_declaration();
    member_declaration_generator::populate(position, *p);
    return p;
}

member_declaration_generator::result_type
member_declaration_generator::operator()() {
    return create(position_++);
}

} }
