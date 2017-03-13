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
#include "zango/northwind/types/customer_customer_demo_key.hpp"

namespace zango {
namespace northwind {

customer_customer_demo_key::customer_customer_demo_key(
    const zango::northwind::customer_id& customer_id,
    const zango::northwind::customer_type_id& customer_type_id)
    : customer_id_(customer_id),
      customer_type_id_(customer_type_id) { }

void customer_customer_demo_key::swap(customer_customer_demo_key& other) noexcept {
    using std::swap;
    swap(customer_id_, other.customer_id_);
    swap(customer_type_id_, other.customer_type_id_);
}

bool customer_customer_demo_key::operator==(const customer_customer_demo_key& rhs) const {
    return customer_id_ == rhs.customer_id_ &&
        customer_type_id_ == rhs.customer_type_id_;
}

customer_customer_demo_key& customer_customer_demo_key::operator=(customer_customer_demo_key other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const zango::northwind::customer_id& customer_customer_demo_key::customer_id() const {
    return customer_id_;
}

zango::northwind::customer_id& customer_customer_demo_key::customer_id() {
    return customer_id_;
}

void customer_customer_demo_key::customer_id(const zango::northwind::customer_id& v) {
    customer_id_ = v;
}

void customer_customer_demo_key::customer_id(const zango::northwind::customer_id&& v) {
    customer_id_ = std::move(v);
}

const zango::northwind::customer_type_id& customer_customer_demo_key::customer_type_id() const {
    return customer_type_id_;
}

zango::northwind::customer_type_id& customer_customer_demo_key::customer_type_id() {
    return customer_type_id_;
}

void customer_customer_demo_key::customer_type_id(const zango::northwind::customer_type_id& v) {
    customer_type_id_ = v;
}

void customer_customer_demo_key::customer_type_id(const zango::northwind::customer_type_id&& v) {
    customer_type_id_ = std::move(v);
}

} }
