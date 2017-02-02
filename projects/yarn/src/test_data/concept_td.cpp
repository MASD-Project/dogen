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
#include "dogen/yarn/test_data/concept_td.hpp"
#include "dogen/yarn/test_data/element_td.hpp"
#include "dogen/yarn/test_data/attribute_td.hpp"

namespace {

dogen::yarn::attribute
create_dogen_yarn_attribute(const unsigned int position) {
    return dogen::yarn::attribute_generator::create(position);
}

std::list<dogen::yarn::attribute> create_std_list_dogen_yarn_attribute(unsigned int position) {
    std::list<dogen::yarn::attribute> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_yarn_attribute(position + i));
    }
    return r;
}

dogen::yarn::name
create_dogen_yarn_name(const unsigned int position) {
    return dogen::yarn::name_generator::create(position);
}

std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> > create_std_unordered_map_dogen_yarn_name_std_list_dogen_yarn_attribute(unsigned int position) {
    std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_yarn_name(position + i), create_std_list_dogen_yarn_attribute(position + i)));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

std::list<dogen::yarn::name> create_std_list_dogen_yarn_name(unsigned int position) {
    std::list<dogen::yarn::name> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_yarn_name(position + i));
    }
    return r;
}

}

namespace dogen {
namespace yarn {

concept_generator::concept_generator() : position_(0) { }

void concept_generator::
populate(const unsigned int position, result_type& v) {
    dogen::yarn::element_generator::populate(position, v);
    v.all_attributes(create_std_list_dogen_yarn_attribute(position + 0));
    v.local_attributes(create_std_list_dogen_yarn_attribute(position + 1));
    v.inherited_attributes(create_std_unordered_map_dogen_yarn_name_std_list_dogen_yarn_attribute(position + 2));
    v.is_immutable(create_bool(position + 3));
    v.is_fluent(create_bool(position + 4));
    v.refines(create_std_list_dogen_yarn_name(position + 5));
    v.is_child(create_bool(position + 6));
}

concept_generator::result_type
concept_generator::create(const unsigned int position) {
    concept r;
    concept_generator::populate(position, r);
    return r;
}

concept_generator::result_type*
concept_generator::create_ptr(const unsigned int position) {
    concept* p = new concept();
    concept_generator::populate(position, *p);
    return p;
}

concept_generator::result_type
concept_generator::operator()() {
    return create(position_++);
}

} }
