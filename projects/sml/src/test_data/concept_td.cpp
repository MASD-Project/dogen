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
#include "dogen/sml/test_data/qname_td.hpp"
#include "dogen/sml/test_data/concept_td.hpp"
#include "dogen/sml/test_data/property_td.hpp"
#include "dogen/sml/test_data/operation_td.hpp"
#include "dogen/dynamic/test_data/object_td.hpp"
#include "dogen/sml/test_data/origin_types_td.hpp"
#include "dogen/sml/test_data/generation_types_td.hpp"

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

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::dynamic::object
create_dogen_dynamic_object(const unsigned int position) {
    return dogen::dynamic::object_generator::create(position);
}

dogen::sml::generation_types
create_dogen_sml_generation_types(const unsigned int position) {
    return dogen::sml::generation_types_generator::create(position);
}

dogen::sml::origin_types
create_dogen_sml_origin_types(const unsigned int position) {
    return dogen::sml::origin_types_generator::create(position);
}

boost::optional<dogen::sml::qname>
create_boost_optional_dogen_sml_qname(unsigned int position) {
    boost::optional<dogen::sml::qname> r(
        create_dogen_sml_qname(position));
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

std::list<dogen::sml::qname> create_std_list_dogen_sml_qname(unsigned int position) {
    std::list<dogen::sml::qname> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_sml_qname(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace sml {

concept_generator::concept_generator() : position_(0) { }

void concept_generator::
populate(const unsigned int position, result_type& v) {
    v.all_properties(create_std_list_dogen_sml_property(position + 0));
    v.local_properties(create_std_list_dogen_sml_property(position + 1));
    v.inherited_properties(create_std_unordered_map_dogen_sml_qname_std_list_dogen_sml_property_(position + 2));
    v.documentation(create_std_string(position + 3));
    v.extensions(create_dogen_dynamic_object(position + 4));
    v.name(create_dogen_sml_qname(position + 5));
    v.generation_type(create_dogen_sml_generation_types(position + 6));
    v.origin_type(create_dogen_sml_origin_types(position + 7));
    v.containing_module(create_boost_optional_dogen_sml_qname(position + 8));
    v.operations(create_std_list_dogen_sml_operation(position + 9));
    v.refines(create_std_list_dogen_sml_qname(position + 10));
    v.is_parent(create_bool(position + 11));
    v.is_child(create_bool(position + 12));
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
