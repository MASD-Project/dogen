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
#include "masd.dogen.coding/test_data/meta_model/name_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/model_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/module_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/object_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/builtin_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/licence_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/visitor_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/modeline_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/exception_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/languages_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/primitive_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/enumeration_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/origin_types_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/modeline_group_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/object_template_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/generation_marker_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/orm_model_properties_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/extraction_properties_td.hpp"

namespace {

masd::dogen::coding::meta_model::name
create_masd_dogen_coding_meta_model_name(const unsigned int position) {
    return masd::dogen::coding::meta_model::name_generator::create(position);
}

masd::dogen::coding::meta_model::origin_types
create_masd_dogen_coding_meta_model_origin_types(const unsigned int position) {
    return masd::dogen::coding::meta_model::origin_types_generator::create(position);
}

std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types> create_std_unordered_map_masd_dogen_coding_meta_model_name_masd_dogen_coding_meta_model_origin_types(unsigned int position) {
    std::unordered_map<masd::dogen::coding::meta_model::name, masd::dogen::coding::meta_model::origin_types> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_masd_dogen_coding_meta_model_name(position + i), create_masd_dogen_coding_meta_model_origin_types(position + i)));
    }
    return r;
}

std::unordered_set<masd::dogen::coding::meta_model::name> create_std_unordered_set_masd_dogen_coding_meta_model_name(unsigned int position) {
    std::unordered_set<masd::dogen::coding::meta_model::name> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_masd_dogen_coding_meta_model_name(position + i));
    }
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

masd::dogen::coding::meta_model::module*
create_masd_dogen_coding_meta_model_module_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::module_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::module>
create_boost_shared_ptr_masd_dogen_coding_meta_model_module(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::module> r(
        create_masd_dogen_coding_meta_model_module_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::module> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_module(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::module> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_module(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::object_template*
create_masd_dogen_coding_meta_model_object_template_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::object_template_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::object_template>
create_boost_shared_ptr_masd_dogen_coding_meta_model_object_template(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::object_template> r(
        create_masd_dogen_coding_meta_model_object_template_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object_template> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_object_template(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object_template> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_object_template(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::builtin*
create_masd_dogen_coding_meta_model_builtin_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::builtin_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::builtin>
create_boost_shared_ptr_masd_dogen_coding_meta_model_builtin(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::builtin> r(
        create_masd_dogen_coding_meta_model_builtin_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::builtin> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_builtin(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::builtin> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_builtin(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::enumeration*
create_masd_dogen_coding_meta_model_enumeration_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::enumeration_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::enumeration>
create_boost_shared_ptr_masd_dogen_coding_meta_model_enumeration(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::enumeration> r(
        create_masd_dogen_coding_meta_model_enumeration_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::enumeration> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_enumeration(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::enumeration> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_enumeration(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::primitive*
create_masd_dogen_coding_meta_model_primitive_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::primitive_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::primitive>
create_boost_shared_ptr_masd_dogen_coding_meta_model_primitive(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::primitive> r(
        create_masd_dogen_coding_meta_model_primitive_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::primitive> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_primitive(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::primitive> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_primitive(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::object*
create_masd_dogen_coding_meta_model_object_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::object_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::object>
create_boost_shared_ptr_masd_dogen_coding_meta_model_object(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::object> r(
        create_masd_dogen_coding_meta_model_object_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_object(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::object> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_object(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::exception*
create_masd_dogen_coding_meta_model_exception_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::exception_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::exception>
create_boost_shared_ptr_masd_dogen_coding_meta_model_exception(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::exception> r(
        create_masd_dogen_coding_meta_model_exception_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::exception> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_exception(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::exception> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_exception(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::visitor*
create_masd_dogen_coding_meta_model_visitor_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::visitor_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::visitor>
create_boost_shared_ptr_masd_dogen_coding_meta_model_visitor(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::visitor> r(
        create_masd_dogen_coding_meta_model_visitor_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::visitor> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_visitor(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::visitor> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_visitor(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::modeline_group
create_masd_dogen_coding_meta_model_modeline_group(const unsigned int position) {
    return masd::dogen::coding::meta_model::modeline_group_generator::create(position);
}

std::unordered_map<std::string, masd::dogen::coding::meta_model::modeline_group> create_std_unordered_map_std_string_masd_dogen_coding_meta_model_modeline_group(unsigned int position) {
    std::unordered_map<std::string, masd::dogen::coding::meta_model::modeline_group> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_masd_dogen_coding_meta_model_modeline_group(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::modeline
create_masd_dogen_coding_meta_model_modeline(const unsigned int position) {
    return masd::dogen::coding::meta_model::modeline_generator::create(position);
}

std::unordered_map<std::string, masd::dogen::coding::meta_model::modeline> create_std_unordered_map_std_string_masd_dogen_coding_meta_model_modeline(unsigned int position) {
    std::unordered_map<std::string, masd::dogen::coding::meta_model::modeline> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_masd_dogen_coding_meta_model_modeline(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::licence
create_masd_dogen_coding_meta_model_licence(const unsigned int position) {
    return masd::dogen::coding::meta_model::licence_generator::create(position);
}

std::unordered_map<std::string, masd::dogen::coding::meta_model::licence> create_std_unordered_map_std_string_masd_dogen_coding_meta_model_licence(unsigned int position) {
    std::unordered_map<std::string, masd::dogen::coding::meta_model::licence> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_masd_dogen_coding_meta_model_licence(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::generation_marker
create_masd_dogen_coding_meta_model_generation_marker(const unsigned int position) {
    return masd::dogen::coding::meta_model::generation_marker_generator::create(position);
}

std::unordered_map<std::string, masd::dogen::coding::meta_model::generation_marker> create_std_unordered_map_std_string_masd_dogen_coding_meta_model_generation_marker(unsigned int position) {
    std::unordered_map<std::string, masd::dogen::coding::meta_model::generation_marker> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_masd_dogen_coding_meta_model_generation_marker(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::languages
create_masd_dogen_coding_meta_model_languages(const unsigned int position) {
    return masd::dogen::coding::meta_model::languages_generator::create(position);
}

std::list<masd::dogen::coding::meta_model::languages> create_std_list_masd_dogen_coding_meta_model_languages(unsigned int position) {
    std::list<masd::dogen::coding::meta_model::languages> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_masd_dogen_coding_meta_model_languages(position + i));
    }
    return r;
}

masd::dogen::coding::meta_model::orm_model_properties
create_masd_dogen_coding_meta_model_orm_model_properties(const unsigned int position) {
    return masd::dogen::coding::meta_model::orm_model_properties_generator::create(position);
}

boost::optional<masd::dogen::coding::meta_model::orm_model_properties>
create_boost_optional_masd_dogen_coding_meta_model_orm_model_properties(unsigned int position) {
    boost::optional<masd::dogen::coding::meta_model::orm_model_properties> r(
        create_masd_dogen_coding_meta_model_orm_model_properties(position));
    return r;
}

masd::dogen::coding::meta_model::extraction_properties
create_masd_dogen_coding_meta_model_extraction_properties(const unsigned int position) {
    return masd::dogen::coding::meta_model::extraction_properties_generator::create(position);
}

}

namespace masd::dogen::coding::meta_model {

model_generator::model_generator() : position_(0) { }

void model_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_masd_dogen_coding_meta_model_name(position + 0));
    v.meta_name(create_masd_dogen_coding_meta_model_name(position + 1));
    v.origin_type(create_masd_dogen_coding_meta_model_origin_types(position + 2));
    v.references(create_std_unordered_map_masd_dogen_coding_meta_model_name_masd_dogen_coding_meta_model_origin_types(position + 3));
    v.leaves(create_std_unordered_set_masd_dogen_coding_meta_model_name(position + 4));
    v.modules(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_module(position + 5));
    v.object_templates(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_object_template(position + 6));
    v.builtins(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_builtin(position + 7));
    v.enumerations(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_enumeration(position + 8));
    v.primitives(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_primitive(position + 9));
    v.objects(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_object(position + 10));
    v.exceptions(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_exception(position + 11));
    v.visitors(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_visitor(position + 12));
    v.modeline_groups(create_std_unordered_map_std_string_masd_dogen_coding_meta_model_modeline_group(position + 13));
    v.modelines(create_std_unordered_map_std_string_masd_dogen_coding_meta_model_modeline(position + 14));
    v.licences(create_std_unordered_map_std_string_masd_dogen_coding_meta_model_licence(position + 15));
    v.generation_markers(create_std_unordered_map_std_string_masd_dogen_coding_meta_model_generation_marker(position + 16));
    v.root_module(create_boost_shared_ptr_masd_dogen_coding_meta_model_module(position + 17));
    v.input_language(create_masd_dogen_coding_meta_model_languages(position + 18));
    v.output_languages(create_std_list_masd_dogen_coding_meta_model_languages(position + 19));
    v.orm_properties(create_boost_optional_masd_dogen_coding_meta_model_orm_model_properties(position + 20));
    v.extraction_properties(create_masd_dogen_coding_meta_model_extraction_properties(position + 21));
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

}
