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
#include "zango/northwind/test_data/region_td.hpp"
#include "zango/northwind/test_data/products_td.hpp"
#include "zango/northwind/test_data/shippers_td.hpp"
#include "zango/northwind/test_data/supplier_td.hpp"
#include "zango/northwind/test_data/customers_td.hpp"
#include "zango/northwind/test_data/employees_td.hpp"
#include "zango/northwind/test_data/territory_td.hpp"
#include "zango/northwind/test_data/categories_td.hpp"
#include "zango/northwind/test_data/repository_td.hpp"
#include "zango/northwind/test_data/order_details_td.hpp"
#include "zango/northwind/test_data/employee_territories_td.hpp"
#include "zango/northwind/test_data/customer_demographics_td.hpp"
#include "zango/northwind/test_data/customer_customer_demo_td.hpp"

namespace {

zango::northwind::territory
create_zango_northwind_territory(const unsigned int position) {
    return zango::northwind::territory_generator::create(position);
}

std::list<zango::northwind::territory> create_std_list_zango_northwind_territory(unsigned int position) {
    std::list<zango::northwind::territory> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_zango_northwind_territory(position + i));
    }
    return r;
}

zango::northwind::region
create_zango_northwind_region(const unsigned int position) {
    return zango::northwind::region_generator::create(position);
}

std::list<zango::northwind::region> create_std_list_zango_northwind_region(unsigned int position) {
    std::list<zango::northwind::region> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_zango_northwind_region(position + i));
    }
    return r;
}

zango::northwind::employees
create_zango_northwind_employees(const unsigned int position) {
    return zango::northwind::employees_generator::create(position);
}

std::list<zango::northwind::employees> create_std_list_zango_northwind_employees(unsigned int position) {
    std::list<zango::northwind::employees> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_zango_northwind_employees(position + i));
    }
    return r;
}

zango::northwind::employee_territories
create_zango_northwind_employee_territories(const unsigned int position) {
    return zango::northwind::employee_territories_generator::create(position);
}

std::list<zango::northwind::employee_territories> create_std_list_zango_northwind_employee_territories(unsigned int position) {
    std::list<zango::northwind::employee_territories> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_zango_northwind_employee_territories(position + i));
    }
    return r;
}

zango::northwind::order_details
create_zango_northwind_order_details(const unsigned int position) {
    return zango::northwind::order_details_generator::create(position);
}

std::list<zango::northwind::order_details> create_std_list_zango_northwind_order_details(unsigned int position) {
    std::list<zango::northwind::order_details> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_zango_northwind_order_details(position + i));
    }
    return r;
}

zango::northwind::categories
create_zango_northwind_categories(const unsigned int position) {
    return zango::northwind::categories_generator::create(position);
}

std::list<zango::northwind::categories> create_std_list_zango_northwind_categories(unsigned int position) {
    std::list<zango::northwind::categories> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_zango_northwind_categories(position + i));
    }
    return r;
}

zango::northwind::customer_demographics
create_zango_northwind_customer_demographics(const unsigned int position) {
    return zango::northwind::customer_demographics_generator::create(position);
}

std::list<zango::northwind::customer_demographics> create_std_list_zango_northwind_customer_demographics(unsigned int position) {
    std::list<zango::northwind::customer_demographics> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_zango_northwind_customer_demographics(position + i));
    }
    return r;
}

zango::northwind::products
create_zango_northwind_products(const unsigned int position) {
    return zango::northwind::products_generator::create(position);
}

std::list<zango::northwind::products> create_std_list_zango_northwind_products(unsigned int position) {
    std::list<zango::northwind::products> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_zango_northwind_products(position + i));
    }
    return r;
}

zango::northwind::supplier
create_zango_northwind_supplier(const unsigned int position) {
    return zango::northwind::supplier_generator::create(position);
}

std::list<zango::northwind::supplier> create_std_list_zango_northwind_supplier(unsigned int position) {
    std::list<zango::northwind::supplier> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_zango_northwind_supplier(position + i));
    }
    return r;
}

zango::northwind::shippers
create_zango_northwind_shippers(const unsigned int position) {
    return zango::northwind::shippers_generator::create(position);
}

std::list<zango::northwind::shippers> create_std_list_zango_northwind_shippers(unsigned int position) {
    std::list<zango::northwind::shippers> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_zango_northwind_shippers(position + i));
    }
    return r;
}

zango::northwind::customer_customer_demo
create_zango_northwind_customer_customer_demo(const unsigned int position) {
    return zango::northwind::customer_customer_demo_generator::create(position);
}

std::list<zango::northwind::customer_customer_demo> create_std_list_zango_northwind_customer_customer_demo(unsigned int position) {
    std::list<zango::northwind::customer_customer_demo> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_zango_northwind_customer_customer_demo(position + i));
    }
    return r;
}

zango::northwind::customers
create_zango_northwind_customers(const unsigned int position) {
    return zango::northwind::customers_generator::create(position);
}

std::list<zango::northwind::customers> create_std_list_zango_northwind_customers(unsigned int position) {
    std::list<zango::northwind::customers> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_zango_northwind_customers(position + i));
    }
    return r;
}

}

namespace zango {
namespace northwind {

repository_generator::repository_generator() : position_(0) { }

void repository_generator::
populate(const unsigned int position, result_type& v) {
    v.territories(create_std_list_zango_northwind_territory(position + 0));
    v.regions(create_std_list_zango_northwind_region(position + 1));
    v.employees(create_std_list_zango_northwind_employees(position + 2));
    v.employee_territories(create_std_list_zango_northwind_employee_territories(position + 3));
    v.order_details(create_std_list_zango_northwind_order_details(position + 4));
    v.categories(create_std_list_zango_northwind_categories(position + 5));
    v.customer_demographics(create_std_list_zango_northwind_customer_demographics(position + 6));
    v.products(create_std_list_zango_northwind_products(position + 7));
    v.suppliers(create_std_list_zango_northwind_supplier(position + 8));
    v.shippers(create_std_list_zango_northwind_shippers(position + 9));
    v.customer_customer_demos(create_std_list_zango_northwind_customer_customer_demo(position + 10));
    v.customers(create_std_list_zango_northwind_customers(position + 11));
}

repository_generator::result_type
repository_generator::create(const unsigned int position) {
    repository r;
    repository_generator::populate(position, r);
    return r;
}

repository_generator::result_type*
repository_generator::create_ptr(const unsigned int position) {
    repository* p = new repository();
    repository_generator::populate(position, *p);
    return p;
}

repository_generator::result_type
repository_generator::operator()() {
    return create(position_++);
}

} }
