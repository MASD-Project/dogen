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
#include "dogen/test_models/northwind/types/orders.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

orders::orders()
    : ship_via_(static_cast<int>(0)),
      freight_(static_cast<double>(0)) { }

orders::orders(
    const dogen::test_models::northwind::order_id& order_id,
    const dogen::test_models::northwind::customer_id& customer_id,
    const dogen::test_models::northwind::employee_id& employee_id,
    const boost::gregorian::date& order_date,
    const boost::gregorian::date& required_date,
    const boost::gregorian::date& shipped_date,
    const int ship_via,
    const double freight,
    const std::string& ship_name,
    const std::string& ship_address,
    const std::string& ship_city,
    const std::string& ship_region,
    const std::string& ship_postal_code,
    const std::string& ship_country)
    : order_id_(order_id),
      customer_id_(customer_id),
      employee_id_(employee_id),
      order_date_(order_date),
      required_date_(required_date),
      shipped_date_(shipped_date),
      ship_via_(ship_via),
      freight_(freight),
      ship_name_(ship_name),
      ship_address_(ship_address),
      ship_city_(ship_city),
      ship_region_(ship_region),
      ship_postal_code_(ship_postal_code),
      ship_country_(ship_country) { }

void orders::swap(orders& other) noexcept {
    using std::swap;
    swap(order_id_, other.order_id_);
    swap(customer_id_, other.customer_id_);
    swap(employee_id_, other.employee_id_);
    swap(order_date_, other.order_date_);
    swap(required_date_, other.required_date_);
    swap(shipped_date_, other.shipped_date_);
    swap(ship_via_, other.ship_via_);
    swap(freight_, other.freight_);
    swap(ship_name_, other.ship_name_);
    swap(ship_address_, other.ship_address_);
    swap(ship_city_, other.ship_city_);
    swap(ship_region_, other.ship_region_);
    swap(ship_postal_code_, other.ship_postal_code_);
    swap(ship_country_, other.ship_country_);
}

bool orders::operator==(const orders& rhs) const {
    return order_id_ == rhs.order_id_ &&
        customer_id_ == rhs.customer_id_ &&
        employee_id_ == rhs.employee_id_ &&
        order_date_ == rhs.order_date_ &&
        required_date_ == rhs.required_date_ &&
        shipped_date_ == rhs.shipped_date_ &&
        ship_via_ == rhs.ship_via_ &&
        freight_ == rhs.freight_ &&
        ship_name_ == rhs.ship_name_ &&
        ship_address_ == rhs.ship_address_ &&
        ship_city_ == rhs.ship_city_ &&
        ship_region_ == rhs.ship_region_ &&
        ship_postal_code_ == rhs.ship_postal_code_ &&
        ship_country_ == rhs.ship_country_;
}

orders& orders::operator=(orders other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::test_models::northwind::order_id& orders::order_id() const {
    return order_id_;
}

dogen::test_models::northwind::order_id& orders::order_id() {
    return order_id_;
}

void orders::order_id(const dogen::test_models::northwind::order_id& v) {
    order_id_ = v;
}

void orders::order_id(const dogen::test_models::northwind::order_id&& v) {
    order_id_ = std::move(v);
}

const dogen::test_models::northwind::customer_id& orders::customer_id() const {
    return customer_id_;
}

dogen::test_models::northwind::customer_id& orders::customer_id() {
    return customer_id_;
}

void orders::customer_id(const dogen::test_models::northwind::customer_id& v) {
    customer_id_ = v;
}

void orders::customer_id(const dogen::test_models::northwind::customer_id&& v) {
    customer_id_ = std::move(v);
}

const dogen::test_models::northwind::employee_id& orders::employee_id() const {
    return employee_id_;
}

dogen::test_models::northwind::employee_id& orders::employee_id() {
    return employee_id_;
}

void orders::employee_id(const dogen::test_models::northwind::employee_id& v) {
    employee_id_ = v;
}

void orders::employee_id(const dogen::test_models::northwind::employee_id&& v) {
    employee_id_ = std::move(v);
}

const boost::gregorian::date& orders::order_date() const {
    return order_date_;
}

boost::gregorian::date& orders::order_date() {
    return order_date_;
}

void orders::order_date(const boost::gregorian::date& v) {
    order_date_ = v;
}

void orders::order_date(const boost::gregorian::date&& v) {
    order_date_ = std::move(v);
}

const boost::gregorian::date& orders::required_date() const {
    return required_date_;
}

boost::gregorian::date& orders::required_date() {
    return required_date_;
}

void orders::required_date(const boost::gregorian::date& v) {
    required_date_ = v;
}

void orders::required_date(const boost::gregorian::date&& v) {
    required_date_ = std::move(v);
}

const boost::gregorian::date& orders::shipped_date() const {
    return shipped_date_;
}

boost::gregorian::date& orders::shipped_date() {
    return shipped_date_;
}

void orders::shipped_date(const boost::gregorian::date& v) {
    shipped_date_ = v;
}

void orders::shipped_date(const boost::gregorian::date&& v) {
    shipped_date_ = std::move(v);
}

int orders::ship_via() const {
    return ship_via_;
}

void orders::ship_via(const int v) {
    ship_via_ = v;
}

double orders::freight() const {
    return freight_;
}

void orders::freight(const double v) {
    freight_ = v;
}

const std::string& orders::ship_name() const {
    return ship_name_;
}

std::string& orders::ship_name() {
    return ship_name_;
}

void orders::ship_name(const std::string& v) {
    ship_name_ = v;
}

void orders::ship_name(const std::string&& v) {
    ship_name_ = std::move(v);
}

const std::string& orders::ship_address() const {
    return ship_address_;
}

std::string& orders::ship_address() {
    return ship_address_;
}

void orders::ship_address(const std::string& v) {
    ship_address_ = v;
}

void orders::ship_address(const std::string&& v) {
    ship_address_ = std::move(v);
}

const std::string& orders::ship_city() const {
    return ship_city_;
}

std::string& orders::ship_city() {
    return ship_city_;
}

void orders::ship_city(const std::string& v) {
    ship_city_ = v;
}

void orders::ship_city(const std::string&& v) {
    ship_city_ = std::move(v);
}

const std::string& orders::ship_region() const {
    return ship_region_;
}

std::string& orders::ship_region() {
    return ship_region_;
}

void orders::ship_region(const std::string& v) {
    ship_region_ = v;
}

void orders::ship_region(const std::string&& v) {
    ship_region_ = std::move(v);
}

const std::string& orders::ship_postal_code() const {
    return ship_postal_code_;
}

std::string& orders::ship_postal_code() {
    return ship_postal_code_;
}

void orders::ship_postal_code(const std::string& v) {
    ship_postal_code_ = v;
}

void orders::ship_postal_code(const std::string&& v) {
    ship_postal_code_ = std::move(v);
}

const std::string& orders::ship_country() const {
    return ship_country_;
}

std::string& orders::ship_country() {
    return ship_country_;
}

void orders::ship_country(const std::string& v) {
    ship_country_ = v;
}

void orders::ship_country(const std::string&& v) {
    ship_country_ = std::move(v);
}

} } }
