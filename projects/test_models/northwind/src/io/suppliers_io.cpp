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
#include <boost/algorithm/string.hpp>
#include "dogen/test_models/northwind/io/suppliers_io.hpp"
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

std::ostream& operator<<(std::ostream& s, const suppliers& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::northwind::suppliers\"" << ", "
      << "\"supplier_id\": " << v.supplier_id() << ", "
      << "\"company_name\": " << "\"" << tidy_up_string(v.company_name()) << "\"" << ", "
      << "\"contact_name\": " << "\"" << tidy_up_string(v.contact_name()) << "\"" << ", "
      << "\"contact_title\": " << "\"" << tidy_up_string(v.contact_title()) << "\"" << ", "
      << "\"address\": " << "\"" << tidy_up_string(v.address()) << "\"" << ", "
      << "\"city\": " << "\"" << tidy_up_string(v.city()) << "\"" << ", "
      << "\"region\": " << "\"" << tidy_up_string(v.region()) << "\"" << ", "
      << "\"postal_code\": " << "\"" << tidy_up_string(v.postal_code()) << "\"" << ", "
      << "\"country\": " << "\"" << tidy_up_string(v.country()) << "\"" << ", "
      << "\"phone\": " << "\"" << tidy_up_string(v.phone()) << "\"" << ", "
      << "\"fax\": " << "\"" << tidy_up_string(v.fax()) << "\"" << ", "
      << "\"home_page\": " << "\"" << tidy_up_string(v.home_page()) << "\""
      << " }";
    return(s);
}

} } }
