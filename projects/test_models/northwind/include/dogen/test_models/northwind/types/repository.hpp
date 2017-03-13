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
#ifndef DOGEN_TEST_MODELS_NORTHWIND_TYPES_REPOSITORY_HPP
#define DOGEN_TEST_MODELS_NORTHWIND_TYPES_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen/test_models/northwind/types/region.hpp"
#include "dogen/test_models/northwind/types/products.hpp"
#include "dogen/test_models/northwind/types/shippers.hpp"
#include "dogen/test_models/northwind/types/supplier.hpp"
#include "dogen/test_models/northwind/types/customers.hpp"
#include "dogen/test_models/northwind/types/employees.hpp"
#include "dogen/test_models/northwind/types/territory.hpp"
#include "dogen/test_models/northwind/types/categories.hpp"
#include "dogen/test_models/northwind/types/order_details.hpp"
#include "dogen/test_models/northwind/types/employee_territories.hpp"
#include "dogen/test_models/northwind/types/customer_demographics.hpp"
#include "dogen/test_models/northwind/types/customer_customer_demo.hpp"
#include "dogen/test_models/northwind/serialization/repository_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

class repository final {
public:
    repository() = default;
    repository(const repository&) = default;
    repository(repository&&) = default;
    ~repository() = default;

public:
    repository(
        const std::list<dogen::test_models::northwind::territory>& territories,
        const std::list<dogen::test_models::northwind::region>& regions,
        const std::list<dogen::test_models::northwind::employees>& employees,
        const std::list<dogen::test_models::northwind::employee_territories>& employee_territories,
        const std::list<dogen::test_models::northwind::order_details>& order_details,
        const std::list<dogen::test_models::northwind::categories>& categories,
        const std::list<dogen::test_models::northwind::customer_demographics>& customer_demographics,
        const std::list<dogen::test_models::northwind::products>& products,
        const std::list<dogen::test_models::northwind::supplier>& suppliers,
        const std::list<dogen::test_models::northwind::shippers>& shippers,
        const std::list<dogen::test_models::northwind::customer_customer_demo>& customer_customer_demos,
        const std::list<dogen::test_models::northwind::customers>& customers);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::northwind::repository& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::northwind::repository& v, unsigned int version);

public:
    const std::list<dogen::test_models::northwind::territory>& territories() const;
    std::list<dogen::test_models::northwind::territory>& territories();
    void territories(const std::list<dogen::test_models::northwind::territory>& v);
    void territories(const std::list<dogen::test_models::northwind::territory>&& v);

    const std::list<dogen::test_models::northwind::region>& regions() const;
    std::list<dogen::test_models::northwind::region>& regions();
    void regions(const std::list<dogen::test_models::northwind::region>& v);
    void regions(const std::list<dogen::test_models::northwind::region>&& v);

    const std::list<dogen::test_models::northwind::employees>& employees() const;
    std::list<dogen::test_models::northwind::employees>& employees();
    void employees(const std::list<dogen::test_models::northwind::employees>& v);
    void employees(const std::list<dogen::test_models::northwind::employees>&& v);

    const std::list<dogen::test_models::northwind::employee_territories>& employee_territories() const;
    std::list<dogen::test_models::northwind::employee_territories>& employee_territories();
    void employee_territories(const std::list<dogen::test_models::northwind::employee_territories>& v);
    void employee_territories(const std::list<dogen::test_models::northwind::employee_territories>&& v);

    const std::list<dogen::test_models::northwind::order_details>& order_details() const;
    std::list<dogen::test_models::northwind::order_details>& order_details();
    void order_details(const std::list<dogen::test_models::northwind::order_details>& v);
    void order_details(const std::list<dogen::test_models::northwind::order_details>&& v);

    const std::list<dogen::test_models::northwind::categories>& categories() const;
    std::list<dogen::test_models::northwind::categories>& categories();
    void categories(const std::list<dogen::test_models::northwind::categories>& v);
    void categories(const std::list<dogen::test_models::northwind::categories>&& v);

    const std::list<dogen::test_models::northwind::customer_demographics>& customer_demographics() const;
    std::list<dogen::test_models::northwind::customer_demographics>& customer_demographics();
    void customer_demographics(const std::list<dogen::test_models::northwind::customer_demographics>& v);
    void customer_demographics(const std::list<dogen::test_models::northwind::customer_demographics>&& v);

    const std::list<dogen::test_models::northwind::products>& products() const;
    std::list<dogen::test_models::northwind::products>& products();
    void products(const std::list<dogen::test_models::northwind::products>& v);
    void products(const std::list<dogen::test_models::northwind::products>&& v);

    const std::list<dogen::test_models::northwind::supplier>& suppliers() const;
    std::list<dogen::test_models::northwind::supplier>& suppliers();
    void suppliers(const std::list<dogen::test_models::northwind::supplier>& v);
    void suppliers(const std::list<dogen::test_models::northwind::supplier>&& v);

    const std::list<dogen::test_models::northwind::shippers>& shippers() const;
    std::list<dogen::test_models::northwind::shippers>& shippers();
    void shippers(const std::list<dogen::test_models::northwind::shippers>& v);
    void shippers(const std::list<dogen::test_models::northwind::shippers>&& v);

    const std::list<dogen::test_models::northwind::customer_customer_demo>& customer_customer_demos() const;
    std::list<dogen::test_models::northwind::customer_customer_demo>& customer_customer_demos();
    void customer_customer_demos(const std::list<dogen::test_models::northwind::customer_customer_demo>& v);
    void customer_customer_demos(const std::list<dogen::test_models::northwind::customer_customer_demo>&& v);

    const std::list<dogen::test_models::northwind::customers>& customers() const;
    std::list<dogen::test_models::northwind::customers>& customers();
    void customers(const std::list<dogen::test_models::northwind::customers>& v);
    void customers(const std::list<dogen::test_models::northwind::customers>&& v);

public:
    bool operator==(const repository& rhs) const;
    bool operator!=(const repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(repository& other) noexcept;
    repository& operator=(repository other);

private:
    std::list<dogen::test_models::northwind::territory> territories_;
    std::list<dogen::test_models::northwind::region> regions_;
    std::list<dogen::test_models::northwind::employees> employees_;
    std::list<dogen::test_models::northwind::employee_territories> employee_territories_;
    std::list<dogen::test_models::northwind::order_details> order_details_;
    std::list<dogen::test_models::northwind::categories> categories_;
    std::list<dogen::test_models::northwind::customer_demographics> customer_demographics_;
    std::list<dogen::test_models::northwind::products> products_;
    std::list<dogen::test_models::northwind::supplier> suppliers_;
    std::list<dogen::test_models::northwind::shippers> shippers_;
    std::list<dogen::test_models::northwind::customer_customer_demo> customer_customer_demos_;
    std::list<dogen::test_models::northwind::customers> customers_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::northwind::repository& lhs,
    dogen::test_models::northwind::repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
