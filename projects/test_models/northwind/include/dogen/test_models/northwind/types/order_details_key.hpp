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
#ifndef DOGEN_TEST_MODELS_NORTHWIND_TYPES_ORDER_DETAILS_KEY_HPP
#define DOGEN_TEST_MODELS_NORTHWIND_TYPES_ORDER_DETAILS_KEY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/northwind/types/order_id.hpp"
#include "dogen/test_models/northwind/types/product_id.hpp"
#include "dogen/test_models/northwind/serialization/order_details_key_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

class order_details_key final {
public:
    order_details_key() = default;
    order_details_key(const order_details_key&) = default;
    order_details_key(order_details_key&&) = default;
    ~order_details_key() = default;

public:
    order_details_key(
        const dogen::test_models::northwind::order_id& order_id,
        const dogen::test_models::northwind::product_id& product_id);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::northwind::order_details_key& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::northwind::order_details_key& v, unsigned int version);

public:
    const dogen::test_models::northwind::order_id& order_id() const;
    dogen::test_models::northwind::order_id& order_id();
    void order_id(const dogen::test_models::northwind::order_id& v);
    void order_id(const dogen::test_models::northwind::order_id&& v);

    const dogen::test_models::northwind::product_id& product_id() const;
    dogen::test_models::northwind::product_id& product_id();
    void product_id(const dogen::test_models::northwind::product_id& v);
    void product_id(const dogen::test_models::northwind::product_id&& v);

public:
    bool operator==(const order_details_key& rhs) const;
    bool operator!=(const order_details_key& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(order_details_key& other) noexcept;
    order_details_key& operator=(order_details_key other);

private:
    dogen::test_models::northwind::order_id order_id_;
    dogen::test_models::northwind::product_id product_id_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::northwind::order_details_key& lhs,
    dogen::test_models::northwind::order_details_key& rhs) {
    lhs.swap(rhs);
}

}

#endif
