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
#include <boost/io/ios_state.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/test_models/northwind/io/products_io.hpp"
#include "dogen/test_models/northwind/io/product_id_io.hpp"
#include "dogen/test_models/northwind/io/category_id_io.hpp"
#include "dogen/test_models/northwind/io/supplier_id_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace dogen {
namespace test_models {
namespace northwind {

std::ostream& operator<<(std::ostream& s, const products& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::northwind::products\"" << ", "
      << "\"product_id\": " << v.product_id() << ", "
      << "\"product_name\": " << "\"" << tidy_up_string(v.product_name()) << "\"" << ", "
      << "\"supplier_id\": " << v.supplier_id() << ", "
      << "\"category_id\": " << v.category_id() << ", "
      << "\"quantity_per_unit\": " << "\"" << tidy_up_string(v.quantity_per_unit()) << "\"" << ", "
      << "\"unit_price\": " << v.unit_price() << ", "
      << "\"units_in_stock\": " << v.units_in_stock() << ", "
      << "\"units_in_order\": " << v.units_in_order() << ", "
      << "\"reorder_level\": " << v.reorder_level() << ", "
      << "\"discontinued\": " << v.discontinued()
      << " }";
    return(s);
}

} } }
