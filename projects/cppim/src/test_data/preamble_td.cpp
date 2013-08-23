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
#include "dogen/cppim/test_data/feature_td.hpp"
#include "dogen/cppim/test_data/preamble_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::pair<std::string, std::string>
create_std_pair_std_string_std_string(unsigned int position) {
    std::pair<std::string, std::string> r(
        create_std_string(position),
        create_std_string(position));
    return r;
}

std::list<std::pair<std::string, std::string> > create_std_list_std_pair_std_string_std_string_(unsigned int position) {
    std::list<std::pair<std::string, std::string> > r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_std_pair_std_string_std_string(position + i));
    }
    return r;
}

}

namespace dogen {
namespace cppim {

preamble_generator::preamble_generator() : position_(0) { }

void preamble_generator::
populate(const unsigned int position, result_type& v) {
    dogen::cppim::feature_generator::populate(position, v);
    v.prefix(create_std_string(position + 0));
    v.fields(create_std_list_std_pair_std_string_std_string_(position + 1));
    v.kvp_separator(create_std_string(position + 2));
    v.field_separator(create_std_string(position + 3));
    v.postfix(create_std_string(position + 4));
}

preamble_generator::result_type
preamble_generator::create(const unsigned int position) {
    preamble r;
    preamble_generator::populate(position, r);
    return r;
}
preamble_generator::result_type*
preamble_generator::create_ptr(const unsigned int position) {
    preamble* p = new preamble();
    preamble_generator::populate(position, *p);
    return p;
}

preamble_generator::result_type
preamble_generator::operator()() {
    return create(position_++);
}

} }
