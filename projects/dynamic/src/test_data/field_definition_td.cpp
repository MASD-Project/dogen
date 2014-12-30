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
#include "dogen/dynamic/test_data/field_definition_td.hpp"
#include "dogen/dynamic/test_data/name_td.hpp"
#include "dogen/dynamic/test_data/scope_types_td.hpp"
#include "dogen/dynamic/test_data/value_types_td.hpp"

namespace {

dogen::dynamic::name
create_dogen_dynamic_name(const unsigned int position) {
    return dogen::dynamic::name_generator::create(position);
}

dogen::dynamic::value_types
create_dogen_dynamic_value_types(const unsigned int position) {
    return dogen::dynamic::value_types_generator::create(position);
}

dogen::dynamic::scope_types
create_dogen_dynamic_scope_types(const unsigned int position) {
    return dogen::dynamic::scope_types_generator::create(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace dynamic {

field_definition_generator::field_definition_generator() : position_(0) { }

void field_definition_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_dogen_dynamic_name(position + 0));
    v.type(create_dogen_dynamic_value_types(position + 1));
    v.scope(create_dogen_dynamic_scope_types(position + 2));
    v.is_mandatory(create_bool(position + 3));
}

field_definition_generator::result_type
field_definition_generator::create(const unsigned int position) {
    field_definition r;
    field_definition_generator::populate(position, r);
    return r;
}
field_definition_generator::result_type*
field_definition_generator::create_ptr(const unsigned int position) {
    field_definition* p = new field_definition();
    field_definition_generator::populate(position, *p);
    return p;
}

field_definition_generator::result_type
field_definition_generator::operator()() {
    return create(position_++);
}

} }
