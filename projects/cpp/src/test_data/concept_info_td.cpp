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
#include "dogen/cpp/test_data/concept_info_td.hpp"
#include "dogen/cpp/test_data/entity_td.hpp"
#include "dogen/cpp/test_data/state_td.hpp"

namespace {

dogen::cpp::state
create_dogen_cpp_state(const unsigned int position) {
    return dogen::cpp::state_generator::create(position);
}

}

namespace dogen {
namespace cpp {

concept_info_generator::concept_info_generator() : position_(0) { }

void concept_info_generator::
populate(const unsigned int position, result_type& v) {
    dogen::cpp::entity_generator::populate(position, v);
    v.state(create_dogen_cpp_state(position + 0));
}

concept_info_generator::result_type
concept_info_generator::create(const unsigned int position) {
    concept_info r;
    concept_info_generator::populate(position, r);
    return r;
}
concept_info_generator::result_type*
concept_info_generator::create_ptr(const unsigned int position) {
    concept_info* p = new concept_info();
    concept_info_generator::populate(position, *p);
    return p;
}

concept_info_generator::result_type
concept_info_generator::operator()() {
    return create(position_++);
}

} }
