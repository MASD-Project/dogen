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
#include "dogen/test_models/boost_model/test_data/class_a_td.hpp"
#include "dogen/test_models/boost_model/test_data/class_b_td.hpp"
#include "dogen/test_models/boost_model/test_data/class_base_td.hpp"
#include "dogen/test_models/boost_model/test_data/pkg1/class_c_td.hpp"

namespace {

dogen::test_models::boost_model::class_a*
create_dogen_test_models_boost_model_class_a_ptr(const unsigned int position) {
    return dogen::test_models::boost_model::class_a_generator::create_ptr(position);
}

boost::shared_ptr<dogen::test_models::boost_model::class_a>
create_boost_shared_ptr_dogen_test_models_boost_model_class_a(unsigned int position) {
    boost::shared_ptr<dogen::test_models::boost_model::class_a> r(
        create_dogen_test_models_boost_model_class_a_ptr(position));
    return r;
}

std::vector<boost::shared_ptr<dogen::test_models::boost_model::class_a> > create_std_vector_boost_shared_ptr_dogen_test_models_boost_model_class_a(unsigned int position) {
    std::vector<boost::shared_ptr<dogen::test_models::boost_model::class_a> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_shared_ptr_dogen_test_models_boost_model_class_a(position + i));
    }
    return r;
}

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

std::unordered_map<int, boost::shared_ptr<dogen::test_models::boost_model::class_a> > create_std_unordered_map_int_boost_shared_ptr_dogen_test_models_boost_model_class_a(unsigned int position) {
    std::unordered_map<int, boost::shared_ptr<dogen::test_models::boost_model::class_a> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_int(position + i), create_boost_shared_ptr_dogen_test_models_boost_model_class_a(position + i)));
    }
    return r;
}

dogen::test_models::boost_model::pkg1::class_c*
create_dogen_test_models_boost_model_pkg1_class_c_ptr(const unsigned int position) {
    return dogen::test_models::boost_model::pkg1::class_c_generator::create_ptr(position);
}

boost::shared_ptr<dogen::test_models::boost_model::pkg1::class_c>
create_boost_shared_ptr_dogen_test_models_boost_model_pkg1_class_c(unsigned int position) {
    boost::shared_ptr<dogen::test_models::boost_model::pkg1::class_c> r(
        create_dogen_test_models_boost_model_pkg1_class_c_ptr(position));
    return r;
}

dogen::test_models::boost_model::class_base*
create_dogen_test_models_boost_model_class_base_ptr(const unsigned int position) {
    return dogen::test_models::boost_model::class_base_generator::create_ptr(position);
}

boost::shared_ptr<dogen::test_models::boost_model::class_base>
create_boost_shared_ptr_dogen_test_models_boost_model_class_base(unsigned int position) {
    boost::shared_ptr<dogen::test_models::boost_model::class_base> r(
        create_dogen_test_models_boost_model_class_base_ptr(position));
    return r;
}

std::vector<boost::shared_ptr<dogen::test_models::boost_model::class_base> > create_std_vector_boost_shared_ptr_dogen_test_models_boost_model_class_base(unsigned int position) {
    std::vector<boost::shared_ptr<dogen::test_models::boost_model::class_base> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_boost_shared_ptr_dogen_test_models_boost_model_class_base(position + i));
    }
    return r;
}

dogen::test_models::boost_model::pkg1::class_c
create_dogen_test_models_boost_model_pkg1_class_c(const unsigned int position) {
    return dogen::test_models::boost_model::pkg1::class_c_generator::create(position);
}

}

namespace dogen {
namespace test_models {
namespace boost_model {

class_b_generator::class_b_generator() : position_(0) { }

void class_b_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_boost_shared_ptr_dogen_test_models_boost_model_class_a(position + 0));
    v.prop_1(create_std_vector_boost_shared_ptr_dogen_test_models_boost_model_class_a(position + 1));
    v.prop_2(create_std_unordered_map_int_boost_shared_ptr_dogen_test_models_boost_model_class_a(position + 2));
    v.prop_3(create_boost_shared_ptr_dogen_test_models_boost_model_pkg1_class_c(position + 3));
    v.prop_4(create_boost_shared_ptr_dogen_test_models_boost_model_class_base(position + 4));
    v.prop_5(create_std_vector_boost_shared_ptr_dogen_test_models_boost_model_class_base(position + 5));
    v.prop_6(create_dogen_test_models_boost_model_pkg1_class_c(position + 6));
}

class_b_generator::result_type
class_b_generator::create(const unsigned int position) {
    class_b r;
    class_b_generator::populate(position, r);
    return r;
}

class_b_generator::result_type*
class_b_generator::create_ptr(const unsigned int position) {
    class_b* p = new class_b();
    class_b_generator::populate(position, *p);
    return p;
}

class_b_generator::result_type
class_b_generator::operator()() {
    return create(position_++);
}

} } }
