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
#include "dogen/test_models/northwind/test_data/customers_td.hpp"
#include "dogen/test_models/northwind/test_data/customer_id_td.hpp"

namespace {

dogen::test_models::northwind::customer_id
create_dogen_test_models_northwind_customer_id(const unsigned int position) {
    return dogen::test_models::northwind::customer_id_generator::create(position);
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

customers_generator::customers_generator() : position_(0) { }

void customers_generator::
populate(const unsigned int position, result_type& v) {
    v.customer_id(create_dogen_test_models_northwind_customer_id(position + 0));
    v.customer_code(create_std_string(position + 1));
    v.company_name(create_std_string(position + 2));
    v.contact_name(create_std_string(position + 3));
    v.contact_title(create_std_string(position + 4));
    v.address(create_std_string(position + 5));
    v.city(create_std_string(position + 6));
    v.region(create_std_string(position + 7));
    v.postal_code(create_std_string(position + 8));
    v.country(create_std_string(position + 9));
    v.phone(create_std_string(position + 10));
    v.fax(create_std_string(position + 11));
}

customers_generator::result_type
customers_generator::create(const unsigned int position) {
    customers r;
    customers_generator::populate(position, r);
    return r;
}

customers_generator::result_type*
customers_generator::create_ptr(const unsigned int position) {
    customers* p = new customers();
    customers_generator::populate(position, *p);
    return p;
}

customers_generator::result_type
customers_generator::operator()() {
    return create(position_++);
}

} } }
