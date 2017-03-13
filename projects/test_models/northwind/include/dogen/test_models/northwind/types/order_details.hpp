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
#ifndef DOGEN_TEST_MODELS_NORTHWIND_TYPES_ORDER_DETAILS_HPP
#define DOGEN_TEST_MODELS_NORTHWIND_TYPES_ORDER_DETAILS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/northwind/types/order_details_key.hpp"
#include "dogen/test_models/northwind/serialization/order_details_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

class order_details final {
public:
    order_details(const order_details&) = default;
    order_details(order_details&&) = default;
    ~order_details() = default;

public:
    order_details();

public:
    order_details(
        const dogen::test_models::northwind::order_details_key& order_details_key,
        const double unit_price,
        const int quantity,
        const double discount);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::northwind::order_details& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::northwind::order_details& v, unsigned int version);

public:
    const dogen::test_models::northwind::order_details_key& order_details_key() const;
    dogen::test_models::northwind::order_details_key& order_details_key();
    void order_details_key(const dogen::test_models::northwind::order_details_key& v);
    void order_details_key(const dogen::test_models::northwind::order_details_key&& v);

    double unit_price() const;
    void unit_price(const double v);

    int quantity() const;
    void quantity(const int v);

    double discount() const;
    void discount(const double v);

public:
    bool operator==(const order_details& rhs) const;
    bool operator!=(const order_details& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(order_details& other) noexcept;
    order_details& operator=(order_details other);

private:
    dogen::test_models::northwind::order_details_key order_details_key_;
    double unit_price_;
    int quantity_;
    double discount_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::northwind::order_details& lhs,
    dogen::test_models::northwind::order_details& rhs) {
    lhs.swap(rhs);
}

}

#endif
