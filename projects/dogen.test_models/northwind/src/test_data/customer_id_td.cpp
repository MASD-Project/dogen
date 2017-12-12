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
#include "dogen/test_models/northwind/test_data/customer_id_td.hpp"

namespace {

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

}

namespace dogen {
namespace test_models {
namespace northwind {

customer_id_generator::customer_id_generator() : position_(0) { }

void customer_id_generator::
populate(const unsigned int position, result_type& v) {
    v.value(create_int(position + 1));
}

customer_id_generator::result_type
customer_id_generator::create(const unsigned int position) {
    customer_id r;
    customer_id_generator::populate(position, r);
    return r;
}

customer_id_generator::result_type*
customer_id_generator::create_ptr(const unsigned int position) {
    customer_id* r = new customer_id();
    customer_id_generator::populate(position, *r);
    return r;
}

customer_id_generator::result_type
customer_id_generator::operator()() {
    return create(position_++);
}

} } }
