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
#include "dogen/test_models/northwind/types/employee_territories_key.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

employee_territories_key::employee_territories_key(
    const dogen::test_models::northwind::employee_id& employee_id,
    const dogen::test_models::northwind::territory_id& territory_id)
    : employee_id_(employee_id),
      territory_id_(territory_id) { }

void employee_territories_key::swap(employee_territories_key& other) noexcept {
    using std::swap;
    swap(employee_id_, other.employee_id_);
    swap(territory_id_, other.territory_id_);
}

bool employee_territories_key::operator==(const employee_territories_key& rhs) const {
    return employee_id_ == rhs.employee_id_ &&
        territory_id_ == rhs.territory_id_;
}

employee_territories_key& employee_territories_key::operator=(employee_territories_key other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::test_models::northwind::employee_id& employee_territories_key::employee_id() const {
    return employee_id_;
}

dogen::test_models::northwind::employee_id& employee_territories_key::employee_id() {
    return employee_id_;
}

void employee_territories_key::employee_id(const dogen::test_models::northwind::employee_id& v) {
    employee_id_ = v;
}

void employee_territories_key::employee_id(const dogen::test_models::northwind::employee_id&& v) {
    employee_id_ = std::move(v);
}

const dogen::test_models::northwind::territory_id& employee_territories_key::territory_id() const {
    return territory_id_;
}

dogen::test_models::northwind::territory_id& employee_territories_key::territory_id() {
    return territory_id_;
}

void employee_territories_key::territory_id(const dogen::test_models::northwind::territory_id& v) {
    territory_id_ = v;
}

void employee_territories_key::territory_id(const dogen::test_models::northwind::territory_id&& v) {
    territory_id_ = std::move(v);
}

} } }
