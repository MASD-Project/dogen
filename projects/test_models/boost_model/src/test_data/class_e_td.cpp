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
#include "dogen/test_models/boost_model/test_data/class_e_td.hpp"
#include "dogen/test_models/boost_model/test_data/class_derived_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

double create_double(const unsigned int position) {
    return static_cast<double>(position);
}

boost::variant<int, double>
create_boost_variant_int_double(unsigned int position) {
    boost::variant<int, double> r;

    if (position == 0 || ((position % 2) == 0))
        r = create_int(position);
    else if (position == 1 || ((position % 3) == 0))
        r = create_double(position);

    return r;
}

dogen::test_models::boost_model::class_derived
create_dogen_test_models_boost_model_class_derived(const unsigned int position) {
    return dogen::test_models::boost_model::class_derived_generator::create(position);
}

boost::variant<int, dogen::test_models::boost_model::class_derived, double>
create_boost_variant_int_dogen_test_models_boost_model_class_derived_double(unsigned int position) {
    boost::variant<int, dogen::test_models::boost_model::class_derived, double> r;

    if (position == 0 || ((position % 3) == 0))
        r = create_int(position);
    else if (position == 1 || ((position % 4) == 0))
        r = create_dogen_test_models_boost_model_class_derived(position);
    else if ((position % 2) == 0)
        r = create_double(position);

    return r;
}

std::vector<boost::variant<int, dogen::test_models::boost_model::class_derived, double> > create_std_vector_boost_variant_int_dogen_test_models_boost_model_class_derived_double(unsigned int position) {
    std::vector<boost::variant<int, dogen::test_models::boost_model::class_derived, double> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_variant_int_dogen_test_models_boost_model_class_derived_double(position + i));
    }
    return r;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

char create_char(const unsigned int position) {
    return static_cast<char>(((position % 95) + 32) == 34) ? 35 : ((position % 95) + 32);
}

boost::variant<int, std::string, char>
create_boost_variant_int_std_string_char(unsigned int position) {
    boost::variant<int, std::string, char> r;

    if (position == 0 || ((position % 3) == 0))
        r = create_int(position);
    else if (position == 1 || ((position % 4) == 0))
        r = create_std_string(position);
    else if ((position % 2) == 0)
        r = create_char(position);

    return r;
}

}

namespace dogen {
namespace test_models {
namespace boost_model {

class_e_generator::class_e_generator() : position_(0) { }

void class_e_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_boost_variant_int_double(position + 0));
    v.prop_1(create_boost_variant_int_dogen_test_models_boost_model_class_derived_double(position + 1));
    v.prop_2(create_std_vector_boost_variant_int_dogen_test_models_boost_model_class_derived_double(position + 2));
    v.prop_3(create_boost_variant_int_std_string_char(position + 3));
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
