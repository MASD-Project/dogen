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
#include "dogen/test_models/northwind/types/order_details.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

order_details::order_details()
    : unit_price_(static_cast<double>(0)),
      quantity_(static_cast<int>(0)),
      discount_(static_cast<double>(0)) { }

order_details::order_details(
    const dogen::test_models::northwind::order_details_key& order_details_key,
    const double unit_price,
    const int quantity,
    const double discount)
    : order_details_key_(order_details_key),
      unit_price_(unit_price),
      quantity_(quantity),
      discount_(discount) { }

void order_details::swap(order_details& other) noexcept {
    using std::swap;
    swap(order_details_key_, other.order_details_key_);
    swap(unit_price_, other.unit_price_);
    swap(quantity_, other.quantity_);
    swap(discount_, other.discount_);
}

bool order_details::operator==(const order_details& rhs) const {
    return order_details_key_ == rhs.order_details_key_ &&
        unit_price_ == rhs.unit_price_ &&
        quantity_ == rhs.quantity_ &&
        discount_ == rhs.discount_;
}

order_details& order_details::operator=(order_details other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::test_models::northwind::order_details_key& order_details::order_details_key() const {
    return order_details_key_;
}

dogen::test_models::northwind::order_details_key& order_details::order_details_key() {
    return order_details_key_;
}

void order_details::order_details_key(const dogen::test_models::northwind::order_details_key& v) {
    order_details_key_ = v;
}

void order_details::order_details_key(const dogen::test_models::northwind::order_details_key&& v) {
    order_details_key_ = std::move(v);
}

double order_details::unit_price() const {
    return unit_price_;
}

void order_details::unit_price(const double v) {
    unit_price_ = v;
}

int order_details::quantity() const {
    return quantity_;
}

void order_details::quantity(const int v) {
    quantity_ = v;
}

double order_details::discount() const {
    return discount_;
}

void order_details::discount(const double v) {
    discount_ = v;
}

} } }
