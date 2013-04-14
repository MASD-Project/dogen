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
#include <sstream>
#include "dogen/dia/test_data/composite_td.hpp"
#include "dogen/dia_to_sml/test_data/object_types_td.hpp"
#include "dogen/dia_to_sml/test_data/processed_object_td.hpp"
#include "dogen/dia_to_sml/test_data/stereotypes_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::dia_to_sml::object_types
create_dogen_dia_to_sml_object_types(const unsigned int position) {
    return dogen::dia_to_sml::object_types_generator::create(position);
}

dogen::dia_to_sml::stereotypes
create_dogen_dia_to_sml_stereotypes(const unsigned int position) {
    return dogen::dia_to_sml::stereotypes_generator::create(position);
}

dogen::dia::composite
create_dogen_dia_composite(const unsigned int position) {
    return dogen::dia::composite_generator::create(position);
}

std::vector<dogen::dia::composite> create_std_vector_dogen_dia_composite(unsigned int position) {
    std::vector<dogen::dia::composite> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_dia_composite(position + i));
    }
    return r;
}

}

namespace dogen {
namespace dia_to_sml {

processed_object_generator::processed_object_generator() : position_(0) { }

void processed_object_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_std_string(position + 0));
    v.object_type(create_dogen_dia_to_sml_object_types(position + 1));
    v.stereotype(create_dogen_dia_to_sml_stereotypes(position + 2));
    v.comment(create_std_string(position + 3));
    v.uml_attributes(create_std_vector_dogen_dia_composite(position + 4));
    v.parent_id(create_std_string(position + 5));
}

processed_object_generator::result_type
processed_object_generator::create(const unsigned int position) {
    processed_object r;
    processed_object_generator::populate(position, r);
    return r;
}
processed_object_generator::result_type*
processed_object_generator::create_ptr(const unsigned int position) {
    processed_object* p = new processed_object();
    processed_object_generator::populate(position, *p);
    return p;
}

processed_object_generator::result_type
processed_object_generator::operator()() {
    return create(position_++);
}

} }
