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
#include "dogen/sml/test_data/model_td.hpp"
#include "dogen/sml/test_data/qname_td.hpp"
#include "dogen/sml/test_data/module_td.hpp"
#include "dogen/sml/test_data/object_td.hpp"
#include "dogen/sml/test_data/concept_td.hpp"
#include "dogen/sml/test_data/primitive_td.hpp"
#include "dogen/dynamic/test_data/object_td.hpp"
#include "dogen/sml/test_data/enumeration_td.hpp"
#include "dogen/sml/test_data/origin_types_td.hpp"
#include "dogen/sml/test_data/generation_types_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::dynamic::object
create_dogen_dynamic_object(const unsigned int position) {
    return dogen::dynamic::object_generator::create(position);
}

dogen::sml::qname
create_dogen_sml_qname(const unsigned int position) {
    return dogen::sml::qname_generator::create(position);
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

std::unordered_map<dogen::sml::qname, dogen::sml::origin_types> create_std_unordered_map_dogen_sml_qname_dogen_sml_origin_types(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::sml::origin_types> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_sml_origin_types(position + i)));
    }
    return r;
}

std::unordered_set<dogen::sml::qname> create_std_unordered_set_dogen_sml_qname(unsigned int position) {
    std::unordered_set<dogen::sml::qname> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_dogen_sml_qname(position + i));
    }
    return r;
}

dogen::sml::module
create_dogen_sml_module(const unsigned int position) {
    return dogen::sml::module_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::sml::module> create_std_unordered_map_dogen_sml_qname_dogen_sml_module(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::sml::module> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_sml_module(position + i)));
    }
    return r;
}

dogen::sml::concept
create_dogen_sml_concept(const unsigned int position) {
    return dogen::sml::concept_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::sml::concept> create_std_unordered_map_dogen_sml_qname_dogen_sml_concept(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::sml::concept> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_sml_concept(position + i)));
    }
    return r;
}

dogen::sml::primitive
create_dogen_sml_primitive(const unsigned int position) {
    return dogen::sml::primitive_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::sml::primitive> create_std_unordered_map_dogen_sml_qname_dogen_sml_primitive(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::sml::primitive> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_sml_primitive(position + i)));
    }
    return r;
}

dogen::sml::enumeration
create_dogen_sml_enumeration(const unsigned int position) {
    return dogen::sml::enumeration_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::sml::enumeration> create_std_unordered_map_dogen_sml_qname_dogen_sml_enumeration(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::sml::enumeration> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_sml_enumeration(position + i)));
    }
    return r;
}

dogen::sml::object
create_dogen_sml_object(const unsigned int position) {
    return dogen::sml::object_generator::create(position);
}

std::unordered_map<dogen::sml::qname, dogen::sml::object> create_std_unordered_map_dogen_sml_qname_dogen_sml_object(unsigned int position) {
    std::unordered_map<dogen::sml::qname, dogen::sml::object> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_sml_qname(position + i), create_dogen_sml_object(position + i)));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace sml {

model_generator::model_generator() : position_(0) { }

void model_generator::
populate(const unsigned int position, result_type& v) {
    v.documentation(create_std_string(position + 0));
    v.extensions(create_dogen_dynamic_object(position + 1));
    v.name(create_dogen_sml_qname(position + 2));
    v.generation_type(create_dogen_sml_generation_types(position + 3));
    v.origin_type(create_dogen_sml_origin_types(position + 4));
    v.containing_module(create_boost_optional_dogen_sml_qname(position + 5));
    v.references(create_std_unordered_map_dogen_sml_qname_dogen_sml_origin_types(position + 6));
    v.leaves(create_std_unordered_set_dogen_sml_qname(position + 7));
    v.modules(create_std_unordered_map_dogen_sml_qname_dogen_sml_module(position + 8));
    v.concepts(create_std_unordered_map_dogen_sml_qname_dogen_sml_concept(position + 9));
    v.primitives(create_std_unordered_map_dogen_sml_qname_dogen_sml_primitive(position + 10));
    v.enumerations(create_std_unordered_map_dogen_sml_qname_dogen_sml_enumeration(position + 11));
    v.objects(create_std_unordered_map_dogen_sml_qname_dogen_sml_object(position + 12));
    v.is_target(create_bool(position + 13));
    v.has_generatable_types(create_bool(position + 14));
}

model_generator::result_type
model_generator::create(const unsigned int position) {
    model r;
    model_generator::populate(position, r);
    return r;
}

model_generator::result_type*
model_generator::create_ptr(const unsigned int position) {
    model* p = new model();
    model_generator::populate(position, *p);
    return p;
}

model_generator::result_type
model_generator::operator()() {
    return create(position_++);
}

} }
