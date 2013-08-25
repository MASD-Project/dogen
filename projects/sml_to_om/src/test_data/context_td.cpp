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
#include "dogen/om/test_data/cpp_project_td.hpp"
#include "dogen/sml_to_om/test_data/context_td.hpp"

namespace {

dogen::om::cpp_project
create_dogen_om_cpp_project(const unsigned int position) {
    return dogen::om::cpp_project_generator::create(position);
}

}

namespace dogen {
namespace sml_to_om {

context_generator::context_generator() : position_(0) { }

void context_generator::
populate(const unsigned int position, result_type& v) {
    v.project(create_dogen_om_cpp_project(position + 0));
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
