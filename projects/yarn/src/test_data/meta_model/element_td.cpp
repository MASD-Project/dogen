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
#include "dogen/annotations/test_data/annotation_td.hpp"
#include "dogen/yarn/test_data/meta_model/module_td.hpp"
#include "dogen/yarn/test_data/meta_model/object_td.hpp"
#include "dogen/yarn/test_data/meta_model/builtin_td.hpp"
#include "dogen/yarn/test_data/meta_model/concept_td.hpp"
#include "dogen/yarn/test_data/meta_model/element_td.hpp"
#include "dogen/yarn/test_data/meta_model/visitor_td.hpp"
#include "dogen/yarn/test_data/meta_model/exception_td.hpp"
#include "dogen/yarn/test_data/meta_model/primitive_td.hpp"
#include "dogen/yarn/test_data/meta_model/enumeration_td.hpp"
#include "dogen/yarn/test_data/meta_model/origin_types_td.hpp"
#include "dogen/yarn/test_data/meta_model/element_properties_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::annotations::annotation
create_dogen_annotations_annotation(const unsigned int position) {
    return dogen::annotations::annotation_generator::create(position);
}

dogen::yarn::meta_model::name
create_dogen_yarn_meta_model_name(const unsigned int position) {
    return dogen::yarn::meta_model::name_generator::create(position);
}

dogen::yarn::meta_model::origin_types
create_dogen_yarn_meta_model_origin_types(const unsigned int position) {
    return dogen::yarn::meta_model::origin_types_generator::create(position);
}

boost::optional<dogen::yarn::meta_model::name>
create_boost_optional_dogen_yarn_meta_model_name(unsigned int position) {
    boost::optional<dogen::yarn::meta_model::name> r(
        create_dogen_yarn_meta_model_name(position));
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

std::vector<std::string> create_std_vector_std_string(unsigned int position) {
    std::vector<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

dogen::yarn::meta_model::element_properties
create_dogen_yarn_meta_model_element_properties(const unsigned int position) {
    return dogen::yarn::meta_model::element_properties_generator::create(position);
}

}

namespace dogen {
namespace yarn {
namespace meta_model {

void element_generator::
populate(const unsigned int position, result_type& v) {
    v.documentation(create_std_string(position + 0));
    v.annotation(create_dogen_annotations_annotation(position + 1));
    v.name(create_dogen_yarn_meta_model_name(position + 2));
    v.origin_type(create_dogen_yarn_meta_model_origin_types(position + 3));
    v.contained_by(create_boost_optional_dogen_yarn_meta_model_name(position + 4));
    v.in_global_module(create_bool(position + 5));
    v.stereotypes(create_std_vector_std_string(position + 6));
    v.meta_name(create_dogen_yarn_meta_model_name(position + 7));
    v.is_element_extension(create_bool(position + 8));
    v.element_properties(create_dogen_yarn_meta_model_element_properties(position + 9));
}

element_generator::result_type*
element_generator::create_ptr(const unsigned int position) {
    if ((position % 7) == 0)
        return dogen::yarn::meta_model::concept_generator::create_ptr(position);
    if ((position % 7) == 1)
        return dogen::yarn::meta_model::enumeration_generator::create_ptr(position);
    if ((position % 7) == 2)
        return dogen::yarn::meta_model::exception_generator::create_ptr(position);
    if ((position % 7) == 3)
        return dogen::yarn::meta_model::module_generator::create_ptr(position);
    if ((position % 7) == 4)
        return dogen::yarn::meta_model::object_generator::create_ptr(position);
    if ((position % 7) == 5)
        return dogen::yarn::meta_model::primitive_generator::create_ptr(position);
    if ((position % 7) == 6)
        return dogen::yarn::meta_model::visitor_generator::create_ptr(position);
    return dogen::yarn::meta_model::builtin_generator::create_ptr(position);
}

} } }
