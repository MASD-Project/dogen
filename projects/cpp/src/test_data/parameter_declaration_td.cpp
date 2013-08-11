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
#include "dogen/cpp/test_data/declarator_td.hpp"
#include "dogen/cpp/test_data/parameter_declaration_td.hpp"

namespace {

dogen::cpp::declarator*
create_dogen_cpp_declarator_ptr(const unsigned int position) {
    return dogen::cpp::declarator_generator::create_ptr(position);
}

boost::shared_ptr<dogen::cpp::declarator>
create_boost_shared_ptr_dogen_cpp_declarator(unsigned int position) {
    boost::shared_ptr<dogen::cpp::declarator> r(
        create_dogen_cpp_declarator_ptr(position));
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace cpp {

parameter_declaration_generator::parameter_declaration_generator() : position_(0) { }

void parameter_declaration_generator::
populate(const unsigned int position, result_type& v) {
    v.declarator(create_boost_shared_ptr_dogen_cpp_declarator(position + 0));
    v.assignment_expression(create_std_string(position + 1));
}

parameter_declaration_generator::result_type
parameter_declaration_generator::create(const unsigned int position) {
    parameter_declaration r;
    parameter_declaration_generator::populate(position, r);
    return r;
}
parameter_declaration_generator::result_type*
parameter_declaration_generator::create_ptr(const unsigned int position) {
    parameter_declaration* p = new parameter_declaration();
    parameter_declaration_generator::populate(position, *p);
    return p;
}

parameter_declaration_generator::result_type
parameter_declaration_generator::operator()() {
    return create(position_++);
}

} }
