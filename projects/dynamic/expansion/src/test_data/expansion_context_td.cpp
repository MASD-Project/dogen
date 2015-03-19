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
#include "dogen/dynamic/expansion/test_data/expansion_context_td.hpp"
#include "dogen/dynamic/schema/test_data/field_definition_td.hpp"
#include "dogen/dynamic/schema/test_data/object_td.hpp"
#include "dogen/sml/test_data/model_td.hpp"

namespace {

dogen::sml::model
create_dogen_sml_model(const unsigned int position) {
    return dogen::sml::model_generator::create(position);
}

dogen::dynamic::schema::object
create_dogen_dynamic_schema_object(const unsigned int position) {
    return dogen::dynamic::schema::object_generator::create(position);
}

dogen::dynamic::schema::field_definition
create_dogen_dynamic_schema_field_definition(const unsigned int position) {
    return dogen::dynamic::schema::field_definition_generator::create(position);
}

std::list<dogen::dynamic::schema::field_definition> create_std_list_dogen_dynamic_schema_field_definition(unsigned int position) {
    std::list<dogen::dynamic::schema::field_definition> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_dynamic_schema_field_definition(position + i));
    }
    return r;
}

}

namespace dogen {
namespace dynamic {
namespace expansion {

expansion_context_generator::expansion_context_generator() : position_(0) { }

void expansion_context_generator::
populate(const unsigned int position, result_type& v) {
    v.model(create_dogen_sml_model(position + 0));
    v.root(create_dogen_dynamic_schema_object(position + 1));
    v.field_definitions(create_std_list_dogen_dynamic_schema_field_definition(position + 2));
}

expansion_context_generator::result_type
expansion_context_generator::create(const unsigned int position) {
    expansion_context r;
    expansion_context_generator::populate(position, r);
    return r;
}
expansion_context_generator::result_type*
expansion_context_generator::create_ptr(const unsigned int position) {
    expansion_context* p = new expansion_context();
    expansion_context_generator::populate(position, *p);
    return p;
}

expansion_context_generator::result_type
expansion_context_generator::operator()() {
    return create(position_++);
}

} } }
