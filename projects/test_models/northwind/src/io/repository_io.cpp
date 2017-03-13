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
#include "zango/northwind/io/region_io.hpp"
#include "zango/northwind/io/products_io.hpp"
#include "zango/northwind/io/shippers_io.hpp"
#include "zango/northwind/io/supplier_io.hpp"
#include "zango/northwind/io/customers_io.hpp"
#include "zango/northwind/io/employees_io.hpp"
#include "zango/northwind/io/territory_io.hpp"
#include "zango/northwind/io/categories_io.hpp"
#include "zango/northwind/io/repository_io.hpp"
#include "zango/northwind/io/order_details_io.hpp"
#include "zango/northwind/io/employee_territories_io.hpp"
#include "zango/northwind/io/customer_demographics_io.hpp"
#include "zango/northwind/io/customer_customer_demo_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<zango::northwind::territory>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<zango::northwind::region>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<zango::northwind::employees>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<zango::northwind::employee_territories>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<zango::northwind::order_details>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<zango::northwind::categories>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<zango::northwind::customer_demographics>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<zango::northwind::products>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<zango::northwind::supplier>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<zango::northwind::shippers>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<zango::northwind::customer_customer_demo>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<zango::northwind::customers>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace zango {
namespace northwind {

std::ostream& operator<<(std::ostream& s, const repository& v) {
    s << " { "
      << "\"__type__\": " << "\"zango::northwind::repository\"" << ", "
      << "\"territories\": " << v.territories() << ", "
      << "\"regions\": " << v.regions() << ", "
      << "\"employees\": " << v.employees() << ", "
      << "\"employee_territories\": " << v.employee_territories() << ", "
      << "\"order_details\": " << v.order_details() << ", "
      << "\"categories\": " << v.categories() << ", "
      << "\"customer_demographics\": " << v.customer_demographics() << ", "
      << "\"products\": " << v.products() << ", "
      << "\"suppliers\": " << v.suppliers() << ", "
      << "\"shippers\": " << v.shippers() << ", "
      << "\"customer_customer_demos\": " << v.customer_customer_demos() << ", "
      << "\"customers\": " << v.customers()
      << " }";
    return(s);
}

} }
