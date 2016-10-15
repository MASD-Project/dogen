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
#include <sstream>
#include "dogen/yarn.dia/test_data/profile_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

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
namespace yarn {
namespace dia {

profile_generator::profile_generator() : position_(0) { }

void profile_generator::
populate(const unsigned int position, result_type& v) {
    v.is_uml_large_package(create_bool(position + 0));
    v.is_uml_class(create_bool(position + 1));
    v.is_uml_generalization(create_bool(position + 2));
    v.is_uml_association(create_bool(position + 3));
    v.is_uml_note(create_bool(position + 4));
    v.is_uml_message(create_bool(position + 5));
    v.is_uml_realization(create_bool(position + 6));
    v.is_enumeration(create_bool(position + 7));
    v.is_exception(create_bool(position + 8));
    v.is_object(create_bool(position + 9));
    v.is_concept(create_bool(position + 10));
    v.unknown_stereotypes(create_std_list_std_string(position + 11));
}

profile_generator::result_type
profile_generator::create(const unsigned int position) {
    profile r;
    profile_generator::populate(position, r);
    return r;
}

profile_generator::result_type*
profile_generator::create_ptr(const unsigned int position) {
    profile* p = new profile();
    profile_generator::populate(position, *p);
    return p;
}

profile_generator::result_type
profile_generator::operator()() {
    return create(position_++);
}

} } }
