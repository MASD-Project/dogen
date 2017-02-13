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
#include "dogen/test_models/database/types/northwind/customer_demographics.hpp"

namespace dogen {
namespace test_models {
namespace database {
namespace northwind {

customer_demographics::customer_demographics(
    const dogen::test_models::database::northwind::customer_type_id& customer_type_id,
    const std::string& customer_description)
    : customer_type_id_(customer_type_id),
      customer_description_(customer_description) { }

void customer_demographics::swap(customer_demographics& other) noexcept {
    using std::swap;
    swap(customer_type_id_, other.customer_type_id_);
    swap(customer_description_, other.customer_description_);
}

bool customer_demographics::operator==(const customer_demographics& rhs) const {
    return customer_type_id_ == rhs.customer_type_id_ &&
        customer_description_ == rhs.customer_description_;
}

customer_demographics& customer_demographics::operator=(customer_demographics other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::test_models::database::northwind::customer_type_id& customer_demographics::customer_type_id() const {
    return customer_type_id_;
}

dogen::test_models::database::northwind::customer_type_id& customer_demographics::customer_type_id() {
    return customer_type_id_;
}

void customer_demographics::customer_type_id(const dogen::test_models::database::northwind::customer_type_id& v) {
    customer_type_id_ = v;
}

void customer_demographics::customer_type_id(const dogen::test_models::database::northwind::customer_type_id&& v) {
    customer_type_id_ = std::move(v);
}

const std::string& customer_demographics::customer_description() const {
    return customer_description_;
}

std::string& customer_demographics::customer_description() {
    return customer_description_;
}

void customer_demographics::customer_description(const std::string& v) {
    customer_description_ = v;
}

void customer_demographics::customer_description(const std::string&& v) {
    customer_description_ = std::move(v);
}

} } } }
