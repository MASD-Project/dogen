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
#ifndef DOGEN_TEST_MODELS_NORTHWIND_ODB_ORDERS_PRAGMAS_HPP
#define DOGEN_TEST_MODELS_NORTHWIND_ODB_ORDERS_PRAGMAS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/northwind/types/orders.hpp"
#include "dogen/test_models/northwind/odb/order_id_pragmas.hpp"
#include "dogen/test_models/northwind/odb/customer_id_pragmas.hpp"
#include "dogen/test_models/northwind/odb/employee_id_pragmas.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

#ifdef ODB_COMPILER

#pragma db object(orders) schema("NORTHWIND")

#pragma db member(orders::order_id_) id
#pragma db member(orders::customer_id_) null
#pragma db member(orders::employee_id_) null
#pragma db member(orders::order_date_) null
#pragma db member(orders::required_date_) null
#pragma db member(orders::shipped_date_) null
#pragma db member(orders::ship_via_) null
#pragma db member(orders::freight_) null
#pragma db member(orders::ship_name_) null
#pragma db member(orders::ship_address_) null
#pragma db member(orders::ship_city_) null
#pragma db member(orders::ship_region_) null
#pragma db member(orders::ship_postal_code_) null
#pragma db member(orders::ship_country_) null

#endif

} } }

#endif
