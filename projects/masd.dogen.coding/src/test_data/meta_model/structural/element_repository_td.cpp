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
#include "masd.dogen.coding/test_data/meta_model/structural/module_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/structural/object_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/structural/builtin_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/structural/visitor_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/structural/exception_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/structural/primitive_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/structural/enumeration_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/structural/object_template_td.hpp"
#include "masd.dogen.coding/test_data/meta_model/structural/element_repository_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

masd::dogen::coding::meta_model::structural::module*
create_masd_dogen_coding_meta_model_structural_module_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::structural::module_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::structural::module>
create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_module(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::module> r(
        create_masd_dogen_coding_meta_model_structural_module_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::module> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_module(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::module> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_module(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::structural::object_template*
create_masd_dogen_coding_meta_model_structural_object_template_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::structural::object_template_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::structural::object_template>
create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_object_template(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::object_template> r(
        create_masd_dogen_coding_meta_model_structural_object_template_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object_template> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_object_template(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object_template> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_object_template(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::structural::builtin*
create_masd_dogen_coding_meta_model_structural_builtin_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::structural::builtin_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::structural::builtin>
create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_builtin(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::builtin> r(
        create_masd_dogen_coding_meta_model_structural_builtin_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::builtin> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_builtin(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::builtin> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_builtin(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::structural::enumeration*
create_masd_dogen_coding_meta_model_structural_enumeration_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::structural::enumeration_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::structural::enumeration>
create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_enumeration(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::enumeration> r(
        create_masd_dogen_coding_meta_model_structural_enumeration_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::enumeration> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_enumeration(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::enumeration> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_enumeration(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::structural::primitive*
create_masd_dogen_coding_meta_model_structural_primitive_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::structural::primitive_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::structural::primitive>
create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_primitive(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::primitive> r(
        create_masd_dogen_coding_meta_model_structural_primitive_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::primitive> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_primitive(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::primitive> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_primitive(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::structural::object*
create_masd_dogen_coding_meta_model_structural_object_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::structural::object_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::structural::object>
create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_object(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::object> r(
        create_masd_dogen_coding_meta_model_structural_object_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_object(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::object> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_object(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::structural::exception*
create_masd_dogen_coding_meta_model_structural_exception_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::structural::exception_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::structural::exception>
create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_exception(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::exception> r(
        create_masd_dogen_coding_meta_model_structural_exception_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::exception> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_exception(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::exception> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_exception(position + i)));
    }
    return r;
}

masd::dogen::coding::meta_model::structural::visitor*
create_masd_dogen_coding_meta_model_structural_visitor_ptr(const unsigned int position) {
    return masd::dogen::coding::meta_model::structural::visitor_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::coding::meta_model::structural::visitor>
create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_visitor(unsigned int position) {
    boost::shared_ptr<masd::dogen::coding::meta_model::structural::visitor> r(
        create_masd_dogen_coding_meta_model_structural_visitor_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::visitor> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_visitor(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::structural::visitor> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_coding_meta_model_structural_visitor(position + i)));
    }
    return r;
}

}

namespace masd::dogen::coding::meta_model::structural {

element_repository_generator::element_repository_generator() : position_(0) { }

void element_repository_generator::
populate(const unsigned int position, result_type& v) {
    v.modules(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_module(position + 0));
    v.object_templates(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_object_template(position + 1));
    v.builtins(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_builtin(position + 2));
    v.enumerations(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_enumeration(position + 3));
    v.primitives(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_primitive(position + 4));
    v.objects(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_object(position + 5));
    v.exceptions(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_exception(position + 6));
    v.visitors(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_coding_meta_model_structural_visitor(position + 7));
}

element_repository_generator::result_type
element_repository_generator::create(const unsigned int position) {
    element_repository r;
    element_repository_generator::populate(position, r);
    return r;
}

element_repository_generator::result_type*
element_repository_generator::create_ptr(const unsigned int position) {
    element_repository* p = new element_repository();
    element_repository_generator::populate(position, *p);
    return p;
}

element_repository_generator::result_type
element_repository_generator::operator()() {
    return create(position_++);
}

}
