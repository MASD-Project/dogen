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
#include "dogen/test_models/northwind/types/order_details_key.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

order_details_key::order_details_key(
    const dogen::test_models::northwind::order_id& order_id,
    const dogen::test_models::northwind::product_id& product_id)
    : order_id_(order_id),
      product_id_(product_id) { }

void order_details_key::swap(order_details_key& other) noexcept {
    using std::swap;
    swap(order_id_, other.order_id_);
    swap(product_id_, other.product_id_);
}

bool order_details_key::operator==(const order_details_key& rhs) const {
    return order_id_ == rhs.order_id_ &&
        product_id_ == rhs.product_id_;
}

order_details_key& order_details_key::operator=(order_details_key other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::test_models::northwind::order_id& order_details_key::order_id() const {
    return order_id_;
}

dogen::test_models::northwind::order_id& order_details_key::order_id() {
    return order_id_;
}

void order_details_key::order_id(const dogen::test_models::northwind::order_id& v) {
    order_id_ = v;
}

void order_details_key::order_id(const dogen::test_models::northwind::order_id&& v) {
    order_id_ = std::move(v);
}

const dogen::test_models::northwind::product_id& order_details_key::product_id() const {
    return product_id_;
}

dogen::test_models::northwind::product_id& order_details_key::product_id() {
    return product_id_;
}

void order_details_key::product_id(const dogen::test_models::northwind::product_id& v) {
    product_id_ = v;
}

void order_details_key::product_id(const dogen::test_models::northwind::product_id&& v) {
    product_id_ = std::move(v);
}

} } }
