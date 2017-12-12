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
#include "dogen/test_models/std_model/test_data/class_j_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

std::pair<int, int>
create_std_pair_int_int(unsigned int position) {
    std::pair<int, int> r(
        create_int(position),
        create_int(position));
    return r;
}

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

std::pair<std::string, int>
create_std_pair_std_string_int(unsigned int position) {
    std::pair<std::string, int> r(
        create_std_string(position),
        create_int(position));
    return r;
}

std::vector<std::pair<std::string, int> > create_std_vector_std_pair_std_string_int(unsigned int position) {
    std::vector<std::pair<std::string, int> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_pair_std_string_int(position + i));
    }
    return r;
}

}

namespace dogen {
namespace test_models {
namespace std_model {

class_j_generator::class_j_generator() : position_(0) { }

void class_j_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_std_pair_int_int(position + 0));
    v.prop_1(create_std_pair_std_string_std_string(position + 1));
    v.prop_2(create_std_vector_std_pair_std_string_int(position + 2));
}

class_j_generator::result_type
class_j_generator::create(const unsigned int position) {
    class_j r;
    class_j_generator::populate(position, r);
    return r;
}

class_j_generator::result_type*
class_j_generator::create_ptr(const unsigned int position) {
    class_j* p = new class_j();
    class_j_generator::populate(position, *p);
    return p;
}

class_j_generator::result_type
class_j_generator::operator()() {
    return create(position_++);
}

} } }
