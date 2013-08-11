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
#include "dogen/cpp/test_data/access_specifier_types_td.hpp"
#include "dogen/cpp/test_data/member_declaration_td.hpp"
#include "dogen/cpp/test_data/member_specification_td.hpp"

namespace {

dogen::cpp::access_specifier_types
create_dogen_cpp_access_specifier_types(const unsigned int position) {
    return dogen::cpp::access_specifier_types_generator::create(position);
}

dogen::cpp::member_declaration
create_dogen_cpp_member_declaration(const unsigned int position) {
    return dogen::cpp::member_declaration_generator::create(position);
}

std::list<dogen::cpp::member_declaration> create_std_list_dogen_cpp_member_declaration(unsigned int position) {
    std::list<dogen::cpp::member_declaration> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_cpp_member_declaration(position + i));
    }
    return r;
}

}

namespace dogen {
namespace cpp {

member_specification_generator::member_specification_generator() : position_(0) { }

void member_specification_generator::
populate(const unsigned int position, result_type& v) {
    v.access(create_dogen_cpp_access_specifier_types(position + 0));
    v.member_declaration_list(create_std_list_dogen_cpp_member_declaration(position + 1));
}

member_specification_generator::result_type
member_specification_generator::create(const unsigned int position) {
    member_specification r;
    member_specification_generator::populate(position, r);
    return r;
}
member_specification_generator::result_type*
member_specification_generator::create_ptr(const unsigned int position) {
    member_specification* p = new member_specification();
    member_specification_generator::populate(position, *p);
    return p;
}

member_specification_generator::result_type
member_specification_generator::operator()() {
    return create(position_++);
}

} }
