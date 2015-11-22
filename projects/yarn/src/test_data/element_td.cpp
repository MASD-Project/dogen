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
#include "dogen/dynamic/test_data/object_td.hpp"
#include "dogen/yarn/test_data/primitive_td.hpp"
#include "dogen/yarn/test_data/enumeration_td.hpp"
#include "dogen/yarn/test_data/origin_types_td.hpp"
#include "dogen/yarn/test_data/generation_types_td.hpp"

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

}

namespace dogen {
namespace yarn {

void element_generator::
populate(const unsigned int position, result_type& v) {
    v.in_global_module(create_bool(position + 0));
    v.documentation(create_std_string(position + 1));
    v.extensions(create_dogen_dynamic_object(position + 2));
    v.name(create_dogen_yarn_name(position + 3));
    v.generation_type(create_dogen_yarn_generation_types(position + 4));
    v.origin_type(create_dogen_yarn_origin_types(position + 5));
    v.original_model_name(create_std_string(position + 6));
    v.containing_module(create_boost_optional_dogen_yarn_name(position + 7));
}

element_generator::result_type*
element_generator::create_ptr(const unsigned int position) {
    if ((position % 4) == 0)
        return dogen::yarn::enumeration_generator::create_ptr(position);
    if ((position % 4) == 1)
        return dogen::yarn::module_generator::create_ptr(position);
    if ((position % 4) == 2)
        return dogen::yarn::object_generator::create_ptr(position);
    if ((position % 4) == 3)
        return dogen::yarn::primitive_generator::create_ptr(position);
    return dogen::yarn::concept_generator::create_ptr(position);
}

} }
