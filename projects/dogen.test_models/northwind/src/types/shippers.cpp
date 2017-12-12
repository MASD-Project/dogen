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
#include "dogen/test_models/northwind/types/shippers.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

shippers::shippers(
    const dogen::test_models::northwind::shipper_id& shipper_id,
    const std::string& company_name,
    const std::string& phone)
    : shipper_id_(shipper_id),
      company_name_(company_name),
      phone_(phone) { }

void shippers::swap(shippers& other) noexcept {
    using std::swap;
    swap(shipper_id_, other.shipper_id_);
    swap(company_name_, other.company_name_);
    swap(phone_, other.phone_);
}

bool shippers::operator==(const shippers& rhs) const {
    return shipper_id_ == rhs.shipper_id_ &&
        company_name_ == rhs.company_name_ &&
        phone_ == rhs.phone_;
}

shippers& shippers::operator=(shippers other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::test_models::northwind::shipper_id& shippers::shipper_id() const {
    return shipper_id_;
}

dogen::test_models::northwind::shipper_id& shippers::shipper_id() {
    return shipper_id_;
}

void shippers::shipper_id(const dogen::test_models::northwind::shipper_id& v) {
    shipper_id_ = v;
}

void shippers::shipper_id(const dogen::test_models::northwind::shipper_id&& v) {
    shipper_id_ = std::move(v);
}

const std::string& shippers::company_name() const {
    return company_name_;
}

std::string& shippers::company_name() {
    return company_name_;
}

void shippers::company_name(const std::string& v) {
    company_name_ = v;
}

void shippers::company_name(const std::string&& v) {
    company_name_ = std::move(v);
}

const std::string& shippers::phone() const {
    return phone_;
}

std::string& shippers::phone() {
    return phone_;
}

void shippers::phone(const std::string& v) {
    phone_ = v;
}

void shippers::phone(const std::string&& v) {
    phone_ = std::move(v);
}

} } }
