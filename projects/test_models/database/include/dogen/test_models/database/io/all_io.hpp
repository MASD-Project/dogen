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
#ifndef DOGEN_TEST_MODELS_DATABASE_IO_ALL_IO_HPP
#define DOGEN_TEST_MODELS_DATABASE_IO_ALL_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/database/io/no_keys_io.hpp"
#include "dogen/test_models/database/io/no_keys_2_io.hpp"
#include "dogen/test_models/database/io/foreign_key_io.hpp"
#include "dogen/test_models/database/io/primary_key_io.hpp"
#include "dogen/test_models/database/io/primary_key_2_io.hpp"
#include "dogen/test_models/database/io/northwind/orders_io.hpp"
#include "dogen/test_models/database/io/northwind/region_io.hpp"
#include "dogen/test_models/database/io/northwind/order_id_io.hpp"
#include "dogen/test_models/database/io/northwind/products_io.hpp"
#include "dogen/test_models/database/io/northwind/shippers_io.hpp"
#include "dogen/test_models/database/io/northwind/supplier_io.hpp"
#include "dogen/test_models/database/io/northwind/customers_io.hpp"
#include "dogen/test_models/database/io/northwind/employees_io.hpp"
#include "dogen/test_models/database/io/northwind/region_id_io.hpp"
#include "dogen/test_models/database/io/northwind/territory_io.hpp"
#include "dogen/test_models/database/io/northwind/categories_io.hpp"
#include "dogen/test_models/database/io/northwind/product_id_io.hpp"
#include "dogen/test_models/database/io/northwind/shipper_id_io.hpp"
#include "dogen/test_models/database/io/northwind/category_id_io.hpp"
#include "dogen/test_models/database/io/northwind/customer_id_io.hpp"
#include "dogen/test_models/database/io/northwind/employee_id_io.hpp"
#include "dogen/test_models/database/io/northwind/supplier_id_io.hpp"
#include "dogen/test_models/database/io/northwind/territory_id_io.hpp"
#include "dogen/test_models/database/io/northwind/order_details_io.hpp"
#include "dogen/test_models/database/io/northwind/customer_type_id_io.hpp"
#include "dogen/test_models/database/io/northwind/order_details_key_io.hpp"
#include "dogen/test_models/database/io/northwind/employee_territories_io.hpp"
#include "dogen/test_models/database/io/northwind/customer_demographics_io.hpp"
#include "dogen/test_models/database/io/northwind/customer_customer_demo_io.hpp"
#include "dogen/test_models/database/io/northwind/employee_territories_key_io.hpp"
#include "dogen/test_models/database/io/northwind/customer_customer_demo_key_io.hpp"

#endif
