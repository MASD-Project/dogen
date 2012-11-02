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
#include "dogen/boost_model/test_data/class_a_td.hpp"
#include "dogen/boost_model/test_data/class_b_td.hpp"
#include "dogen/boost_model/test_data/versioned_key_td.hpp"

namespace {

dogen::boost_model::class_a
create_dogen_boost_model_class_a(const unsigned int position) {
    return dogen::boost_model::class_a_generator::create(position);
}

boost::shared_ptr<dogen::boost_model::class_a>
create_boost_shared_ptr_dogen_boost_model_class_a(unsigned int position) {
    boost::shared_ptr<dogen::boost_model::class_a> r(
        new dogen::boost_model::class_a(create_dogen_boost_model_class_a(position)));
    return r;
}

std::vector<boost::shared_ptr<dogen::boost_model::class_a> > create_std_vector_boost_shared_ptr_dogen_boost_model_class_a_(unsigned int position) {
    std::vector<boost::shared_ptr<dogen::boost_model::class_a> > r;
    for (unsigned int i(0); i < 10; ++i) {
        r.push_back(create_boost_shared_ptr_dogen_boost_model_class_a(position + i));
    }
    return r;
}

dogen::boost_model::versioned_key
create_dogen_boost_model_versioned_key(const unsigned int position) {
    return dogen::boost_model::versioned_key_generator::create(position);
}

}

namespace dogen {
namespace boost_model {

class_b_generator::class_b_generator() : position_(0) { }

void class_b_generator::
populate(const unsigned int position, result_type& v) {
    v.prop_0(create_boost_shared_ptr_dogen_boost_model_class_a(position + 0));
    v.prop_1(create_std_vector_boost_shared_ptr_dogen_boost_model_class_a_(position + 1));
    v.versioned_key(create_dogen_boost_model_versioned_key(position + 2));
}

class_b_generator::result_type
class_b_generator::create(const unsigned int position) {
    class_b r;
    class_b_generator::populate(position, r);
    return r;
}

class_b_generator::result_type
class_b_generator::operator()() {
    return create(position_++);
}

} }
