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
#include <sstream>
#include "dogen/om/test_data/cpp_abstract_instance_td.hpp"
#include "dogen/om/test_data/cpp_argument_td.hpp"
#include "dogen/om/test_data/cpp_feature_td.hpp"
#include "dogen/om/test_data/cpp_member_variable_td.hpp"
#include "dogen/om/test_data/cpp_typeref_td.hpp"
#include "dogen/om/test_data/cpp_variable_td.hpp"
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

dogen::om::cpp_typeref
create_dogen_om_cpp_typeref(const unsigned int position) {
    return dogen::om::cpp_typeref_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace om {


void cpp_abstract_instance_generator::
populate(const unsigned int position, result_type& v) {
    dogen::om::cpp_feature_generator::populate(position, v);
    v.commands(create_std_list_dogen_om_doxygen_command(position + 0));
    v.type(create_dogen_om_cpp_typeref(position + 1));
    v.default_value(create_std_string(position + 2));
}

cpp_abstract_instance_generator::result_type*
cpp_abstract_instance_generator::create_ptr(const unsigned int position) {
    if ((position % 2) == 0)
        return dogen::om::cpp_variable_generator::create_ptr(position);
    if ((position % 2) == 1)
        return dogen::om::cpp_argument_generator::create_ptr(position);
    return dogen::om::cpp_member_variable_generator::create_ptr(position);
}


} }
