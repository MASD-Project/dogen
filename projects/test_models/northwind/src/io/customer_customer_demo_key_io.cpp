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
#include <ostream>
#include "zango/northwind/io/customer_id_io.hpp"
#include "zango/northwind/io/customer_type_id_io.hpp"
#include "zango/northwind/io/customer_customer_demo_key_io.hpp"

namespace zango {
namespace northwind {

std::ostream& operator<<(std::ostream& s, const customer_customer_demo_key& v) {
    s << " { "
      << "\"__type__\": " << "\"zango::northwind::customer_customer_demo_key\"" << ", "
      << "\"customer_id\": " << v.customer_id() << ", "
      << "\"customer_type_id\": " << v.customer_type_id()
      << " }";
    return(s);
}

} }
