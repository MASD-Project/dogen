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
#include "dogen/annotations/test_data/profile_td.hpp"
#include "dogen/annotations/test_data/annotation_td.hpp"
#include "dogen/annotations/test_data/field_instance_definition_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

dogen::annotations::field_instance_definition
create_dogen_annotations_field_instance_definition(const unsigned int position) {
    return dogen::annotations::field_instance_definition_generator::create(position);
}

std::unordered_map<std::string, dogen::annotations::field_instance_definition> create_std_unordered_map_std_string_dogen_annotations_field_instance_definition(unsigned int position) {
    std::unordered_map<std::string, dogen::annotations::field_instance_definition> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_annotations_field_instance_definition(position + i)));
    }
    return r;
}

dogen::annotations::annotation
create_dogen_annotations_annotation(const unsigned int position) {
    return dogen::annotations::annotation_generator::create(position);
}

}

namespace dogen {
namespace annotations {

profile_generator::profile_generator() : position_(0) { }

void profile_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_std_string(position + 0));
    v.parents(create_std_list_std_string(position + 1));
    v.instance_definitions(create_std_unordered_map_std_string_dogen_annotations_field_instance_definition(position + 2));
    v.content(create_dogen_annotations_annotation(position + 3));
}

profile_generator::result_type
profile_generator::create(const unsigned int position) {
    profile r;
    profile_generator::populate(position, r);
    return r;
}

profile_generator::result_type*
profile_generator::create_ptr(const unsigned int position) {
    profile* p = new profile();
    profile_generator::populate(position, *p);
    return p;
}

profile_generator::result_type
profile_generator::operator()() {
    return create(position_++);
}

} }
