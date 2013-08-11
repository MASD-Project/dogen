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
#include "dogen/cpp/test_data/template_argument_td.hpp"
#include "dogen/cpp/test_data/template_id_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::cpp::template_argument
create_dogen_cpp_template_argument(const unsigned int position) {
    return dogen::cpp::template_argument_generator::create(position);
}

std::list<dogen::cpp::template_argument> create_std_list_dogen_cpp_template_argument(unsigned int position) {
    std::list<dogen::cpp::template_argument> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_cpp_template_argument(position + i));
    }
    return r;
}

}

namespace dogen {
namespace cpp {

template_id_generator::template_id_generator() : position_(0) { }

void template_id_generator::
populate(const unsigned int position, result_type& v) {
    v.template_name(create_std_string(position + 0));
    v.template_argument_list(create_std_list_dogen_cpp_template_argument(position + 1));
}

template_id_generator::result_type
template_id_generator::create(const unsigned int position) {
    template_id r;
    template_id_generator::populate(position, r);
    return r;
}
template_id_generator::result_type*
template_id_generator::create_ptr(const unsigned int position) {
    template_id* p = new template_id();
    template_id_generator::populate(position, *p);
    return p;
}

template_id_generator::result_type
template_id_generator::operator()() {
    return create(position_++);
}

} }
