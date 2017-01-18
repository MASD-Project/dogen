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
#include "dogen/yarn/test_data/element_td.hpp"
#include "dogen/yarn/test_data/indices_td.hpp"
#include "dogen/yarn/test_data/visitor_td.hpp"
#include "dogen/yarn/test_data/exception_td.hpp"
#include "dogen/yarn/test_data/languages_td.hpp"
#include "dogen/yarn/test_data/primitive_td.hpp"
#include "dogen/yarn/test_data/enumeration_td.hpp"
#include "dogen/yarn/test_data/origin_types_td.hpp"
#include "dogen/yarn/test_data/intermediate_model_td.hpp"

namespace {

dogen::yarn::name
create_dogen_yarn_name(const unsigned int position) {
    return dogen::yarn::name_generator::create(position);
}

dogen::yarn::origin_types
create_dogen_yarn_origin_types(const unsigned int position) {
    return dogen::yarn::origin_types_generator::create(position);
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

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::yarn::module
create_dogen_yarn_module(const unsigned int position) {
    return dogen::yarn::module_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::module> create_std_unordered_map_std_string_dogen_yarn_module(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::module> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_module(position + i)));
    }
    return r;
}

dogen::yarn::concept
create_dogen_yarn_concept(const unsigned int position) {
    return dogen::yarn::concept_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::concept> create_std_unordered_map_std_string_dogen_yarn_concept(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::concept> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_concept(position + i)));
    }
    return r;
}

dogen::yarn::primitive
create_dogen_yarn_primitive(const unsigned int position) {
    return dogen::yarn::primitive_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::primitive> create_std_unordered_map_std_string_dogen_yarn_primitive(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::primitive> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_primitive(position + i)));
    }
    return r;
}

dogen::yarn::enumeration
create_dogen_yarn_enumeration(const unsigned int position) {
    return dogen::yarn::enumeration_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::enumeration> create_std_unordered_map_std_string_dogen_yarn_enumeration(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::enumeration> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_enumeration(position + i)));
    }
    return r;
}

dogen::yarn::object
create_dogen_yarn_object(const unsigned int position) {
    return dogen::yarn::object_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::object> create_std_unordered_map_std_string_dogen_yarn_object(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::object> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_object(position + i)));
    }
    return r;
}

dogen::yarn::exception
create_dogen_yarn_exception(const unsigned int position) {
    return dogen::yarn::exception_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::exception> create_std_unordered_map_std_string_dogen_yarn_exception(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::exception> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_exception(position + i)));
    }
    return r;
}

dogen::yarn::visitor
create_dogen_yarn_visitor(const unsigned int position) {
    return dogen::yarn::visitor_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::visitor> create_std_unordered_map_std_string_dogen_yarn_visitor(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::visitor> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_visitor(position + i)));
    }
    return r;
}

dogen::yarn::element*
create_dogen_yarn_element_ptr(const unsigned int position) {
    return dogen::yarn::element_generator::create_ptr(position);
}

boost::shared_ptr<dogen::yarn::element>
create_boost_shared_ptr_dogen_yarn_element(unsigned int position) {
    boost::shared_ptr<dogen::yarn::element> r(
        create_dogen_yarn_element_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> > create_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_element(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_dogen_yarn_element(position + i)));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

dogen::yarn::indices
create_dogen_yarn_indices(const unsigned int position) {
    return dogen::yarn::indices_generator::create(position);
}

dogen::yarn::languages
create_dogen_yarn_languages(const unsigned int position) {
    return dogen::yarn::languages_generator::create(position);
}

std::list<dogen::yarn::languages> create_std_list_dogen_yarn_languages(unsigned int position) {
    std::list<dogen::yarn::languages> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_yarn_languages(position + i));
    }
    return r;
}

}

namespace dogen {
namespace yarn {

intermediate_model_generator::intermediate_model_generator() : position_(0) { }

void intermediate_model_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_dogen_yarn_name(position + 0));
    v.origin_type(create_dogen_yarn_origin_types(position + 1));
    v.references(create_std_unordered_map_dogen_yarn_name_dogen_yarn_origin_types(position + 2));
    v.leaves(create_std_unordered_set_dogen_yarn_name(position + 3));
    v.modules(create_std_unordered_map_std_string_dogen_yarn_module(position + 4));
    v.concepts(create_std_unordered_map_std_string_dogen_yarn_concept(position + 5));
    v.primitives(create_std_unordered_map_std_string_dogen_yarn_primitive(position + 6));
    v.enumerations(create_std_unordered_map_std_string_dogen_yarn_enumeration(position + 7));
    v.objects(create_std_unordered_map_std_string_dogen_yarn_object(position + 8));
    v.exceptions(create_std_unordered_map_std_string_dogen_yarn_exception(position + 9));
    v.visitors(create_std_unordered_map_std_string_dogen_yarn_visitor(position + 10));
    v.injected_elements(create_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_element(position + 11));
    v.has_generatable_types(create_bool(position + 12));
    v.indices(create_dogen_yarn_indices(position + 13));
    v.root_module(create_dogen_yarn_module(position + 14));
    v.input_language(create_dogen_yarn_languages(position + 15));
    v.output_languages(create_std_list_dogen_yarn_languages(position + 16));
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
