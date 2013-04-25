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
#include "dogen/dia_to_sml/test_data/object_profile_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace dia_to_sml {

object_profile_generator::object_profile_generator() : position_(0) { }

void object_profile_generator::
populate(const unsigned int position, result_type& v) {
    v.is_uml_large_package(create_bool(position + 0));
    v.is_uml_class(create_bool(position + 1));
    v.is_uml_generalization(create_bool(position + 2));
    v.is_uml_association(create_bool(position + 3));
    v.is_uml_note(create_bool(position + 4));
    v.is_uml_message(create_bool(position + 5));
    v.is_uml_realization(create_bool(position + 6));
    v.is_enumeration(create_bool(position + 7));
    v.is_exception(create_bool(position + 8));
    v.is_entity(create_bool(position + 9));
    v.is_value(create_bool(position + 10));
    v.is_service(create_bool(position + 11));
    v.is_non_generatable(create_bool(position + 12));
    v.is_versioned(create_bool(position + 13));
    v.is_keyed(create_bool(position + 14));
    v.is_visitable(create_bool(position + 15));
}

object_profile_generator::result_type
object_profile_generator::create(const unsigned int position) {
    object_profile r;
    object_profile_generator::populate(position, r);
    return r;
}
object_profile_generator::result_type*
object_profile_generator::create_ptr(const unsigned int position) {
    object_profile* p = new object_profile();
    object_profile_generator::populate(position, *p);
    return p;
}

object_profile_generator::result_type
object_profile_generator::operator()() {
    return create(position_++);
}

} }
