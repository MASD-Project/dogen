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
#include "dogen/cpp/test_data/base_specifier_td.hpp"
#include "dogen/cpp/test_data/class_head_td.hpp"
#include "dogen/cpp/test_data/class_key_types_td.hpp"
#include "dogen/cpp/test_data/qualified_id_td.hpp"

namespace {

dogen::cpp::class_key_types
create_dogen_cpp_class_key_types(const unsigned int position) {
    return dogen::cpp::class_key_types_generator::create(position);
}

dogen::cpp::qualified_id
create_dogen_cpp_qualified_id(const unsigned int position) {
    return dogen::cpp::qualified_id_generator::create(position);
}

dogen::cpp::base_specifier
create_dogen_cpp_base_specifier(const unsigned int position) {
    return dogen::cpp::base_specifier_generator::create(position);
}

std::list<dogen::cpp::base_specifier> create_std_list_dogen_cpp_base_specifier(unsigned int position) {
    std::list<dogen::cpp::base_specifier> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_cpp_base_specifier(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace cpp {

class_head_generator::class_head_generator() : position_(0) { }

void class_head_generator::
populate(const unsigned int position, result_type& v) {
    v.key(create_dogen_cpp_class_key_types(position + 0));
    v.name(create_dogen_cpp_qualified_id(position + 1));
    v.base_specifier_list(create_std_list_dogen_cpp_base_specifier(position + 2));
    v.is_final(create_bool(position + 3));
}

class_head_generator::result_type
class_head_generator::create(const unsigned int position) {
    class_head r;
    class_head_generator::populate(position, r);
    return r;
}
class_head_generator::result_type*
class_head_generator::create_ptr(const unsigned int position) {
    class_head* p = new class_head();
    class_head_generator::populate(position, *p);
    return p;
}

class_head_generator::result_type
class_head_generator::operator()() {
    return create(position_++);
}

} }
