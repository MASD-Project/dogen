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
#include "dogen/yarn/test_data/meta_model/module_td.hpp"
#include "dogen/yarn/test_data/meta_model/object_td.hpp"
#include "dogen/yarn/test_data/meta_model/builtin_td.hpp"
#include "dogen/yarn/test_data/meta_model/concept_td.hpp"
#include "dogen/yarn/test_data/meta_model/exception_td.hpp"
#include "dogen/yarn/test_data/meta_model/primitive_td.hpp"
#include "dogen/annotations/test_data/scribble_group_td.hpp"
#include "dogen/yarn/test_data/meta_model/enumeration_td.hpp"
#include "dogen/yarn/test_data/meta_model/exogenous_model_td.hpp"

namespace {

dogen::annotations::scribble_group
create_dogen_annotations_scribble_group(const unsigned int position) {
    return dogen::annotations::scribble_group_generator::create(position);
}

dogen::yarn::meta_model::module*
create_dogen_yarn_meta_model_module_ptr(const unsigned int position) {
    return dogen::yarn::meta_model::module_generator::create_ptr(position);
}

boost::shared_ptr<dogen::yarn::meta_model::module>
create_boost_shared_ptr_dogen_yarn_meta_model_module(unsigned int position) {
    boost::shared_ptr<dogen::yarn::meta_model::module> r(
        create_dogen_yarn_meta_model_module_ptr(position));
    return r;
}

std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> >
create_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_module(unsigned int position) {
    std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > r(
        create_dogen_annotations_scribble_group(position),
        create_boost_shared_ptr_dogen_yarn_meta_model_module(position));
    return r;
}

std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > > create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_module(unsigned int position) {
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::module> > > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_module(position + i));
    }
    return r;
}

dogen::yarn::meta_model::concept*
create_dogen_yarn_meta_model_concept_ptr(const unsigned int position) {
    return dogen::yarn::meta_model::concept_generator::create_ptr(position);
}

boost::shared_ptr<dogen::yarn::meta_model::concept>
create_boost_shared_ptr_dogen_yarn_meta_model_concept(unsigned int position) {
    boost::shared_ptr<dogen::yarn::meta_model::concept> r(
        create_dogen_yarn_meta_model_concept_ptr(position));
    return r;
}

std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::concept> >
create_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_concept(unsigned int position) {
    std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::concept> > r(
        create_dogen_annotations_scribble_group(position),
        create_boost_shared_ptr_dogen_yarn_meta_model_concept(position));
    return r;
}

std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::concept> > > create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_concept(unsigned int position) {
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::concept> > > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_concept(position + i));
    }
    return r;
}

dogen::yarn::meta_model::builtin*
create_dogen_yarn_meta_model_builtin_ptr(const unsigned int position) {
    return dogen::yarn::meta_model::builtin_generator::create_ptr(position);
}

boost::shared_ptr<dogen::yarn::meta_model::builtin>
create_boost_shared_ptr_dogen_yarn_meta_model_builtin(unsigned int position) {
    boost::shared_ptr<dogen::yarn::meta_model::builtin> r(
        create_dogen_yarn_meta_model_builtin_ptr(position));
    return r;
}

std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::builtin> >
create_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_builtin(unsigned int position) {
    std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::builtin> > r(
        create_dogen_annotations_scribble_group(position),
        create_boost_shared_ptr_dogen_yarn_meta_model_builtin(position));
    return r;
}

std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::builtin> > > create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_builtin(unsigned int position) {
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::builtin> > > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_builtin(position + i));
    }
    return r;
}

dogen::yarn::meta_model::enumeration*
create_dogen_yarn_meta_model_enumeration_ptr(const unsigned int position) {
    return dogen::yarn::meta_model::enumeration_generator::create_ptr(position);
}

boost::shared_ptr<dogen::yarn::meta_model::enumeration>
create_boost_shared_ptr_dogen_yarn_meta_model_enumeration(unsigned int position) {
    boost::shared_ptr<dogen::yarn::meta_model::enumeration> r(
        create_dogen_yarn_meta_model_enumeration_ptr(position));
    return r;
}

std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::enumeration> >
create_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_enumeration(unsigned int position) {
    std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::enumeration> > r(
        create_dogen_annotations_scribble_group(position),
        create_boost_shared_ptr_dogen_yarn_meta_model_enumeration(position));
    return r;
}

std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::enumeration> > > create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_enumeration(unsigned int position) {
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::enumeration> > > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_enumeration(position + i));
    }
    return r;
}

dogen::yarn::meta_model::primitive*
create_dogen_yarn_meta_model_primitive_ptr(const unsigned int position) {
    return dogen::yarn::meta_model::primitive_generator::create_ptr(position);
}

boost::shared_ptr<dogen::yarn::meta_model::primitive>
create_boost_shared_ptr_dogen_yarn_meta_model_primitive(unsigned int position) {
    boost::shared_ptr<dogen::yarn::meta_model::primitive> r(
        create_dogen_yarn_meta_model_primitive_ptr(position));
    return r;
}

std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::primitive> >
create_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_primitive(unsigned int position) {
    std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::primitive> > r(
        create_dogen_annotations_scribble_group(position),
        create_boost_shared_ptr_dogen_yarn_meta_model_primitive(position));
    return r;
}

std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::primitive> > > create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_primitive(unsigned int position) {
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::primitive> > > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_primitive(position + i));
    }
    return r;
}

dogen::yarn::meta_model::object*
create_dogen_yarn_meta_model_object_ptr(const unsigned int position) {
    return dogen::yarn::meta_model::object_generator::create_ptr(position);
}

boost::shared_ptr<dogen::yarn::meta_model::object>
create_boost_shared_ptr_dogen_yarn_meta_model_object(unsigned int position) {
    boost::shared_ptr<dogen::yarn::meta_model::object> r(
        create_dogen_yarn_meta_model_object_ptr(position));
    return r;
}

std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object> >
create_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_object(unsigned int position) {
    std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object> > r(
        create_dogen_annotations_scribble_group(position),
        create_boost_shared_ptr_dogen_yarn_meta_model_object(position));
    return r;
}

std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object> > > create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_object(unsigned int position) {
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object> > > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_object(position + i));
    }
    return r;
}

dogen::yarn::meta_model::exception*
create_dogen_yarn_meta_model_exception_ptr(const unsigned int position) {
    return dogen::yarn::meta_model::exception_generator::create_ptr(position);
}

boost::shared_ptr<dogen::yarn::meta_model::exception>
create_boost_shared_ptr_dogen_yarn_meta_model_exception(unsigned int position) {
    boost::shared_ptr<dogen::yarn::meta_model::exception> r(
        create_dogen_yarn_meta_model_exception_ptr(position));
    return r;
}

std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::exception> >
create_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_exception(unsigned int position) {
    std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::exception> > r(
        create_dogen_annotations_scribble_group(position),
        create_boost_shared_ptr_dogen_yarn_meta_model_exception(position));
    return r;
}

std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::exception> > > create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_exception(unsigned int position) {
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::exception> > > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_exception(position + i));
    }
    return r;
}

}

namespace dogen {
namespace yarn {
namespace meta_model {

exogenous_model_generator::exogenous_model_generator() : position_(0) { }

void exogenous_model_generator::
populate(const unsigned int position, result_type& v) {
    v.modules(create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_module(position + 0));
    v.concepts(create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_concept(position + 1));
    v.builtins(create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_builtin(position + 2));
    v.enumerations(create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_enumeration(position + 3));
    v.primitives(create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_primitive(position + 4));
    v.objects(create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_object(position + 5));
    v.exceptions(create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_exception(position + 6));
}

exogenous_model_generator::result_type
exogenous_model_generator::create(const unsigned int position) {
    exogenous_model r;
    exogenous_model_generator::populate(position, r);
    return r;
}

exogenous_model_generator::result_type*
exogenous_model_generator::create_ptr(const unsigned int position) {
    exogenous_model* p = new exogenous_model();
    exogenous_model_generator::populate(position, *p);
    return p;
}

exogenous_model_generator::result_type
exogenous_model_generator::operator()() {
    return create(position_++);
}

} } }
