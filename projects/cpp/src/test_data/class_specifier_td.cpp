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
#include "dogen/cpp/test_data/class_head_td.hpp"
#include "dogen/cpp/test_data/class_specifier_td.hpp"
#include "dogen/cpp/test_data/entity_td.hpp"
#include "dogen/cpp/test_data/member_specification_td.hpp"

namespace {

dogen::cpp::class_head
create_dogen_cpp_class_head(const unsigned int position) {
    return dogen::cpp::class_head_generator::create(position);
}

dogen::cpp::member_specification
create_dogen_cpp_member_specification(const unsigned int position) {
    return dogen::cpp::member_specification_generator::create(position);
}

std::list<dogen::cpp::member_specification> create_std_list_dogen_cpp_member_specification(unsigned int position) {
    std::list<dogen::cpp::member_specification> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_cpp_member_specification(position + i));
    }
    return r;
}

}

namespace dogen {
namespace cpp {

class_specifier_generator::class_specifier_generator() : position_(0) { }

void class_specifier_generator::
populate(const unsigned int position, result_type& v) {
    dogen::cpp::entity_generator::populate(position, v);
    v.head(create_dogen_cpp_class_head(position + 0));
    v.members(create_std_list_dogen_cpp_member_specification(position + 1));
}

class_specifier_generator::result_type
class_specifier_generator::create(const unsigned int position) {
    class_specifier r;
    class_specifier_generator::populate(position, r);
    return r;
}
class_specifier_generator::result_type*
class_specifier_generator::create_ptr(const unsigned int position) {
    class_specifier* p = new class_specifier();
    class_specifier_generator::populate(position, *p);
    return p;
}

class_specifier_generator::result_type
class_specifier_generator::operator()() {
    return create(position_++);
}

} }
