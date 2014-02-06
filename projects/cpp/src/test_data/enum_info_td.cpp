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
#include "dogen/cpp/test_data/enum_info_td.hpp"
#include "dogen/cpp/test_data/enumerator_info_td.hpp"

namespace {

dogen::cpp::enumerator_info
create_dogen_cpp_enumerator_info(const unsigned int position) {
    return dogen::cpp::enumerator_info_generator::create(position);
}

std::list<dogen::cpp::enumerator_info> create_std_list_dogen_cpp_enumerator_info(unsigned int position) {
    std::list<dogen::cpp::enumerator_info> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_cpp_enumerator_info(position + i));
    }
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

enum_info_generator::enum_info_generator() : position_(0) { }

void enum_info_generator::
populate(const unsigned int position, result_type& v) {
    dogen::cpp::entity_generator::populate(position, v);
    v.enumerators(create_std_list_dogen_cpp_enumerator_info(position + 0));
    v.type(create_std_string(position + 1));
}

enum_info_generator::result_type
enum_info_generator::create(const unsigned int position) {
    enum_info r;
    enum_info_generator::populate(position, r);
    return r;
}
enum_info_generator::result_type*
enum_info_generator::create_ptr(const unsigned int position) {
    enum_info* p = new enum_info();
    enum_info_generator::populate(position, *p);
    return p;
}

enum_info_generator::result_type
enum_info_generator::operator()() {
    return create(position_++);
}

} }
