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
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/list.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen/test_models/northwind/serialization/region_ser.hpp"
#include "dogen/test_models/northwind/serialization/products_ser.hpp"
#include "dogen/test_models/northwind/serialization/shippers_ser.hpp"
#include "dogen/test_models/northwind/serialization/supplier_ser.hpp"
#include "dogen/test_models/northwind/serialization/customers_ser.hpp"
#include "dogen/test_models/northwind/serialization/employees_ser.hpp"
#include "dogen/test_models/northwind/serialization/territory_ser.hpp"
#include "dogen/test_models/northwind/serialization/categories_ser.hpp"
#include "dogen/test_models/northwind/serialization/repository_ser.hpp"
#include "dogen/test_models/northwind/serialization/order_details_ser.hpp"
#include "dogen/test_models/northwind/serialization/employee_territories_ser.hpp"
#include "dogen/test_models/northwind/serialization/customer_demographics_ser.hpp"
#include "dogen/test_models/northwind/serialization/customer_customer_demo_ser.hpp"

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::test_models::northwind::repository& v,
    const unsigned int /*version*/) {
    ar << make_nvp("territories", v.territories_);
    ar << make_nvp("regions", v.regions_);
    ar << make_nvp("employees", v.employees_);
    ar << make_nvp("employee_territories", v.employee_territories_);
    ar << make_nvp("order_details", v.order_details_);
    ar << make_nvp("categories", v.categories_);
    ar << make_nvp("customer_demographics", v.customer_demographics_);
    ar << make_nvp("products", v.products_);
    ar << make_nvp("suppliers", v.suppliers_);
    ar << make_nvp("shippers", v.shippers_);
    ar << make_nvp("customer_customer_demos", v.customer_customer_demos_);
    ar << make_nvp("customers", v.customers_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::test_models::northwind::repository& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("territories", v.territories_);
    ar >> make_nvp("regions", v.regions_);
    ar >> make_nvp("employees", v.employees_);
    ar >> make_nvp("employee_territories", v.employee_territories_);
    ar >> make_nvp("order_details", v.order_details_);
    ar >> make_nvp("categories", v.categories_);
    ar >> make_nvp("customer_demographics", v.customer_demographics_);
    ar >> make_nvp("products", v.products_);
    ar >> make_nvp("suppliers", v.suppliers_);
    ar >> make_nvp("shippers", v.shippers_);
    ar >> make_nvp("customer_customer_demos", v.customer_customer_demos_);
    ar >> make_nvp("customers", v.customers_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::test_models::northwind::repository& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::test_models::northwind::repository& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::test_models::northwind::repository& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::test_models::northwind::repository& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::test_models::northwind::repository& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::test_models::northwind::repository& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::test_models::northwind::repository& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::test_models::northwind::repository& v, unsigned int version);

} }
