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
#include "zango/northwind/test_data/customer_type_id_td.hpp"
#include "zango/northwind/test_data/customer_demographics_td.hpp"

namespace {

zango::northwind::customer_type_id
create_zango_northwind_customer_type_id(const unsigned int position) {
    return zango::northwind::customer_type_id_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace zango {
namespace northwind {

customer_demographics_generator::customer_demographics_generator() : position_(0) { }

void customer_demographics_generator::
populate(const unsigned int position, result_type& v) {
    v.customer_type_id(create_zango_northwind_customer_type_id(position + 0));
    v.customer_description(create_std_string(position + 1));
}

customer_demographics_generator::result_type
customer_demographics_generator::create(const unsigned int position) {
    customer_demographics r;
    customer_demographics_generator::populate(position, r);
    return r;
}

customer_demographics_generator::result_type*
customer_demographics_generator::create_ptr(const unsigned int position) {
    customer_demographics* p = new customer_demographics();
    customer_demographics_generator::populate(position, *p);
    return p;
}

customer_demographics_generator::result_type
customer_demographics_generator::operator()() {
    return create(position_++);
}

} }
