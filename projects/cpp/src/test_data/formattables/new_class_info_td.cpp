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
#include "dogen/cpp/test_data/formattables/state_td.hpp"
#include "dogen/cpp/test_data/formattables/entity_td.hpp"
#include "dogen/cpp/test_data/formattables/abilities_td.hpp"
#include "dogen/cpp/test_data/formattables/inheritance_td.hpp"
#include "dogen/cpp/test_data/formattables/class_aspects_td.hpp"
#include "dogen/cpp/test_data/formattables/new_class_info_td.hpp"

namespace {

dogen::cpp::formattables::state
create_dogen_cpp_formattables_state(const unsigned int position) {
    return dogen::cpp::formattables::state_generator::create(position);
}

dogen::cpp::formattables::inheritance
create_dogen_cpp_formattables_inheritance(const unsigned int position) {
    return dogen::cpp::formattables::inheritance_generator::create(position);
}

dogen::cpp::formattables::abilities
create_dogen_cpp_formattables_abilities(const unsigned int position) {
    return dogen::cpp::formattables::abilities_generator::create(position);
}

dogen::cpp::formattables::class_aspects
create_dogen_cpp_formattables_class_aspects(const unsigned int position) {
    return dogen::cpp::formattables::class_aspects_generator::create(position);
}

}

namespace dogen {
namespace cpp {
namespace formattables {

new_class_info_generator::new_class_info_generator() : position_(0) { }

void new_class_info_generator::
populate(const unsigned int position, result_type& v) {
    dogen::cpp::formattables::entity_generator::populate(position, v);
    v.state(create_dogen_cpp_formattables_state(position + 0));
    v.inheritance(create_dogen_cpp_formattables_inheritance(position + 1));
    v.abilities(create_dogen_cpp_formattables_abilities(position + 2));
    v.aspects(create_dogen_cpp_formattables_class_aspects(position + 3));
}

new_class_info_generator::result_type
new_class_info_generator::create(const unsigned int position) {
    new_class_info r;
    new_class_info_generator::populate(position, r);
    return r;
}
new_class_info_generator::result_type*
new_class_info_generator::create_ptr(const unsigned int position) {
    new_class_info* p = new new_class_info();
    new_class_info_generator::populate(position, *p);
    return p;
}

new_class_info_generator::result_type
new_class_info_generator::operator()() {
    return create(position_++);
}

} } }
