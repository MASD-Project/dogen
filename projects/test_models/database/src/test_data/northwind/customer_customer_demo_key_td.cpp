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
#include "dogen/test_models/database/test_data/northwind/customer_id_td.hpp"
#include "dogen/test_models/database/test_data/northwind/customer_type_id_td.hpp"
#include "dogen/test_models/database/test_data/northwind/customer_customer_demo_key_td.hpp"

namespace {

dogen::test_models::database::northwind::customer_id
create_dogen_test_models_database_northwind_customer_id(const unsigned int position) {
    return dogen::test_models::database::northwind::customer_id_generator::create(position);
}

dogen::test_models::database::northwind::customer_type_id
create_dogen_test_models_database_northwind_customer_type_id(const unsigned int position) {
    return dogen::test_models::database::northwind::customer_type_id_generator::create(position);
}

}

namespace dogen {
namespace test_models {
namespace database {
namespace northwind {

customer_customer_demo_key_generator::customer_customer_demo_key_generator() : position_(0) { }

void customer_customer_demo_key_generator::
populate(const unsigned int position, result_type& v) {
    v.customer_id(create_dogen_test_models_database_northwind_customer_id(position + 0));
    v.customer_type(create_dogen_test_models_database_northwind_customer_type_id(position + 1));
}

customer_customer_demo_key_generator::result_type
customer_customer_demo_key_generator::create(const unsigned int position) {
    customer_customer_demo_key r;
    customer_customer_demo_key_generator::populate(position, r);
    return r;
}

customer_customer_demo_key_generator::result_type*
customer_customer_demo_key_generator::create_ptr(const unsigned int position) {
    customer_customer_demo_key* p = new customer_customer_demo_key();
    customer_customer_demo_key_generator::populate(position, *p);
    return p;
}

customer_customer_demo_key_generator::result_type
customer_customer_demo_key_generator::operator()() {
    return create(position_++);
}

} } } }
