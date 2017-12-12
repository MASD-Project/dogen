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
#include "dogen/test_models/std_model/test_data/class_e_td.hpp"
#include "dogen/test_models/std_model/test_data/pkg1/class_c_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::deque<std::string> create_std_deque_std_string(unsigned int position) {
    std::deque<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

dogen::test_models::std_model::class_a
create_dogen_test_models_std_model_class_a(const unsigned int position) {
    return dogen::test_models::std_model::class_a_generator::create(position);
}

std::deque<dogen::test_models::std_model::class_a> create_std_deque_dogen_test_models_std_model_class_a(unsigned int position) {
    std::deque<dogen::test_models::std_model::class_a> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_test_models_std_model_class_a(position + i));
    }
    return r;
}

dogen::test_models::std_model::pkg1::class_c
create_dogen_test_models_std_model_pkg1_class_c(const unsigned int position) {
    return dogen::test_models::std_model::pkg1::class_c_generator::create(position);
}

std::deque<dogen::test_models::std_model::pkg1::class_c> create_std_deque_dogen_test_models_std_model_pkg1_class_c(unsigned int position) {
    std::deque<dogen::test_models::std_model::pkg1::class_c> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_test_models_std_model_pkg1_class_c(position + i));
    }
    return r;
}

unsigned int create_unsigned_int(const unsigned int position) {
    return static_cast<unsigned int>(position);
}

std::deque<unsigned int> create_std_deque_unsigned_int(unsigned int position) {
    std::deque<unsigned int> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_unsigned_int(position + i));
    }
    return r;
}

std::deque<std::deque<unsigned int> > create_std_deque_std_deque_unsigned_int(unsigned int position) {
    std::deque<std::deque<unsigned int> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_deque_unsigned_int(position + i));
    }
    return r;
}

}

namespace dogen {
namespace test_models {
namespace std_model {

class_e_generator::class_e_generator() : position_(0) { }

void class_e_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_std_deque_std_string(position + 0));
    v.prop_1(create_std_deque_dogen_test_models_std_model_class_a(position + 1));
    v.prop_2(create_std_deque_dogen_test_models_std_model_pkg1_class_c(position + 2));
    v.prop_3(create_std_deque_unsigned_int(position + 3));
    v.prop_4(create_std_deque_dogen_test_models_std_model_class_a(position + 4));
    v.prop_5(create_std_deque_std_deque_unsigned_int(position + 5));
}

class_e_generator::result_type
class_e_generator::create(const unsigned int position) {
    class_e r;
    class_e_generator::populate(position, r);
    return r;
}

class_e_generator::result_type*
class_e_generator::create_ptr(const unsigned int position) {
    class_e* p = new class_e();
    class_e_generator::populate(position, *p);
    return p;
}

class_e_generator::result_type
class_e_generator::operator()() {
    return create(position_++);
}

} } }
