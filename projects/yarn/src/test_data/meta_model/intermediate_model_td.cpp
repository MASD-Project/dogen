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
#include "dogen/yarn/test_data/meta_model/name_td.hpp"
#include "dogen/yarn/test_data/meta_model/module_td.hpp"
#include "dogen/yarn/test_data/meta_model/object_td.hpp"
#include "dogen/yarn/test_data/meta_model/builtin_td.hpp"
#include "dogen/yarn/test_data/meta_model/concept_td.hpp"
#include "dogen/yarn/test_data/meta_model/element_td.hpp"
#include "dogen/yarn/test_data/meta_model/visitor_td.hpp"
#include "dogen/yarn/test_data/meta_model/exception_td.hpp"
#include "dogen/yarn/test_data/meta_model/languages_td.hpp"
#include "dogen/yarn/test_data/meta_model/primitive_td.hpp"
#include "dogen/annotations/test_data/scribble_group_td.hpp"
#include "dogen/yarn/test_data/meta_model/enumeration_td.hpp"
#include "dogen/yarn/test_data/meta_model/origin_types_td.hpp"
#include "dogen/yarn/test_data/meta_model/facet_properties_td.hpp"
#include "dogen/yarn/test_data/meta_model/intermediate_model_td.hpp"
#include "dogen/yarn/test_data/meta_model/orm_model_properties_td.hpp"

namespace {

dogen::yarn::meta_model::name
create_dogen_yarn_meta_model_name(const unsigned int position) {
    return dogen::yarn::meta_model::name_generator::create(position);
}

dogen::yarn::meta_model::origin_types
create_dogen_yarn_meta_model_origin_types(const unsigned int position) {
    return dogen::yarn::meta_model::origin_types_generator::create(position);
}

std::unordered_map<dogen::yarn::meta_model::name, dogen::yarn::meta_model::origin_types> create_std_unordered_map_dogen_yarn_meta_model_name_dogen_yarn_meta_model_origin_types(unsigned int position) {
    std::unordered_map<dogen::yarn::meta_model::name, dogen::yarn::meta_model::origin_types> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_yarn_meta_model_name(position + i), create_dogen_yarn_meta_model_origin_types(position + i)));
    }
    return r;
}

std::unordered_set<dogen::yarn::meta_model::name> create_std_unordered_set_dogen_yarn_meta_model_name(unsigned int position) {
    std::unordered_set<dogen::yarn::meta_model::name> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_dogen_yarn_meta_model_name(position + i));
    }
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::yarn::meta_model::module
create_dogen_yarn_meta_model_module(const unsigned int position) {
    return dogen::yarn::meta_model::module_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::meta_model::module> create_std_unordered_map_std_string_dogen_yarn_meta_model_module(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::meta_model::module> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_meta_model_module(position + i)));
    }
    return r;
}

dogen::yarn::meta_model::concept
create_dogen_yarn_meta_model_concept(const unsigned int position) {
    return dogen::yarn::meta_model::concept_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::meta_model::concept> create_std_unordered_map_std_string_dogen_yarn_meta_model_concept(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::meta_model::concept> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_meta_model_concept(position + i)));
    }
    return r;
}

dogen::yarn::meta_model::builtin
create_dogen_yarn_meta_model_builtin(const unsigned int position) {
    return dogen::yarn::meta_model::builtin_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::meta_model::builtin> create_std_unordered_map_std_string_dogen_yarn_meta_model_builtin(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::meta_model::builtin> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_meta_model_builtin(position + i)));
    }
    return r;
}

dogen::yarn::meta_model::enumeration
create_dogen_yarn_meta_model_enumeration(const unsigned int position) {
    return dogen::yarn::meta_model::enumeration_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::meta_model::enumeration> create_std_unordered_map_std_string_dogen_yarn_meta_model_enumeration(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::meta_model::enumeration> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_meta_model_enumeration(position + i)));
    }
    return r;
}

dogen::yarn::meta_model::primitive
create_dogen_yarn_meta_model_primitive(const unsigned int position) {
    return dogen::yarn::meta_model::primitive_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::meta_model::primitive> create_std_unordered_map_std_string_dogen_yarn_meta_model_primitive(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::meta_model::primitive> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_meta_model_primitive(position + i)));
    }
    return r;
}

dogen::yarn::meta_model::object
create_dogen_yarn_meta_model_object(const unsigned int position) {
    return dogen::yarn::meta_model::object_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::meta_model::object> create_std_unordered_map_std_string_dogen_yarn_meta_model_object(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::meta_model::object> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_meta_model_object(position + i)));
    }
    return r;
}

dogen::yarn::meta_model::exception
create_dogen_yarn_meta_model_exception(const unsigned int position) {
    return dogen::yarn::meta_model::exception_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::meta_model::exception> create_std_unordered_map_std_string_dogen_yarn_meta_model_exception(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::meta_model::exception> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_meta_model_exception(position + i)));
    }
    return r;
}

dogen::yarn::meta_model::visitor
create_dogen_yarn_meta_model_visitor(const unsigned int position) {
    return dogen::yarn::meta_model::visitor_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::meta_model::visitor> create_std_unordered_map_std_string_dogen_yarn_meta_model_visitor(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::meta_model::visitor> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_meta_model_visitor(position + i)));
    }
    return r;
}

dogen::yarn::meta_model::element*
create_dogen_yarn_meta_model_element_ptr(const unsigned int position) {
    return dogen::yarn::meta_model::element_generator::create_ptr(position);
}

boost::shared_ptr<dogen::yarn::meta_model::element>
create_boost_shared_ptr_dogen_yarn_meta_model_element(unsigned int position) {
    boost::shared_ptr<dogen::yarn::meta_model::element> r(
        create_dogen_yarn_meta_model_element_ptr(position));
    return r;
}

std::list<boost::shared_ptr<dogen::yarn::meta_model::element> > create_std_list_boost_shared_ptr_dogen_yarn_meta_model_element(unsigned int position) {
    std::list<boost::shared_ptr<dogen::yarn::meta_model::element> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_shared_ptr_dogen_yarn_meta_model_element(position + i));
    }
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

dogen::yarn::meta_model::languages
create_dogen_yarn_meta_model_languages(const unsigned int position) {
    return dogen::yarn::meta_model::languages_generator::create(position);
}

std::list<dogen::yarn::meta_model::languages> create_std_list_dogen_yarn_meta_model_languages(unsigned int position) {
    std::list<dogen::yarn::meta_model::languages> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_yarn_meta_model_languages(position + i));
    }
    return r;
}

dogen::annotations::scribble_group
create_dogen_annotations_scribble_group(const unsigned int position) {
    return dogen::annotations::scribble_group_generator::create(position);
}

std::unordered_map<std::string, dogen::annotations::scribble_group> create_std_unordered_map_std_string_dogen_annotations_scribble_group(unsigned int position) {
    std::unordered_map<std::string, dogen::annotations::scribble_group> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_annotations_scribble_group(position + i)));
    }
    return r;
}

dogen::yarn::meta_model::orm_model_properties
create_dogen_yarn_meta_model_orm_model_properties(const unsigned int position) {
    return dogen::yarn::meta_model::orm_model_properties_generator::create(position);
}

boost::optional<dogen::yarn::meta_model::orm_model_properties>
create_boost_optional_dogen_yarn_meta_model_orm_model_properties(unsigned int position) {
    boost::optional<dogen::yarn::meta_model::orm_model_properties> r(
        create_dogen_yarn_meta_model_orm_model_properties(position));
    return r;
}

dogen::yarn::meta_model::facet_properties
create_dogen_yarn_meta_model_facet_properties(const unsigned int position) {
    return dogen::yarn::meta_model::facet_properties_generator::create(position);
}

std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties> create_std_unordered_map_std_string_dogen_yarn_meta_model_facet_properties(unsigned int position) {
    std::unordered_map<std::string, dogen::yarn::meta_model::facet_properties> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_yarn_meta_model_facet_properties(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace yarn {
namespace meta_model {

intermediate_model_generator::intermediate_model_generator() : position_(0) { }

void intermediate_model_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_dogen_yarn_meta_model_name(position + 0));
    v.origin_type(create_dogen_yarn_meta_model_origin_types(position + 1));
    v.references(create_std_unordered_map_dogen_yarn_meta_model_name_dogen_yarn_meta_model_origin_types(position + 2));
    v.leaves(create_std_unordered_set_dogen_yarn_meta_model_name(position + 3));
    v.modules(create_std_unordered_map_std_string_dogen_yarn_meta_model_module(position + 4));
    v.concepts(create_std_unordered_map_std_string_dogen_yarn_meta_model_concept(position + 5));
    v.builtins(create_std_unordered_map_std_string_dogen_yarn_meta_model_builtin(position + 6));
    v.enumerations(create_std_unordered_map_std_string_dogen_yarn_meta_model_enumeration(position + 7));
    v.primitives(create_std_unordered_map_std_string_dogen_yarn_meta_model_primitive(position + 8));
    v.objects(create_std_unordered_map_std_string_dogen_yarn_meta_model_object(position + 9));
    v.exceptions(create_std_unordered_map_std_string_dogen_yarn_meta_model_exception(position + 10));
    v.visitors(create_std_unordered_map_std_string_dogen_yarn_meta_model_visitor(position + 11));
    v.injected_elements(create_std_list_boost_shared_ptr_dogen_yarn_meta_model_element(position + 12));
    v.has_generatable_types(create_bool(position + 13));
    v.root_module(create_dogen_yarn_meta_model_module(position + 14));
    v.input_language(create_dogen_yarn_meta_model_languages(position + 15));
    v.output_languages(create_std_list_dogen_yarn_meta_model_languages(position + 16));
    v.scribble_groups(create_std_unordered_map_std_string_dogen_annotations_scribble_group(position + 17));
    v.orm_properties(create_boost_optional_dogen_yarn_meta_model_orm_model_properties(position + 18));
    v.facet_properties(create_std_unordered_map_std_string_dogen_yarn_meta_model_facet_properties(position + 19));
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

} } }
