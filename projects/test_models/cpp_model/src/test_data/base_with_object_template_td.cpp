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
#include "dogen/test_models/cpp_model/test_data/further_inherited_td.hpp"
#include "dogen/test_models/cpp_model/test_data/base_with_object_template_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace test_models {
namespace cpp_model {

void base_with_object_template_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_2(create_int(position + 0));
    v.prop_0(create_std_string(position + 1));
}

base_with_object_template_generator::result_type*
base_with_object_template_generator::create_ptr(const unsigned int position) {
    return dogen::test_models::cpp_model::further_inherited_generator::create_ptr(position);
}

} } }
