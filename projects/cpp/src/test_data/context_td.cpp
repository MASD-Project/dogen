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
#include "dogen/cpp/test_data/class_info_td.hpp"
#include "dogen/cpp/test_data/context_td.hpp"
#include "dogen/sml/test_data/qname_td.hpp"

namespace {

dogen::sml::qname
create_dogen_sml_qname(const unsigned int position) {
    return dogen::sml::qname_generator::create(position);
}

dogen::cpp::class_info
create_dogen_cpp_class_info(const unsigned int position) {
    return dogen::cpp::class_info_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::cpp::class_info> create_std_unordered_map_dogen_sml_qname_dogen_cpp_class_info(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::cpp::class_info> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_cpp_class_info(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace cpp {

context_generator::context_generator() : position_(0) { }

void context_generator::
populate(const unsigned int position, result_type& v) {
    v.qname_to_class_info(create_std_unordered_map_dogen_sml_qname_dogen_cpp_class_info(position + 0));
}

context_generator::result_type
context_generator::create(const unsigned int position) {
    context r;
    context_generator::populate(position, r);
    return r;
}
context_generator::result_type*
context_generator::create_ptr(const unsigned int position) {
    context* p = new context();
    context_generator::populate(position, *p);
    return p;
}

context_generator::result_type
context_generator::operator()() {
    return create(position_++);
}

} }
