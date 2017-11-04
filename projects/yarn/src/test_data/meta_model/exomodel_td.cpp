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
#include "dogen/yarn/test_data/meta_model/exomodel_td.hpp"
#include "dogen/yarn/test_data/meta_model/exception_td.hpp"
#include "dogen/yarn/test_data/meta_model/primitive_td.hpp"
#include "dogen/annotations/test_data/scribble_group_td.hpp"
#include "dogen/yarn/test_data/meta_model/exoelement_td.hpp"
#include "dogen/yarn/test_data/meta_model/enumeration_td.hpp"
#include "dogen/yarn/test_data/meta_model/object_template_td.hpp"

namespace {

dogen::yarn::meta_model::name
create_dogen_yarn_meta_model_name(const unsigned int position) {
    return dogen::yarn::meta_model::name_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::vector<std::string> create_std_vector_std_string(unsigned int position) {
    std::vector<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

std::pair<std::string, std::string>
create_std_pair_std_string_std_string(unsigned int position) {
    std::pair<std::string, std::string> r(
        create_std_string(position),
        create_std_string(position));
    return r;
}

std::list<std::pair<std::string, std::string> > create_std_list_std_pair_std_string_std_string(unsigned int position) {
    std::list<std::pair<std::string, std::string> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_pair_std_string_std_string(position + i));
    }
    return r;
}

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

dogen::yarn::meta_model::object_template*
create_dogen_yarn_meta_model_object_template_ptr(const unsigned int position) {
    return dogen::yarn::meta_model::object_template_generator::create_ptr(position);
}

boost::shared_ptr<dogen::yarn::meta_model::object_template>
create_boost_shared_ptr_dogen_yarn_meta_model_object_template(unsigned int position) {
    boost::shared_ptr<dogen::yarn::meta_model::object_template> r(
        create_dogen_yarn_meta_model_object_template_ptr(position));
    return r;
}

std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object_template> >
create_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_object_template(unsigned int position) {
    std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object_template> > r(
        create_dogen_annotations_scribble_group(position),
        create_boost_shared_ptr_dogen_yarn_meta_model_object_template(position));
    return r;
}

std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object_template> > > create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_object_template(unsigned int position) {
    std::list<std::pair<dogen::annotations::scribble_group, boost::shared_ptr<dogen::yarn::meta_model::object_template> > > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_object_template(position + i));
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

dogen::yarn::meta_model::exoelement
create_dogen_yarn_meta_model_exoelement(const unsigned int position) {
    return dogen::yarn::meta_model::exoelement_generator::create(position);
}

std::list<dogen::yarn::meta_model::exoelement> create_std_list_dogen_yarn_meta_model_exoelement(unsigned int position) {
    std::list<dogen::yarn::meta_model::exoelement> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_yarn_meta_model_exoelement(position + i));
    }
    return r;
}

}

namespace dogen {
namespace yarn {
namespace meta_model {

exomodel_generator::exomodel_generator() : position_(0) { }

void exomodel_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_dogen_yarn_meta_model_name(position + 0));
    v.meta_name(create_dogen_yarn_meta_model_name(position + 1));
    v.documentation(create_std_string(position + 2));
    v.stereotypes(create_std_vector_std_string(position + 3));
    v.tagged_values(create_std_list_std_pair_std_string_std_string(position + 4));
    v.modules(create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_module(position + 5));
    v.object_templates(create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_object_template(position + 6));
    v.builtins(create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_builtin(position + 7));
    v.enumerations(create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_enumeration(position + 8));
    v.primitives(create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_primitive(position + 9));
    v.objects(create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_object(position + 10));
    v.exceptions(create_std_list_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_exception(position + 11));
    v.root_module(create_std_pair_dogen_annotations_scribble_group_boost_shared_ptr_dogen_yarn_meta_model_module(position + 12));
    v.new_name(create_std_string(position + 13));
    v.elements(create_std_list_dogen_yarn_meta_model_exoelement(position + 14));
}

exomodel_generator::result_type
exomodel_generator::create(const unsigned int position) {
    exomodel r;
    exomodel_generator::populate(position, r);
    return r;
}

exomodel_generator::result_type*
exomodel_generator::create_ptr(const unsigned int position) {
    exomodel* p = new exomodel();
    exomodel_generator::populate(position, *p);
    return p;
}

exomodel_generator::result_type
exomodel_generator::operator()() {
    return create(position_++);
}

} } }
