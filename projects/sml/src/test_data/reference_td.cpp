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
#include "dogen/sml/test_data/reference_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace sml {

reference_generator::reference_generator() : position_(0) { }

void reference_generator::
populate(const unsigned int position, result_type& v) {
    v.model_name(create_std_string(position + 0));
    v.external_package_path(create_std_list_std_string(position + 1));
    v.is_system(create_bool(position + 2));
}

reference_generator::result_type
reference_generator::create(const unsigned int position) {
    reference r;
    reference_generator::populate(position, r);
    return r;
}
reference_generator::result_type*
reference_generator::create_ptr(const unsigned int position) {
    reference* p = new reference();
    reference_generator::populate(position, *p);
    return p;
}

reference_generator::result_type
reference_generator::operator()() {
    return create(position_++);
}

} }
