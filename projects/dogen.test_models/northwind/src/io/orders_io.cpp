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
#include <boost/date_time/gregorian/gregorian.hpp>
#include "dogen/test_models/northwind/io/orders_io.hpp"
#include "dogen/test_models/northwind/io/order_id_io.hpp"
#include "dogen/test_models/northwind/io/customer_id_io.hpp"
#include "dogen/test_models/northwind/io/employee_id_io.hpp"

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

std::ostream& operator<<(std::ostream& s, const orders& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::northwind::orders\"" << ", "
      << "\"order_id\": " << v.order_id() << ", "
      << "\"customer_id\": " << v.customer_id() << ", "
      << "\"employee_id\": " << v.employee_id() << ", "
      << "\"order_date\": " << "\"" << v.order_date() << "\"" << ", "
      << "\"required_date\": " << "\"" << v.required_date() << "\"" << ", "
      << "\"shipped_date\": " << "\"" << v.shipped_date() << "\"" << ", "
      << "\"ship_via\": " << v.ship_via() << ", "
      << "\"freight\": " << v.freight() << ", "
      << "\"ship_name\": " << "\"" << tidy_up_string(v.ship_name()) << "\"" << ", "
      << "\"ship_address\": " << "\"" << tidy_up_string(v.ship_address()) << "\"" << ", "
      << "\"ship_city\": " << "\"" << tidy_up_string(v.ship_city()) << "\"" << ", "
      << "\"ship_region\": " << "\"" << tidy_up_string(v.ship_region()) << "\"" << ", "
      << "\"ship_postal_code\": " << "\"" << tidy_up_string(v.ship_postal_code()) << "\"" << ", "
      << "\"ship_country\": " << "\"" << tidy_up_string(v.ship_country()) << "\""
      << " }";
    return(s);
}

} } }
