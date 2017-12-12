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
#include "dogen/test_models/northwind/test_data/order_id_td.hpp"
#include "dogen/test_models/northwind/test_data/product_id_td.hpp"
#include "dogen/test_models/northwind/test_data/order_details_key_td.hpp"

namespace {

dogen::test_models::northwind::order_id
create_dogen_test_models_northwind_order_id(const unsigned int position) {
    return dogen::test_models::northwind::order_id_generator::create(position);
}

dogen::test_models::northwind::product_id
create_dogen_test_models_northwind_product_id(const unsigned int position) {
    return dogen::test_models::northwind::product_id_generator::create(position);
}

}

namespace dogen {
namespace test_models {
namespace northwind {

order_details_key_generator::order_details_key_generator() : position_(0) { }

void order_details_key_generator::
populate(const unsigned int position, result_type& v) {
    v.order_id(create_dogen_test_models_northwind_order_id(position + 0));
    v.product_id(create_dogen_test_models_northwind_product_id(position + 1));
}

order_details_key_generator::result_type
order_details_key_generator::create(const unsigned int position) {
    order_details_key r;
    order_details_key_generator::populate(position, r);
    return r;
}

order_details_key_generator::result_type*
order_details_key_generator::create_ptr(const unsigned int position) {
    order_details_key* p = new order_details_key();
    order_details_key_generator::populate(position, *p);
    return p;
}

order_details_key_generator::result_type
order_details_key_generator::operator()() {
    return create(position_++);
}

} } }
