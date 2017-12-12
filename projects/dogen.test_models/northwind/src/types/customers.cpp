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
#include "dogen/test_models/northwind/types/customers.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

customers::customers(
    const dogen::test_models::northwind::customer_id& customer_id,
    const std::string& customer_code,
    const std::string& company_name,
    const std::string& contact_name,
    const std::string& contact_title,
    const std::string& address,
    const std::string& city,
    const std::string& region,
    const std::string& postal_code,
    const std::string& country,
    const std::string& phone,
    const std::string& fax)
    : customer_id_(customer_id),
      customer_code_(customer_code),
      company_name_(company_name),
      contact_name_(contact_name),
      contact_title_(contact_title),
      address_(address),
      city_(city),
      region_(region),
      postal_code_(postal_code),
      country_(country),
      phone_(phone),
      fax_(fax) { }

void customers::swap(customers& other) noexcept {
    using std::swap;
    swap(customer_id_, other.customer_id_);
    swap(customer_code_, other.customer_code_);
    swap(company_name_, other.company_name_);
    swap(contact_name_, other.contact_name_);
    swap(contact_title_, other.contact_title_);
    swap(address_, other.address_);
    swap(city_, other.city_);
    swap(region_, other.region_);
    swap(postal_code_, other.postal_code_);
    swap(country_, other.country_);
    swap(phone_, other.phone_);
    swap(fax_, other.fax_);
}

bool customers::operator==(const customers& rhs) const {
    return customer_id_ == rhs.customer_id_ &&
        customer_code_ == rhs.customer_code_ &&
        company_name_ == rhs.company_name_ &&
        contact_name_ == rhs.contact_name_ &&
        contact_title_ == rhs.contact_title_ &&
        address_ == rhs.address_ &&
        city_ == rhs.city_ &&
        region_ == rhs.region_ &&
        postal_code_ == rhs.postal_code_ &&
        country_ == rhs.country_ &&
        phone_ == rhs.phone_ &&
        fax_ == rhs.fax_;
}

customers& customers::operator=(customers other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::test_models::northwind::customer_id& customers::customer_id() const {
    return customer_id_;
}

dogen::test_models::northwind::customer_id& customers::customer_id() {
    return customer_id_;
}

void customers::customer_id(const dogen::test_models::northwind::customer_id& v) {
    customer_id_ = v;
}

void customers::customer_id(const dogen::test_models::northwind::customer_id&& v) {
    customer_id_ = std::move(v);
}

const std::string& customers::customer_code() const {
    return customer_code_;
}

std::string& customers::customer_code() {
    return customer_code_;
}

void customers::customer_code(const std::string& v) {
    customer_code_ = v;
}

void customers::customer_code(const std::string&& v) {
    customer_code_ = std::move(v);
}

const std::string& customers::company_name() const {
    return company_name_;
}

std::string& customers::company_name() {
    return company_name_;
}

void customers::company_name(const std::string& v) {
    company_name_ = v;
}

void customers::company_name(const std::string&& v) {
    company_name_ = std::move(v);
}

const std::string& customers::contact_name() const {
    return contact_name_;
}

std::string& customers::contact_name() {
    return contact_name_;
}

void customers::contact_name(const std::string& v) {
    contact_name_ = v;
}

void customers::contact_name(const std::string&& v) {
    contact_name_ = std::move(v);
}

const std::string& customers::contact_title() const {
    return contact_title_;
}

std::string& customers::contact_title() {
    return contact_title_;
}

void customers::contact_title(const std::string& v) {
    contact_title_ = v;
}

void customers::contact_title(const std::string&& v) {
    contact_title_ = std::move(v);
}

const std::string& customers::address() const {
    return address_;
}

std::string& customers::address() {
    return address_;
}

void customers::address(const std::string& v) {
    address_ = v;
}

void customers::address(const std::string&& v) {
    address_ = std::move(v);
}

const std::string& customers::city() const {
    return city_;
}

std::string& customers::city() {
    return city_;
}

void customers::city(const std::string& v) {
    city_ = v;
}

void customers::city(const std::string&& v) {
    city_ = std::move(v);
}

const std::string& customers::region() const {
    return region_;
}

std::string& customers::region() {
    return region_;
}

void customers::region(const std::string& v) {
    region_ = v;
}

void customers::region(const std::string&& v) {
    region_ = std::move(v);
}

const std::string& customers::postal_code() const {
    return postal_code_;
}

std::string& customers::postal_code() {
    return postal_code_;
}

void customers::postal_code(const std::string& v) {
    postal_code_ = v;
}

void customers::postal_code(const std::string&& v) {
    postal_code_ = std::move(v);
}

const std::string& customers::country() const {
    return country_;
}

std::string& customers::country() {
    return country_;
}

void customers::country(const std::string& v) {
    country_ = v;
}

void customers::country(const std::string&& v) {
    country_ = std::move(v);
}

const std::string& customers::phone() const {
    return phone_;
}

std::string& customers::phone() {
    return phone_;
}

void customers::phone(const std::string& v) {
    phone_ = v;
}

void customers::phone(const std::string&& v) {
    phone_ = std::move(v);
}

const std::string& customers::fax() const {
    return fax_;
}

std::string& customers::fax() {
    return fax_;
}

void customers::fax(const std::string& v) {
    fax_ = v;
}

void customers::fax(const std::string&& v) {
    fax_ = std::move(v);
}

} } }
