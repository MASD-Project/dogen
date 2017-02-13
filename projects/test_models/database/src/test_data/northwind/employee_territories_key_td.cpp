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
#include "dogen/test_models/database/test_data/northwind/employee_id_td.hpp"
#include "dogen/test_models/database/test_data/northwind/territory_id_td.hpp"
#include "dogen/test_models/database/test_data/northwind/employee_territories_key_td.hpp"

namespace {

dogen::test_models::database::northwind::employee_id
create_dogen_test_models_database_northwind_employee_id(const unsigned int position) {
    return dogen::test_models::database::northwind::employee_id_generator::create(position);
}

dogen::test_models::database::northwind::territory_id
create_dogen_test_models_database_northwind_territory_id(const unsigned int position) {
    return dogen::test_models::database::northwind::territory_id_generator::create(position);
}

}

namespace dogen {
namespace test_models {
namespace database {
namespace northwind {

employee_territories_key_generator::employee_territories_key_generator() : position_(0) { }

void employee_territories_key_generator::
populate(const unsigned int position, result_type& v) {
    v.employee_id(create_dogen_test_models_database_northwind_employee_id(position + 0));
    v.territory_id(create_dogen_test_models_database_northwind_territory_id(position + 1));
}

employee_territories_key_generator::result_type
employee_territories_key_generator::create(const unsigned int position) {
    employee_territories_key r;
    employee_territories_key_generator::populate(position, r);
    return r;
}

employee_territories_key_generator::result_type*
employee_territories_key_generator::create_ptr(const unsigned int position) {
    employee_territories_key* p = new employee_territories_key();
    employee_territories_key_generator::populate(position, *p);
    return p;
}

employee_territories_key_generator::result_type
employee_territories_key_generator::operator()() {
    return create(position_++);
}

} } } }
