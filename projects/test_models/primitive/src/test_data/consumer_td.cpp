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
#include "dogen/test_models/primitive/test_data/consumer_td.hpp"
#include "dogen/test_models/primitive/test_data/product_id_td.hpp"

namespace {

dogen::test_models::primitive::product_id
create_dogen_test_models_primitive_product_id(const unsigned int position) {
    return dogen::test_models::primitive::product_id_generator::create(position);
}

}

namespace dogen {
namespace test_models {
namespace primitive {

consumer_generator::consumer_generator() : position_(0) { }

void consumer_generator::
populate(const unsigned int position, result_type& v) {
    v.prop0(create_dogen_test_models_primitive_product_id(position + 0));
}

consumer_generator::result_type
consumer_generator::create(const unsigned int position) {
    consumer r;
    consumer_generator::populate(position, r);
    return r;
}

consumer_generator::result_type*
consumer_generator::create_ptr(const unsigned int position) {
    consumer* p = new consumer();
    consumer_generator::populate(position, *p);
    return p;
}

consumer_generator::result_type
consumer_generator::operator()() {
    return create(position_++);
}

} } }
