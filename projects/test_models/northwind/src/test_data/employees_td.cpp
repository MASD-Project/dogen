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
#include "dogen/test_models/northwind/test_data/employees_td.hpp"
#include "dogen/test_models/northwind/test_data/employee_id_td.hpp"

namespace {

dogen::test_models::northwind::employee_id
create_dogen_test_models_northwind_employee_id(const unsigned int position) {
    return dogen::test_models::northwind::employee_id_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

boost::gregorian::date
create_boost_gregorian_date(const unsigned int position) {
    unsigned int day(1 + (position % 27));
    boost::gregorian::date r(2002, 2, day);
    return r;
}

}

namespace dogen {
namespace test_models {
namespace northwind {

employees_generator::employees_generator() : position_(0) { }

void employees_generator::
populate(const unsigned int position, result_type& v) {
    v.employee_id(create_dogen_test_models_northwind_employee_id(position + 0));
    v.last_name(create_std_string(position + 1));
    v.first_name(create_std_string(position + 2));
    v.title(create_std_string(position + 3));
    v.title_of_courtesy(create_std_string(position + 4));
    v.birth_date(create_boost_gregorian_date(position + 5));
    v.hire_date(create_boost_gregorian_date(position + 6));
    v.address(create_std_string(position + 7));
    v.city(create_std_string(position + 8));
    v.region(create_std_string(position + 9));
    v.postal_code(create_std_string(position + 10));
    v.country(create_std_string(position + 11));
    v.home_phone(create_std_string(position + 12));
    v.extension(create_std_string(position + 13));
    v.photo(create_std_string(position + 14));
    v.notes(create_std_string(position + 15));
    v.reports_to(create_dogen_test_models_northwind_employee_id(position + 16));
}

employees_generator::result_type
employees_generator::create(const unsigned int position) {
    employees r;
    employees_generator::populate(position, r);
    return r;
}

employees_generator::result_type*
employees_generator::create_ptr(const unsigned int position) {
    employees* p = new employees();
    employees_generator::populate(position, *p);
    return p;
}

employees_generator::result_type
employees_generator::operator()() {
    return create(position_++);
}

} } }
