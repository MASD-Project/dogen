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
#include "dogen/test_models/northwind/types/repository.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

repository::repository(
    const std::list<dogen::test_models::northwind::territory>& territories,
    const std::list<dogen::test_models::northwind::region>& regions,
    const std::list<dogen::test_models::northwind::employees>& employees,
    const std::list<dogen::test_models::northwind::employee_territories>& employee_territories,
    const std::list<dogen::test_models::northwind::order_details>& order_details,
    const std::list<dogen::test_models::northwind::categories>& categories,
    const std::list<dogen::test_models::northwind::customer_demographics>& customer_demographics,
    const std::list<dogen::test_models::northwind::products>& products,
    const std::list<dogen::test_models::northwind::supplier>& suppliers,
    const std::list<dogen::test_models::northwind::shippers>& shippers,
    const std::list<dogen::test_models::northwind::customer_customer_demo>& customer_customer_demos,
    const std::list<dogen::test_models::northwind::customers>& customers)
    : territories_(territories),
      regions_(regions),
      employees_(employees),
      employee_territories_(employee_territories),
      order_details_(order_details),
      categories_(categories),
      customer_demographics_(customer_demographics),
      products_(products),
      suppliers_(suppliers),
      shippers_(shippers),
      customer_customer_demos_(customer_customer_demos),
      customers_(customers) { }

void repository::swap(repository& other) noexcept {
    using std::swap;
    swap(territories_, other.territories_);
    swap(regions_, other.regions_);
    swap(employees_, other.employees_);
    swap(employee_territories_, other.employee_territories_);
    swap(order_details_, other.order_details_);
    swap(categories_, other.categories_);
    swap(customer_demographics_, other.customer_demographics_);
    swap(products_, other.products_);
    swap(suppliers_, other.suppliers_);
    swap(shippers_, other.shippers_);
    swap(customer_customer_demos_, other.customer_customer_demos_);
    swap(customers_, other.customers_);
}

bool repository::operator==(const repository& rhs) const {
    return territories_ == rhs.territories_ &&
        regions_ == rhs.regions_ &&
        employees_ == rhs.employees_ &&
        employee_territories_ == rhs.employee_territories_ &&
        order_details_ == rhs.order_details_ &&
        categories_ == rhs.categories_ &&
        customer_demographics_ == rhs.customer_demographics_ &&
        products_ == rhs.products_ &&
        suppliers_ == rhs.suppliers_ &&
        shippers_ == rhs.shippers_ &&
        customer_customer_demos_ == rhs.customer_customer_demos_ &&
        customers_ == rhs.customers_;
}

repository& repository::operator=(repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::test_models::northwind::territory>& repository::territories() const {
    return territories_;
}

std::list<dogen::test_models::northwind::territory>& repository::territories() {
    return territories_;
}

void repository::territories(const std::list<dogen::test_models::northwind::territory>& v) {
    territories_ = v;
}

void repository::territories(const std::list<dogen::test_models::northwind::territory>&& v) {
    territories_ = std::move(v);
}

const std::list<dogen::test_models::northwind::region>& repository::regions() const {
    return regions_;
}

std::list<dogen::test_models::northwind::region>& repository::regions() {
    return regions_;
}

void repository::regions(const std::list<dogen::test_models::northwind::region>& v) {
    regions_ = v;
}

void repository::regions(const std::list<dogen::test_models::northwind::region>&& v) {
    regions_ = std::move(v);
}

const std::list<dogen::test_models::northwind::employees>& repository::employees() const {
    return employees_;
}

std::list<dogen::test_models::northwind::employees>& repository::employees() {
    return employees_;
}

void repository::employees(const std::list<dogen::test_models::northwind::employees>& v) {
    employees_ = v;
}

void repository::employees(const std::list<dogen::test_models::northwind::employees>&& v) {
    employees_ = std::move(v);
}

const std::list<dogen::test_models::northwind::employee_territories>& repository::employee_territories() const {
    return employee_territories_;
}

std::list<dogen::test_models::northwind::employee_territories>& repository::employee_territories() {
    return employee_territories_;
}

void repository::employee_territories(const std::list<dogen::test_models::northwind::employee_territories>& v) {
    employee_territories_ = v;
}

void repository::employee_territories(const std::list<dogen::test_models::northwind::employee_territories>&& v) {
    employee_territories_ = std::move(v);
}

const std::list<dogen::test_models::northwind::order_details>& repository::order_details() const {
    return order_details_;
}

std::list<dogen::test_models::northwind::order_details>& repository::order_details() {
    return order_details_;
}

void repository::order_details(const std::list<dogen::test_models::northwind::order_details>& v) {
    order_details_ = v;
}

void repository::order_details(const std::list<dogen::test_models::northwind::order_details>&& v) {
    order_details_ = std::move(v);
}

const std::list<dogen::test_models::northwind::categories>& repository::categories() const {
    return categories_;
}

std::list<dogen::test_models::northwind::categories>& repository::categories() {
    return categories_;
}

void repository::categories(const std::list<dogen::test_models::northwind::categories>& v) {
    categories_ = v;
}

void repository::categories(const std::list<dogen::test_models::northwind::categories>&& v) {
    categories_ = std::move(v);
}

const std::list<dogen::test_models::northwind::customer_demographics>& repository::customer_demographics() const {
    return customer_demographics_;
}

std::list<dogen::test_models::northwind::customer_demographics>& repository::customer_demographics() {
    return customer_demographics_;
}

void repository::customer_demographics(const std::list<dogen::test_models::northwind::customer_demographics>& v) {
    customer_demographics_ = v;
}

void repository::customer_demographics(const std::list<dogen::test_models::northwind::customer_demographics>&& v) {
    customer_demographics_ = std::move(v);
}

const std::list<dogen::test_models::northwind::products>& repository::products() const {
    return products_;
}

std::list<dogen::test_models::northwind::products>& repository::products() {
    return products_;
}

void repository::products(const std::list<dogen::test_models::northwind::products>& v) {
    products_ = v;
}

void repository::products(const std::list<dogen::test_models::northwind::products>&& v) {
    products_ = std::move(v);
}

const std::list<dogen::test_models::northwind::supplier>& repository::suppliers() const {
    return suppliers_;
}

std::list<dogen::test_models::northwind::supplier>& repository::suppliers() {
    return suppliers_;
}

void repository::suppliers(const std::list<dogen::test_models::northwind::supplier>& v) {
    suppliers_ = v;
}

void repository::suppliers(const std::list<dogen::test_models::northwind::supplier>&& v) {
    suppliers_ = std::move(v);
}

const std::list<dogen::test_models::northwind::shippers>& repository::shippers() const {
    return shippers_;
}

std::list<dogen::test_models::northwind::shippers>& repository::shippers() {
    return shippers_;
}

void repository::shippers(const std::list<dogen::test_models::northwind::shippers>& v) {
    shippers_ = v;
}

void repository::shippers(const std::list<dogen::test_models::northwind::shippers>&& v) {
    shippers_ = std::move(v);
}

const std::list<dogen::test_models::northwind::customer_customer_demo>& repository::customer_customer_demos() const {
    return customer_customer_demos_;
}

std::list<dogen::test_models::northwind::customer_customer_demo>& repository::customer_customer_demos() {
    return customer_customer_demos_;
}

void repository::customer_customer_demos(const std::list<dogen::test_models::northwind::customer_customer_demo>& v) {
    customer_customer_demos_ = v;
}

void repository::customer_customer_demos(const std::list<dogen::test_models::northwind::customer_customer_demo>&& v) {
    customer_customer_demos_ = std::move(v);
}

const std::list<dogen::test_models::northwind::customers>& repository::customers() const {
    return customers_;
}

std::list<dogen::test_models::northwind::customers>& repository::customers() {
    return customers_;
}

void repository::customers(const std::list<dogen::test_models::northwind::customers>& v) {
    customers_ = v;
}

void repository::customers(const std::list<dogen::test_models::northwind::customers>&& v) {
    customers_ = std::move(v);
}

} } }
