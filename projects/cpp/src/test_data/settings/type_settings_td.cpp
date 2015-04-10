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
#include "dogen/cpp/test_data/settings/type_settings_td.hpp"
#include "dogen/cpp/test_data/formattables/family_types_td.hpp"

namespace {

dogen::cpp::formattables::family_types
create_dogen_cpp_formattables_family_types(const unsigned int position) {
    return dogen::cpp::formattables::family_types_generator::create(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace cpp {
namespace settings {

type_settings_generator::type_settings_generator() : position_(0) { }

void type_settings_generator::
populate(const unsigned int position, result_type& v) {
    v.family_type(create_dogen_cpp_formattables_family_types(position + 0));
    v.requires_manual_default_constructor(create_bool(position + 1));
    v.requires_manual_move_constructor(create_bool(position + 2));
}

type_settings_generator::result_type
type_settings_generator::create(const unsigned int position) {
    type_settings r;
    type_settings_generator::populate(position, r);
    return r;
}
type_settings_generator::result_type*
type_settings_generator::create_ptr(const unsigned int position) {
    type_settings* p = new type_settings();
    type_settings_generator::populate(position, *p);
    return p;
}

type_settings_generator::result_type
type_settings_generator::operator()() {
    return create(position_++);
}

} } }
