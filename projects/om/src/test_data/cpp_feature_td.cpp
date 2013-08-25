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
#include "dogen/om/test_data/cpp_argument_td.hpp"
#include "dogen/om/test_data/cpp_class_td.hpp"
#include "dogen/om/test_data/cpp_enumeration_td.hpp"
#include "dogen/om/test_data/cpp_feature_td.hpp"
#include "dogen/om/test_data/cpp_function_td.hpp"
#include "dogen/om/test_data/cpp_header_guard_td.hpp"
#include "dogen/om/test_data/cpp_ifdef_td.hpp"
#include "dogen/om/test_data/cpp_include_directive_td.hpp"
#include "dogen/om/test_data/cpp_member_function_td.hpp"
#include "dogen/om/test_data/cpp_member_variable_td.hpp"
#include "dogen/om/test_data/cpp_namespace_td.hpp"
#include "dogen/om/test_data/cpp_pragma_td.hpp"
#include "dogen/om/test_data/cpp_typedef_td.hpp"
#include "dogen/om/test_data/cpp_variable_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace om {


void cpp_feature_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_std_string(position + 0));
}

cpp_feature_generator::result_type*
cpp_feature_generator::create_ptr(const unsigned int position) {
    if ((position % 12) == 0)
        return dogen::om::cpp_class_generator::create_ptr(position);
    if ((position % 12) == 1)
        return dogen::om::cpp_member_function_generator::create_ptr(position);
    if ((position % 12) == 2)
        return dogen::om::cpp_function_generator::create_ptr(position);
    if ((position % 12) == 3)
        return dogen::om::cpp_enumeration_generator::create_ptr(position);
    if ((position % 12) == 4)
        return dogen::om::cpp_member_variable_generator::create_ptr(position);
    if ((position % 12) == 5)
        return dogen::om::cpp_variable_generator::create_ptr(position);
    if ((position % 12) == 6)
        return dogen::om::cpp_argument_generator::create_ptr(position);
    if ((position % 12) == 7)
        return dogen::om::cpp_header_guard_generator::create_ptr(position);
    if ((position % 12) == 8)
        return dogen::om::cpp_include_directive_generator::create_ptr(position);
    if ((position % 12) == 9)
        return dogen::om::cpp_ifdef_generator::create_ptr(position);
    if ((position % 12) == 10)
        return dogen::om::cpp_typedef_generator::create_ptr(position);
    if ((position % 12) == 11)
        return dogen::om::cpp_pragma_generator::create_ptr(position);
    return dogen::om::cpp_namespace_generator::create_ptr(position);
}


} }
