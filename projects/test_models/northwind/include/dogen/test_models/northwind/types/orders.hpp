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
#ifndef DOGEN_TEST_MODELS_NORTHWIND_TYPES_ORDERS_HPP
#define DOGEN_TEST_MODELS_NORTHWIND_TYPES_ORDERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include "dogen/test_models/northwind/types/order_id.hpp"
#include "dogen/test_models/northwind/types/customer_id.hpp"
#include "dogen/test_models/northwind/types/employee_id.hpp"
#include "dogen/test_models/northwind/serialization/orders_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

class orders final {
public:
    orders(const orders&) = default;
    orders(orders&&) = default;
    ~orders() = default;

public:
    orders();

public:
    orders(
        const dogen::test_models::northwind::order_id& order_id,
        const dogen::test_models::northwind::customer_id& customer_id,
        const dogen::test_models::northwind::employee_id& employee_id,
        const boost::gregorian::date& order_date,
        const boost::gregorian::date& required_date,
        const boost::gregorian::date& shipped_date,
        const int ship_via,
        const double freight,
        const std::string& ship_name,
        const std::string& ship_address,
        const std::string& ship_city,
        const std::string& ship_region,
        const std::string& ship_postal_code,
        const std::string& ship_country);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::northwind::orders& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::northwind::orders& v, unsigned int version);

public:
    const dogen::test_models::northwind::order_id& order_id() const;
    dogen::test_models::northwind::order_id& order_id();
    void order_id(const dogen::test_models::northwind::order_id& v);
    void order_id(const dogen::test_models::northwind::order_id&& v);

    const dogen::test_models::northwind::customer_id& customer_id() const;
    dogen::test_models::northwind::customer_id& customer_id();
    void customer_id(const dogen::test_models::northwind::customer_id& v);
    void customer_id(const dogen::test_models::northwind::customer_id&& v);

    const dogen::test_models::northwind::employee_id& employee_id() const;
    dogen::test_models::northwind::employee_id& employee_id();
    void employee_id(const dogen::test_models::northwind::employee_id& v);
    void employee_id(const dogen::test_models::northwind::employee_id&& v);

    const boost::gregorian::date& order_date() const;
    boost::gregorian::date& order_date();
    void order_date(const boost::gregorian::date& v);
    void order_date(const boost::gregorian::date&& v);

    const boost::gregorian::date& required_date() const;
    boost::gregorian::date& required_date();
    void required_date(const boost::gregorian::date& v);
    void required_date(const boost::gregorian::date&& v);

    const boost::gregorian::date& shipped_date() const;
    boost::gregorian::date& shipped_date();
    void shipped_date(const boost::gregorian::date& v);
    void shipped_date(const boost::gregorian::date&& v);

    int ship_via() const;
    void ship_via(const int v);

    double freight() const;
    void freight(const double v);

    const std::string& ship_name() const;
    std::string& ship_name();
    void ship_name(const std::string& v);
    void ship_name(const std::string&& v);

    const std::string& ship_address() const;
    std::string& ship_address();
    void ship_address(const std::string& v);
    void ship_address(const std::string&& v);

    const std::string& ship_city() const;
    std::string& ship_city();
    void ship_city(const std::string& v);
    void ship_city(const std::string&& v);

    const std::string& ship_region() const;
    std::string& ship_region();
    void ship_region(const std::string& v);
    void ship_region(const std::string&& v);

    const std::string& ship_postal_code() const;
    std::string& ship_postal_code();
    void ship_postal_code(const std::string& v);
    void ship_postal_code(const std::string&& v);

    const std::string& ship_country() const;
    std::string& ship_country();
    void ship_country(const std::string& v);
    void ship_country(const std::string&& v);

public:
    bool operator==(const orders& rhs) const;
    bool operator!=(const orders& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(orders& other) noexcept;
    orders& operator=(orders other);

private:
    dogen::test_models::northwind::order_id order_id_;
    dogen::test_models::northwind::customer_id customer_id_;
    dogen::test_models::northwind::employee_id employee_id_;
    boost::gregorian::date order_date_;
    boost::gregorian::date required_date_;
    boost::gregorian::date shipped_date_;
    int ship_via_;
    double freight_;
    std::string ship_name_;
    std::string ship_address_;
    std::string ship_city_;
    std::string ship_region_;
    std::string ship_postal_code_;
    std::string ship_country_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::northwind::orders& lhs,
    dogen::test_models::northwind::orders& rhs) {
    lhs.swap(rhs);
}

}

#endif
