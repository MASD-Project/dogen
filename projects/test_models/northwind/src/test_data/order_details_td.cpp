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
#include "dogen/test_models/northwind/test_data/order_details_td.hpp"
#include "dogen/test_models/northwind/test_data/order_details_key_td.hpp"

namespace {

dogen::test_models::northwind::order_details_key
create_dogen_test_models_northwind_order_details_key(const unsigned int position) {
    return dogen::test_models::northwind::order_details_key_generator::create(position);
}

double create_double(const unsigned int position) {
    return static_cast<double>(position);
}

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

}

namespace dogen {
namespace test_models {
namespace northwind {

order_details_generator::order_details_generator() : position_(0) { }

void order_details_generator::
populate(const unsigned int position, result_type& v) {
    v.order_details_key(create_dogen_test_models_northwind_order_details_key(position + 0));
    v.unit_price(create_double(position + 1));
    v.quantity(create_int(position + 2));
    v.discount(create_double(position + 3));
}

order_details_generator::result_type
order_details_generator::create(const unsigned int position) {
    order_details r;
    order_details_generator::populate(position, r);
    return r;
}

order_details_generator::result_type*
order_details_generator::create_ptr(const unsigned int position) {
    order_details* p = new order_details();
    order_details_generator::populate(position, *p);
    return p;
}

order_details_generator::result_type
order_details_generator::operator()() {
    return create(position_++);
}

} } }
