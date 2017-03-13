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
#include "dogen/test_models/northwind/test_data/shippers_td.hpp"
#include "dogen/test_models/northwind/test_data/shipper_id_td.hpp"

namespace {

dogen::test_models::northwind::shipper_id
create_dogen_test_models_northwind_shipper_id(const unsigned int position) {
    return dogen::test_models::northwind::shipper_id_generator::create(position);
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

shippers_generator::shippers_generator() : position_(0) { }

void shippers_generator::
populate(const unsigned int position, result_type& v) {
    v.shipper_id(create_dogen_test_models_northwind_shipper_id(position + 0));
    v.company_name(create_std_string(position + 1));
    v.phone(create_std_string(position + 2));
}

shippers_generator::result_type
shippers_generator::create(const unsigned int position) {
    shippers r;
    shippers_generator::populate(position, r);
    return r;
}

shippers_generator::result_type*
shippers_generator::create_ptr(const unsigned int position) {
    shippers* p = new shippers();
    shippers_generator::populate(position, *p);
    return p;
}

shippers_generator::result_type
shippers_generator::operator()() {
    return create(position_++);
}

} } }
