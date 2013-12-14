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
#include "dogen/sml/test_data/abstract_object_td.hpp"
#include "dogen/sml/test_data/entity_td.hpp"
#include "dogen/sml/test_data/object_td.hpp"
#include "dogen/sml/test_data/object_types_td.hpp"
#include "dogen/sml/test_data/operation_td.hpp"
#include "dogen/sml/test_data/property_td.hpp"
#include "dogen/sml/test_data/qname_td.hpp"
#include "dogen/sml/test_data/relationship_types_td.hpp"
#include "dogen/sml/test_data/repository_td.hpp"
#include "dogen/sml/test_data/service_td.hpp"
#include "dogen/sml/test_data/type_td.hpp"
#include "dogen/sml/test_data/value_object_td.hpp"

namespace {

dogen::sml::property
create_dogen_sml_property(const unsigned int position) {
    return dogen::sml::property_generator::create(position);
}

std::list<dogen::sml::property> create_std_list_dogen_sml_property(unsigned int position) {
    std::list<dogen::sml::property> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_sml_property(position + i));
    }
    return r;
}

dogen::sml::qname
create_dogen_sml_qname(const unsigned int position) {
    return dogen::sml::qname_generator::create(position);
}

std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> > create_std_unordered_map_dogen_sml_qname_std_list_dogen_sml_property_(unsigned int position) {
    std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_std_list_dogen_sml_property(position + i)));
    }
    return r;
}

dogen::sml::operation
create_dogen_sml_operation(const unsigned int position) {
    return dogen::sml::operation_generator::create(position);
}

std::list<dogen::sml::operation> create_std_list_dogen_sml_operation(unsigned int position) {
    std::list<dogen::sml::operation> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_sml_operation(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

unsigned int create_unsigned_int(const unsigned int position) {
    return static_cast<unsigned int>(position);
}

dogen::sml::relationship_types
create_dogen_sml_relationship_types(const unsigned int position) {
    return dogen::sml::relationship_types_generator::create(position);
}

std::list<dogen::sml::qname> create_std_list_dogen_sml_qname(unsigned int position) {
    std::list<dogen::sml::qname> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_sml_qname(position + i));
    }
    return r;
}

std::unordered_map<dogen::sml::relationship_types, std::list<dogen::sml::qname> > create_std_unordered_map_dogen_sml_relationship_types_std_list_dogen_sml_qname_(unsigned int position) {
    std::unordered_map<dogen::sml::relationship_types, std::list<dogen::sml::qname> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_sml_relationship_types(position + i), create_std_list_dogen_sml_qname(position + i)));
    }
    return r;
}

dogen::sml::object_types
create_dogen_sml_object_types(const unsigned int position) {
    return dogen::sml::object_types_generator::create(position);
}

}

namespace dogen {
namespace sml {


void abstract_object_generator::
populate(const unsigned int position, result_type& v) {
    dogen::sml::type_generator::populate(position, v);
    v.all_properties(create_std_list_dogen_sml_property(position + 0));
    v.local_properties(create_std_list_dogen_sml_property(position + 1));
    v.inherited_properties(create_std_unordered_map_dogen_sml_qname_std_list_dogen_sml_property_(position + 2));
    v.operations(create_std_list_dogen_sml_operation(position + 3));
    v.is_parent(create_bool(position + 4));
    v.number_of_type_arguments(create_unsigned_int(position + 5));
    v.is_visitable(create_bool(position + 6));
    v.is_immutable(create_bool(position + 7));
    v.is_versioned(create_bool(position + 8));
    v.is_comparable(create_bool(position + 9));
    v.is_fluent(create_bool(position + 10));
    v.is_child(create_bool(position + 11));
    v.relationships(create_std_unordered_map_dogen_sml_relationship_types_std_list_dogen_sml_qname_(position + 12));
    v.is_inheritance_root(create_bool(position + 13));
    v.object_type(create_dogen_sml_object_types(position + 14));
}

abstract_object_generator::result_type*
abstract_object_generator::create_ptr(const unsigned int position) {
    if ((position % 4) == 0)
        return dogen::sml::service_generator::create_ptr(position);
    if ((position % 4) == 1)
        return dogen::sml::repository_generator::create_ptr(position);
    if ((position % 4) == 2)
        return dogen::sml::value_object_generator::create_ptr(position);
    if ((position % 4) == 3)
        return dogen::sml::object_generator::create_ptr(position);
    return dogen::sml::entity_generator::create_ptr(position);
}


} }
