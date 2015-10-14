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
#include "dogen/test_models/std_model/test_data/class_a_td.hpp"
#include "dogen/test_models/std_model/test_data/class_f_td.hpp"
#include "dogen/test_models/std_model/test_data/pkg1/class_c_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::unordered_map<std::string, std::string> create_std_unordered_map_std_string_std_string(unsigned int position) {
    std::unordered_map<std::string, std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_std_string(position + i)));
    }
    return r;
}

dogen::test_models::std_model::class_a
create_dogen_test_models_std_model_class_a(const unsigned int position) {
    return dogen::test_models::std_model::class_a_generator::create(position);
}

std::unordered_map<std::string, dogen::test_models::std_model::class_a> create_std_unordered_map_std_string_dogen_test_models_std_model_class_a(unsigned int position) {
    std::unordered_map<std::string, dogen::test_models::std_model::class_a> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_dogen_test_models_std_model_class_a(position + i)));
    }
    return r;
}

dogen::test_models::std_model::pkg1::class_c
create_dogen_test_models_std_model_pkg1_class_c(const unsigned int position) {
    return dogen::test_models::std_model::pkg1::class_c_generator::create(position);
}

std::unordered_map<dogen::test_models::std_model::class_a, dogen::test_models::std_model::pkg1::class_c> create_std_unordered_map_dogen_test_models_std_model_class_a_dogen_test_models_std_model_pkg1_class_c(unsigned int position) {
    std::unordered_map<dogen::test_models::std_model::class_a, dogen::test_models::std_model::pkg1::class_c> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_test_models_std_model_class_a(position + i), create_dogen_test_models_std_model_pkg1_class_c(position + i)));
    }
    return r;
}

}

namespace dogen {
namespace test_models {
namespace std_model {

class_f_generator::class_f_generator() : position_(0) { }

void class_f_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_std_unordered_map_std_string_std_string(position + 0));
    v.prop_1(create_std_unordered_map_std_string_dogen_test_models_std_model_class_a(position + 1));
    v.prop_2(create_std_unordered_map_dogen_test_models_std_model_class_a_dogen_test_models_std_model_pkg1_class_c(position + 2));
}

class_f_generator::result_type
class_f_generator::create(const unsigned int position) {
    class_f r;
    class_f_generator::populate(position, r);
    return r;
}

class_f_generator::result_type*
class_f_generator::create_ptr(const unsigned int position) {
    class_f* p = new class_f();
    class_f_generator::populate(position, *p);
    return p;
}

class_f_generator::result_type
class_f_generator::operator()() {
    return create(position_++);
}

} } }
