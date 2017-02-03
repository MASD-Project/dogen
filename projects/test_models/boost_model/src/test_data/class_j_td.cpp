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
#include "dogen/test_models/boost_model/test_data/class_j_td.hpp"
#include "dogen/test_models/boost_model/test_data/date_primitive_td.hpp"
#include "dogen/test_models/boost_model/test_data/ptime_primitive_td.hpp"
#include "dogen/test_models/boost_model/test_data/time_duration_primitive_td.hpp"

namespace {

dogen::test_models::boost_model::ptime_primitive
create_dogen_test_models_boost_model_ptime_primitive(const unsigned int position) {
    return dogen::test_models::boost_model::ptime_primitive_generator::create(position);
}

dogen::test_models::boost_model::time_duration_primitive
create_dogen_test_models_boost_model_time_duration_primitive(const unsigned int position) {
    return dogen::test_models::boost_model::time_duration_primitive_generator::create(position);
}

dogen::test_models::boost_model::date_primitive
create_dogen_test_models_boost_model_date_primitive(const unsigned int position) {
    return dogen::test_models::boost_model::date_primitive_generator::create(position);
}

}

namespace dogen {
namespace test_models {
namespace boost_model {

class_j_generator::class_j_generator() : position_(0) { }

void class_j_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_dogen_test_models_boost_model_ptime_primitive(position + 0));
    v.prop_1(create_dogen_test_models_boost_model_time_duration_primitive(position + 1));
    v.prop_2(create_dogen_test_models_boost_model_date_primitive(position + 2));
}

class_j_generator::result_type
class_j_generator::create(const unsigned int position) {
    class_j r;
    class_j_generator::populate(position, r);
    return r;
}

class_j_generator::result_type*
class_j_generator::create_ptr(const unsigned int position) {
    class_j* p = new class_j();
    class_j_generator::populate(position, *p);
    return p;
}

class_j_generator::result_type
class_j_generator::operator()() {
    return create(position_++);
}

} } }
