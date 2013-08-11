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
#include "dogen/cpp/test_data/entity_td.hpp"
#include "dogen/cpp/test_data/scope_td.hpp"
#include "dogen/cpp/test_data/scope_types_td.hpp"

namespace {

dogen::cpp::scope_types
create_dogen_cpp_scope_types(const unsigned int position) {
    return dogen::cpp::scope_types_generator::create(position);
}

dogen::cpp::scope
create_dogen_cpp_scope(const unsigned int) {
    return dogen::cpp::scope();
}

std::list<dogen::cpp::scope> create_std_list_dogen_cpp_scope(unsigned int position) {
    std::list<dogen::cpp::scope> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_cpp_scope(position + i));
    }
    return r;
}

dogen::cpp::entity*
create_dogen_cpp_entity_ptr(const unsigned int position) {
    return dogen::cpp::entity_generator::create_ptr(position);
}

boost::shared_ptr<dogen::cpp::entity>
create_boost_shared_ptr_dogen_cpp_entity(unsigned int position) {
    boost::shared_ptr<dogen::cpp::entity> r(
        create_dogen_cpp_entity_ptr(position));
    return r;
}

std::list<boost::shared_ptr<dogen::cpp::entity> > create_std_list_boost_shared_ptr_dogen_cpp_entity_(unsigned int position) {
    std::list<boost::shared_ptr<dogen::cpp::entity> > r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_boost_shared_ptr_dogen_cpp_entity(position + i));
    }
    return r;
}

}

namespace dogen {
namespace cpp {

scope_generator::scope_generator() : position_(0) { }

void scope_generator::
populate(const unsigned int position, result_type& v) {
    v.type(create_dogen_cpp_scope_types(position + 0));
    v.inner_scopes(create_std_list_dogen_cpp_scope(position + 1));
    v.entities(create_std_list_boost_shared_ptr_dogen_cpp_entity_(position + 2));
}

scope_generator::result_type
scope_generator::create(const unsigned int position) {
    scope r;
    scope_generator::populate(position, r);
    return r;
}
scope_generator::result_type*
scope_generator::create_ptr(const unsigned int position) {
    scope* p = new scope();
    scope_generator::populate(position, *p);
    return p;
}

scope_generator::result_type
scope_generator::operator()() {
    return create(position_++);
}

} }
