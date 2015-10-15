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
#include "dogen/yarn/test_data/name_td.hpp"
#include "dogen/yarn/test_data/type_td.hpp"
#include "dogen/yarn/test_data/object_td.hpp"
#include "dogen/yarn/test_data/property_td.hpp"
#include "dogen/yarn/test_data/object_types_td.hpp"
#include "dogen/yarn/test_data/relationship_types_td.hpp"

namespace {

dogen::yarn::property
create_dogen_yarn_property(const unsigned int position) {
    return dogen::yarn::property_generator::create(position);
}

std::list<dogen::yarn::property> create_std_list_dogen_yarn_property(unsigned int position) {
    std::list<dogen::yarn::property> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_yarn_property(position + i));
    }
    return r;
}

dogen::yarn::name
create_dogen_yarn_name(const unsigned int position) {
    return dogen::yarn::name_generator::create(position);
}

std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> > create_std_unordered_map_dogen_yarn_name_std_list_dogen_yarn_property_(unsigned int position) {
    std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_yarn_name(position + i), create_std_list_dogen_yarn_property(position + i)));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

dogen::yarn::relationship_types
create_dogen_yarn_relationship_types(const unsigned int position) {
    return dogen::yarn::relationship_types_generator::create(position);
}

std::list<dogen::yarn::name> create_std_list_dogen_yarn_name(unsigned int position) {
    std::list<dogen::yarn::name> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_yarn_name(position + i));
    }
    return r;
}

std::unordered_map<dogen::yarn::relationship_types, std::list<dogen::yarn::name> > create_std_unordered_map_dogen_yarn_relationship_types_std_list_dogen_yarn_name_(unsigned int position) {
    std::unordered_map<dogen::yarn::relationship_types, std::list<dogen::yarn::name> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_yarn_relationship_types(position + i), create_std_list_dogen_yarn_name(position + i)));
    }
    return r;
}

dogen::yarn::object_types
create_dogen_yarn_object_types(const unsigned int position) {
    return dogen::yarn::object_types_generator::create(position);
}

}

namespace dogen {
namespace yarn {

object_generator::object_generator() : position_(0) { }

void object_generator::
populate(const unsigned int position, result_type& v) {
    dogen::yarn::type_generator::populate(position, v);
    v.all_properties(create_std_list_dogen_yarn_property(position + 0));
    v.local_properties(create_std_list_dogen_yarn_property(position + 1));
    v.inherited_properties(create_std_unordered_map_dogen_yarn_name_std_list_dogen_yarn_property_(position + 2));
    v.is_parent(create_bool(position + 3));
    v.is_visitable(create_bool(position + 4));
    v.is_immutable(create_bool(position + 5));
    v.is_fluent(create_bool(position + 6));
    v.is_child(create_bool(position + 7));
    v.is_original_parent_visitable(create_bool(position + 8));
    v.relationships(create_std_unordered_map_dogen_yarn_relationship_types_std_list_dogen_yarn_name_(position + 9));
    v.object_type(create_dogen_yarn_object_types(position + 10));
    v.is_final(create_bool(position + 11));
}

object_generator::result_type
object_generator::create(const unsigned int position) {
    object r;
    object_generator::populate(position, r);
    return r;
}

object_generator::result_type*
object_generator::create_ptr(const unsigned int position) {
    object* p = new object();
    object_generator::populate(position, *p);
    return p;
}

object_generator::result_type
object_generator::operator()() {
    return create(position_++);
}

} }
