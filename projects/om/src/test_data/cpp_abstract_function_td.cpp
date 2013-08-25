/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/om/test_data/cpp_abstract_function_td.hpp"
#include "dogen/om/test_data/cpp_argument_td.hpp"
#include "dogen/om/test_data/cpp_feature_td.hpp"
#include "dogen/om/test_data/cpp_function_td.hpp"
#include "dogen/om/test_data/cpp_instance_typeref_td.hpp"
#include "dogen/om/test_data/cpp_member_function_td.hpp"
#include "dogen/om/test_data/cpp_representation_types_td.hpp"
#include "dogen/om/test_data/doxygen_command_td.hpp"

namespace {

dogen::om::doxygen_command
create_dogen_om_doxygen_command(const unsigned int position) {
    return dogen::om::doxygen_command_generator::create(position);
}

std::list<dogen::om::doxygen_command> create_std_list_dogen_om_doxygen_command(unsigned int position) {
    std::list<dogen::om::doxygen_command> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_om_doxygen_command(position + i));
    }
    return r;
}

dogen::om::cpp_representation_types
create_dogen_om_cpp_representation_types(const unsigned int position) {
    return dogen::om::cpp_representation_types_generator::create(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

dogen::om::cpp_instance_typeref
create_dogen_om_cpp_instance_typeref(const unsigned int position) {
    return dogen::om::cpp_instance_typeref_generator::create(position);
}

dogen::om::cpp_argument
create_dogen_om_cpp_argument(const unsigned int position) {
    return dogen::om::cpp_argument_generator::create(position);
}

std::list<dogen::om::cpp_argument> create_std_list_dogen_om_cpp_argument(unsigned int position) {
    std::list<dogen::om::cpp_argument> r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_dogen_om_cpp_argument(position + i));
    }
    return r;
}

}

namespace dogen {
namespace om {


void cpp_abstract_function_generator::
populate(const unsigned int position, result_type& v) {
    dogen::om::cpp_feature_generator::populate(position, v);
    v.commands(create_std_list_dogen_om_doxygen_command(position + 0));
    v.representation_type(create_dogen_om_cpp_representation_types(position + 1));
    v.is_inline(create_bool(position + 2));
    v.return_type(create_dogen_om_cpp_instance_typeref(position + 3));
    v.arguments(create_std_list_dogen_om_cpp_argument(position + 4));
    v.is_friend(create_bool(position + 5));
}

cpp_abstract_function_generator::result_type*
cpp_abstract_function_generator::create_ptr(const unsigned int position) {
    if ((position % 1) == 0)
        return dogen::om::cpp_function_generator::create_ptr(position);
    return dogen::om::cpp_member_function_generator::create_ptr(position);
}


} }
