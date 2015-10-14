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
#include "dogen/test_models/std_model/test_data/base_td.hpp"
#include "dogen/test_models/std_model/test_data/derived_td.hpp"
#include "dogen/test_models/std_model/test_data/pkg1/class_c_td.hpp"

namespace {

dogen::test_models::std_model::pkg1::class_c
create_dogen_test_models_std_model_pkg1_class_c(const unsigned int position) {
    return dogen::test_models::std_model::pkg1::class_c_generator::create(position);
}

std::list<dogen::test_models::std_model::pkg1::class_c> create_std_list_dogen_test_models_std_model_pkg1_class_c(unsigned int position) {
    std::list<dogen::test_models::std_model::pkg1::class_c> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_test_models_std_model_pkg1_class_c(position + i));
    }
    return r;
}

}

namespace dogen {
namespace test_models {
namespace std_model {

derived_generator::derived_generator() : position_(0) { }

void derived_generator::
populate(const unsigned int position, result_type& v) {
    dogen::test_models::std_model::base_generator::populate(position, v);
    v.prop_1(create_std_list_dogen_test_models_std_model_pkg1_class_c(position + 0));
}

derived_generator::result_type
derived_generator::create(const unsigned int position) {
    derived r;
    derived_generator::populate(position, r);
    return r;
}

derived_generator::result_type*
derived_generator::create_ptr(const unsigned int position) {
    derived* p = new derived();
    derived_generator::populate(position, *p);
    return p;
}

derived_generator::result_type
derived_generator::operator()() {
    return create(position_++);
}

} } }
