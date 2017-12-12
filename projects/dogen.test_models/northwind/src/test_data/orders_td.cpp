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
#include "dogen/test_models/northwind/test_data/orders_td.hpp"
#include "dogen/test_models/northwind/test_data/order_id_td.hpp"
#include "dogen/test_models/northwind/test_data/customer_id_td.hpp"
#include "dogen/test_models/northwind/test_data/employee_id_td.hpp"

namespace {

dogen::test_models::northwind::order_id
create_dogen_test_models_northwind_order_id(const unsigned int position) {
    return dogen::test_models::northwind::order_id_generator::create(position);
}

dogen::test_models::northwind::customer_id
create_dogen_test_models_northwind_customer_id(const unsigned int position) {
    return dogen::test_models::northwind::customer_id_generator::create(position);
}

dogen::test_models::northwind::employee_id
create_dogen_test_models_northwind_employee_id(const unsigned int position) {
    return dogen::test_models::northwind::employee_id_generator::create(position);
}

boost::gregorian::date
create_boost_gregorian_date(const unsigned int position) {
    unsigned int day(1 + (position % 27));
    boost::gregorian::date r(2002, 2, day);
    return r;
}

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

double create_double(const unsigned int position) {
    return static_cast<double>(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace test_models {
namespace northwind {

orders_generator::orders_generator() : position_(0) { }

void orders_generator::
populate(const unsigned int position, result_type& v) {
    v.order_id(create_dogen_test_models_northwind_order_id(position + 0));
    v.customer_id(create_dogen_test_models_northwind_customer_id(position + 1));
    v.employee_id(create_dogen_test_models_northwind_employee_id(position + 2));
    v.order_date(create_boost_gregorian_date(position + 3));
    v.required_date(create_boost_gregorian_date(position + 4));
    v.shipped_date(create_boost_gregorian_date(position + 5));
    v.ship_via(create_int(position + 6));
    v.freight(create_double(position + 7));
    v.ship_name(create_std_string(position + 8));
    v.ship_address(create_std_string(position + 9));
    v.ship_city(create_std_string(position + 10));
    v.ship_region(create_std_string(position + 11));
    v.ship_postal_code(create_std_string(position + 12));
    v.ship_country(create_std_string(position + 13));
}

orders_generator::result_type
orders_generator::create(const unsigned int position) {
    orders r;
    orders_generator::populate(position, r);
    return r;
}

orders_generator::result_type*
orders_generator::create_ptr(const unsigned int position) {
    orders* p = new orders();
    orders_generator::populate(position, *p);
    return p;
}

orders_generator::result_type
orders_generator::operator()() {
    return create(position_++);
}

} } }
