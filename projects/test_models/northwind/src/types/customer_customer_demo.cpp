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
#include "dogen/test_models/northwind/types/customer_customer_demo.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

customer_customer_demo::customer_customer_demo(const dogen::test_models::northwind::customer_customer_demo_key& customer_customer_demo_key)
    : customer_customer_demo_key_(customer_customer_demo_key) { }

void customer_customer_demo::swap(customer_customer_demo& other) noexcept {
    using std::swap;
    swap(customer_customer_demo_key_, other.customer_customer_demo_key_);
}

bool customer_customer_demo::operator==(const customer_customer_demo& rhs) const {
    return customer_customer_demo_key_ == rhs.customer_customer_demo_key_;
}

customer_customer_demo& customer_customer_demo::operator=(customer_customer_demo other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::test_models::northwind::customer_customer_demo_key& customer_customer_demo::customer_customer_demo_key() const {
    return customer_customer_demo_key_;
}

dogen::test_models::northwind::customer_customer_demo_key& customer_customer_demo::customer_customer_demo_key() {
    return customer_customer_demo_key_;
}

void customer_customer_demo::customer_customer_demo_key(const dogen::test_models::northwind::customer_customer_demo_key& v) {
    customer_customer_demo_key_ = v;
}

void customer_customer_demo::customer_customer_demo_key(const dogen::test_models::northwind::customer_customer_demo_key&& v) {
    customer_customer_demo_key_ = std::move(v);
}

} } }
