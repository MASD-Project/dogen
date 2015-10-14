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
#include "dogen/tack/test_data/name_td.hpp"
#include "dogen/tack/test_data/type_td.hpp"
#include "dogen/tack/test_data/object_td.hpp"
#include "dogen/dynamic/test_data/object_td.hpp"
#include "dogen/tack/test_data/primitive_td.hpp"
#include "dogen/tack/test_data/enumeration_td.hpp"
#include "dogen/tack/test_data/origin_types_td.hpp"
#include "dogen/tack/test_data/generation_types_td.hpp"

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

dogen::tack::name
create_dogen_tack_name(const unsigned int position) {
    return dogen::tack::name_generator::create(position);
}

dogen::tack::generation_types
create_dogen_tack_generation_types(const unsigned int position) {
    return dogen::tack::generation_types_generator::create(position);
}

dogen::tack::origin_types
create_dogen_tack_origin_types(const unsigned int position) {
    return dogen::tack::origin_types_generator::create(position);
}

boost::optional<dogen::tack::name>
create_boost_optional_dogen_tack_name(unsigned int position) {
    boost::optional<dogen::tack::name> r(
        create_dogen_tack_name(position));
    return r;
}

}

namespace dogen {
namespace tack {

void type_generator::
populate(const unsigned int position, result_type& v) {
    v.documentation(create_std_string(position + 0));
    v.extensions(create_dogen_dynamic_object(position + 1));
    v.name(create_dogen_tack_name(position + 2));
    v.generation_type(create_dogen_tack_generation_types(position + 3));
    v.origin_type(create_dogen_tack_origin_types(position + 4));
    v.containing_module(create_boost_optional_dogen_tack_name(position + 5));
}

type_generator::result_type*
type_generator::create_ptr(const unsigned int position) {
    if ((position % 2) == 0)
        return dogen::tack::object_generator::create_ptr(position);
    if ((position % 2) == 1)
        return dogen::tack::primitive_generator::create_ptr(position);
    return dogen::tack::enumeration_generator::create_ptr(position);
}

} }
