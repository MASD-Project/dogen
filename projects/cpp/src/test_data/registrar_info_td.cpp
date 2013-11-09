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
#include "dogen/cpp/test_data/entity_td.hpp"
#include "dogen/cpp/test_data/registrar_info_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace dogen {
namespace cpp {

registrar_info_generator::registrar_info_generator() : position_(0) { }

void registrar_info_generator::
populate(const unsigned int position, result_type& v) {
    dogen::cpp::entity_generator::populate(position, v);
    v.namespaces(create_std_list_std_string(position + 0));
    v.leaves(create_std_list_std_string(position + 1));
    v.model_dependencies(create_std_list_std_string(position + 2));
}

registrar_info_generator::result_type
registrar_info_generator::create(const unsigned int position) {
    registrar_info r;
    registrar_info_generator::populate(position, r);
    return r;
}
registrar_info_generator::result_type*
registrar_info_generator::create_ptr(const unsigned int position) {
    registrar_info* p = new registrar_info();
    registrar_info_generator::populate(position, *p);
    return p;
}

registrar_info_generator::result_type
registrar_info_generator::operator()() {
    return create(position_++);
}

} }
