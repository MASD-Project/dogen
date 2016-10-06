/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include <sstream>
#include "dogen/dynamic/test_data/ownership_hierarchy_td.hpp"
#include "dogen/dynamic/test_data/field_definition_types_td.hpp"
#include "dogen/dynamic/test_data/field_instance_definition_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::dynamic::ownership_hierarchy
create_dogen_dynamic_ownership_hierarchy(const unsigned int position) {
    return dogen::dynamic::ownership_hierarchy_generator::create(position);
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

dogen::dynamic::field_definition_types
create_dogen_dynamic_field_definition_types(const unsigned int position) {
    return dogen::dynamic::field_definition_types_generator::create(position);
}

}

namespace dogen {
namespace dynamic {

field_instance_definition_generator::field_instance_definition_generator() : position_(0) { }

void field_instance_definition_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_std_string(position + 0));
    v.ownership_hierarchy(create_dogen_dynamic_ownership_hierarchy(position + 1));
    v.value(create_std_list_std_string(position + 2));
    v.definition_types(create_dogen_dynamic_field_definition_types(position + 3));
}

field_instance_definition_generator::result_type
field_instance_definition_generator::create(const unsigned int position) {
    field_instance_definition r;
    field_instance_definition_generator::populate(position, r);
    return r;
}

field_instance_definition_generator::result_type*
field_instance_definition_generator::create_ptr(const unsigned int position) {
    field_instance_definition* p = new field_instance_definition();
    field_instance_definition_generator::populate(position, *p);
    return p;
}

field_instance_definition_generator::result_type
field_instance_definition_generator::operator()() {
    return create(position_++);
}

} }
