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
#include "dogen/yarn/test_data/name_td.hpp"
#include "dogen/yarn/test_data/module_td.hpp"
#include "dogen/yarn/test_data/object_td.hpp"
#include "dogen/yarn/test_data/concept_td.hpp"
#include "dogen/dynamic/test_data/object_td.hpp"
#include "dogen/yarn/test_data/primitive_td.hpp"
#include "dogen/yarn/test_data/enumeration_td.hpp"
#include "dogen/yarn/test_data/origin_types_td.hpp"
#include "dogen/yarn/test_data/generation_types_td.hpp"
#include "dogen/yarn/test_data/intermediate_model_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
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

dogen::yarn::name
create_dogen_yarn_name(const unsigned int position) {
    return dogen::yarn::name_generator::create(position);
}

dogen::yarn::generation_types
create_dogen_yarn_generation_types(const unsigned int position) {
    return dogen::yarn::generation_types_generator::create(position);
}

dogen::yarn::origin_types
create_dogen_yarn_origin_types(const unsigned int position) {
    return dogen::yarn::origin_types_generator::create(position);
}

boost::optional<dogen::yarn::name>
create_boost_optional_dogen_yarn_name(unsigned int position) {
    boost::optional<dogen::yarn::name> r(
        create_dogen_yarn_name(position));
    return r;
}

std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types> create_std_unordered_map_dogen_yarn_name_dogen_yarn_origin_types(unsigned int position) {
    std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_yarn_name(position + i), create_dogen_yarn_origin_types(position + i)));
    }
    return r;
}

std::unordered_set<dogen::yarn::name> create_std_unordered_set_dogen_yarn_name(unsigned int position) {
    std::unordered_set<dogen::yarn::name> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_dogen_yarn_name(position + i));
    }
    return r;
}

dogen::yarn::module
create_dogen_yarn_module(const unsigned int position) {
    return dogen::yarn::module_generator::create(position);
}

std::unordered_map<dogen::yarn::name, dogen::yarn::module> create_std_unordered_map_dogen_yarn_name_dogen_yarn_module(unsigned int position) {
    std::unordered_map<dogen::yarn::name, dogen::yarn::module> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_yarn_name(position + i), create_dogen_yarn_module(position + i)));
    }
    return r;
}

dogen::yarn::concept
create_dogen_yarn_concept(const unsigned int position) {
    return dogen::yarn::concept_generator::create(position);
}

std::unordered_map<dogen::yarn::name, dogen::yarn::concept> create_std_unordered_map_dogen_yarn_name_dogen_yarn_concept(unsigned int position) {
    std::unordered_map<dogen::yarn::name, dogen::yarn::concept> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_yarn_name(position + i), create_dogen_yarn_concept(position + i)));
    }
    return r;
}

dogen::yarn::primitive
create_dogen_yarn_primitive(const unsigned int position) {
    return dogen::yarn::primitive_generator::create(position);
}

std::unordered_map<dogen::yarn::name, dogen::yarn::primitive> create_std_unordered_map_dogen_yarn_name_dogen_yarn_primitive(unsigned int position) {
    std::unordered_map<dogen::yarn::name, dogen::yarn::primitive> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_yarn_name(position + i), create_dogen_yarn_primitive(position + i)));
    }
    return r;
}

dogen::yarn::enumeration
create_dogen_yarn_enumeration(const unsigned int position) {
    return dogen::yarn::enumeration_generator::create(position);
}

std::unordered_map<dogen::yarn::name, dogen::yarn::enumeration> create_std_unordered_map_dogen_yarn_name_dogen_yarn_enumeration(unsigned int position) {
    std::unordered_map<dogen::yarn::name, dogen::yarn::enumeration> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_yarn_name(position + i), create_dogen_yarn_enumeration(position + i)));
    }
    return r;
}

dogen::yarn::object
create_dogen_yarn_object(const unsigned int position) {
    return dogen::yarn::object_generator::create(position);
}

std::unordered_map<dogen::yarn::name, dogen::yarn::object> create_std_unordered_map_dogen_yarn_name_dogen_yarn_object(unsigned int position) {
    std::unordered_map<dogen::yarn::name, dogen::yarn::object> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_yarn_name(position + i), create_dogen_yarn_object(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace yarn {

intermediate_model_generator::intermediate_model_generator() : position_(0) { }

void intermediate_model_generator::
populate(const unsigned int position, result_type& v) {
    v.in_global_namespace(create_bool(position + 0));
    v.original_model_name(create_std_string(position + 1));
    v.documentation(create_std_string(position + 2));
    v.extensions(create_dogen_dynamic_object(position + 3));
    v.name(create_dogen_yarn_name(position + 4));
    v.generation_type(create_dogen_yarn_generation_types(position + 5));
    v.origin_type(create_dogen_yarn_origin_types(position + 6));
    v.containing_module(create_boost_optional_dogen_yarn_name(position + 7));
    v.references(create_std_unordered_map_dogen_yarn_name_dogen_yarn_origin_types(position + 8));
    v.leaves(create_std_unordered_set_dogen_yarn_name(position + 9));
    v.modules(create_std_unordered_map_dogen_yarn_name_dogen_yarn_module(position + 10));
    v.concepts(create_std_unordered_map_dogen_yarn_name_dogen_yarn_concept(position + 11));
    v.primitives(create_std_unordered_map_dogen_yarn_name_dogen_yarn_primitive(position + 12));
    v.enumerations(create_std_unordered_map_dogen_yarn_name_dogen_yarn_enumeration(position + 13));
    v.objects(create_std_unordered_map_dogen_yarn_name_dogen_yarn_object(position + 14));
    v.is_target(create_bool(position + 15));
    v.has_generatable_types(create_bool(position + 16));
}

intermediate_model_generator::result_type
intermediate_model_generator::create(const unsigned int position) {
    intermediate_model r;
    intermediate_model_generator::populate(position, r);
    return r;
}

intermediate_model_generator::result_type*
intermediate_model_generator::create_ptr(const unsigned int position) {
    intermediate_model* p = new intermediate_model();
    intermediate_model_generator::populate(position, *p);
    return p;
}

intermediate_model_generator::result_type
intermediate_model_generator::operator()() {
    return create(position_++);
}

} }
