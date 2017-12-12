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
#include "dogen/test_models/cpp_model/test_data/value_td.hpp"
#include "dogen/test_models/cpp_model/test_data/fluent_td.hpp"

namespace {

unsigned int create_unsigned_int(const unsigned int position) {
    return static_cast<unsigned int>(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::test_models::cpp_model::value
create_dogen_test_models_cpp_model_value(const unsigned int position) {
    return dogen::test_models::cpp_model::value_generator::create(position);
}

}

namespace dogen {
namespace test_models {
namespace cpp_model {

fluent_generator::fluent_generator() : position_(0) { }

void fluent_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_unsigned_int(position + 0));
    v.prop_1(create_std_string(position + 1));
    v.prop_2(create_dogen_test_models_cpp_model_value(position + 2));
}

fluent_generator::result_type
fluent_generator::create(const unsigned int position) {
    fluent r;
    fluent_generator::populate(position, r);
    return r;
}

fluent_generator::result_type*
fluent_generator::create_ptr(const unsigned int position) {
    fluent* p = new fluent();
    fluent_generator::populate(position, *p);
    return p;
}

fluent_generator::result_type
fluent_generator::operator()() {
    return create(position_++);
}

} } }
