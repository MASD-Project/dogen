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
#ifndef DOGEN_TEST_MODELS_DATABASE_ODB_NORTHWIND_EMPLOYEE_TERRITORIES_KEY_PRAGMAS_HPP
#define DOGEN_TEST_MODELS_DATABASE_ODB_NORTHWIND_EMPLOYEE_TERRITORIES_KEY_PRAGMAS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/database/odb/northwind/employee_id_pragmas.hpp"
#include "dogen/test_models/database/odb/northwind/territory_id_pragmas.hpp"
#include "dogen/test_models/database/types/northwind/employee_territories_key.hpp"

namespace dogen {
namespace test_models {
namespace database {
namespace northwind {

#ifdef ODB_COMPILER

#pragma db value(employee_territories_key) schema("NORTHWIND")

#endif

} } } }

#endif
