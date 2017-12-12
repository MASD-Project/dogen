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
#include "dogen/test_models/northwind/test_data/suppliers_td.hpp"
#include "dogen/test_models/northwind/test_data/supplier_id_td.hpp"

namespace {

dogen::test_models::northwind::supplier_id
create_dogen_test_models_northwind_supplier_id(const unsigned int position) {
    return dogen::test_models::northwind::supplier_id_generator::create(position);
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

suppliers_generator::suppliers_generator() : position_(0) { }

void suppliers_generator::
populate(const unsigned int position, result_type& v) {
    v.supplier_id(create_dogen_test_models_northwind_supplier_id(position + 0));
    v.company_name(create_std_string(position + 1));
    v.contact_name(create_std_string(position + 2));
    v.contact_title(create_std_string(position + 3));
    v.address(create_std_string(position + 4));
    v.city(create_std_string(position + 5));
    v.region(create_std_string(position + 6));
    v.postal_code(create_std_string(position + 7));
    v.country(create_std_string(position + 8));
    v.phone(create_std_string(position + 9));
    v.fax(create_std_string(position + 10));
    v.home_page(create_std_string(position + 11));
}

suppliers_generator::result_type
suppliers_generator::create(const unsigned int position) {
    suppliers r;
    suppliers_generator::populate(position, r);
    return r;
}

suppliers_generator::result_type*
suppliers_generator::create_ptr(const unsigned int position) {
    suppliers* p = new suppliers();
    suppliers_generator::populate(position, *p);
    return p;
}

suppliers_generator::result_type
suppliers_generator::operator()() {
    return create(position_++);
}

} } }
