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
#include "dogen/test_models/northwind/test_data/products_td.hpp"
#include "dogen/test_models/northwind/test_data/product_id_td.hpp"
#include "dogen/test_models/northwind/test_data/category_id_td.hpp"
#include "dogen/test_models/northwind/test_data/supplier_id_td.hpp"

namespace {

dogen::test_models::northwind::product_id
create_dogen_test_models_northwind_product_id(const unsigned int position) {
    return dogen::test_models::northwind::product_id_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::test_models::northwind::supplier_id
create_dogen_test_models_northwind_supplier_id(const unsigned int position) {
    return dogen::test_models::northwind::supplier_id_generator::create(position);
}

dogen::test_models::northwind::category_id
create_dogen_test_models_northwind_category_id(const unsigned int position) {
    return dogen::test_models::northwind::category_id_generator::create(position);
}

double create_double(const unsigned int position) {
    return static_cast<double>(position);
}

int create_int(const unsigned int position) {
    return static_cast<int>(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

}

namespace dogen {
namespace test_models {
namespace northwind {

products_generator::products_generator() : position_(0) { }

void products_generator::
populate(const unsigned int position, result_type& v) {
    v.product_id(create_dogen_test_models_northwind_product_id(position + 0));
    v.product_name(create_std_string(position + 1));
    v.supplier_id(create_dogen_test_models_northwind_supplier_id(position + 2));
    v.category_id(create_dogen_test_models_northwind_category_id(position + 3));
    v.quantity_per_unit(create_std_string(position + 4));
    v.unit_price(create_double(position + 5));
    v.units_in_stock(create_int(position + 6));
    v.units_in_order(create_int(position + 7));
    v.reorder_level(create_int(position + 8));
    v.discontinued(create_bool(position + 9));
}

products_generator::result_type
products_generator::create(const unsigned int position) {
    products r;
    products_generator::populate(position, r);
    return r;
}

products_generator::result_type*
products_generator::create_ptr(const unsigned int position) {
    products* p = new products();
    products_generator::populate(position, *p);
    return p;
}

products_generator::result_type
products_generator::operator()() {
    return create(position_++);
}

} } }
