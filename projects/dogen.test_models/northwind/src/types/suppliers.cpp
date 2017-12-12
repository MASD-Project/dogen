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
#include "dogen/test_models/northwind/types/suppliers.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

suppliers::suppliers(
    const dogen::test_models::northwind::supplier_id& supplier_id,
    const std::string& company_name,
    const std::string& contact_name,
    const std::string& contact_title,
    const std::string& address,
    const std::string& city,
    const std::string& region,
    const std::string& postal_code,
    const std::string& country,
    const std::string& phone,
    const std::string& fax,
    const std::string& home_page)
    : supplier_id_(supplier_id),
      company_name_(company_name),
      contact_name_(contact_name),
      contact_title_(contact_title),
      address_(address),
      city_(city),
      region_(region),
      postal_code_(postal_code),
      country_(country),
      phone_(phone),
      fax_(fax),
      home_page_(home_page) { }

void suppliers::swap(suppliers& other) noexcept {
    using std::swap;
    swap(supplier_id_, other.supplier_id_);
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
    swap(home_page_, other.home_page_);
}

bool suppliers::operator==(const suppliers& rhs) const {
    return supplier_id_ == rhs.supplier_id_ &&
        company_name_ == rhs.company_name_ &&
        contact_name_ == rhs.contact_name_ &&
        contact_title_ == rhs.contact_title_ &&
        address_ == rhs.address_ &&
        city_ == rhs.city_ &&
        region_ == rhs.region_ &&
        postal_code_ == rhs.postal_code_ &&
        country_ == rhs.country_ &&
        phone_ == rhs.phone_ &&
        fax_ == rhs.fax_ &&
        home_page_ == rhs.home_page_;
}

suppliers& suppliers::operator=(suppliers other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::test_models::northwind::supplier_id& suppliers::supplier_id() const {
    return supplier_id_;
}

dogen::test_models::northwind::supplier_id& suppliers::supplier_id() {
    return supplier_id_;
}

void suppliers::supplier_id(const dogen::test_models::northwind::supplier_id& v) {
    supplier_id_ = v;
}

void suppliers::supplier_id(const dogen::test_models::northwind::supplier_id&& v) {
    supplier_id_ = std::move(v);
}

const std::string& suppliers::company_name() const {
    return company_name_;
}

std::string& suppliers::company_name() {
    return company_name_;
}

void suppliers::company_name(const std::string& v) {
    company_name_ = v;
}

void suppliers::company_name(const std::string&& v) {
    company_name_ = std::move(v);
}

const std::string& suppliers::contact_name() const {
    return contact_name_;
}

std::string& suppliers::contact_name() {
    return contact_name_;
}

void suppliers::contact_name(const std::string& v) {
    contact_name_ = v;
}

void suppliers::contact_name(const std::string&& v) {
    contact_name_ = std::move(v);
}

const std::string& suppliers::contact_title() const {
    return contact_title_;
}

std::string& suppliers::contact_title() {
    return contact_title_;
}

void suppliers::contact_title(const std::string& v) {
    contact_title_ = v;
}

void suppliers::contact_title(const std::string&& v) {
    contact_title_ = std::move(v);
}

const std::string& suppliers::address() const {
    return address_;
}

std::string& suppliers::address() {
    return address_;
}

void suppliers::address(const std::string& v) {
    address_ = v;
}

void suppliers::address(const std::string&& v) {
    address_ = std::move(v);
}

const std::string& suppliers::city() const {
    return city_;
}

std::string& suppliers::city() {
    return city_;
}

void suppliers::city(const std::string& v) {
    city_ = v;
}

void suppliers::city(const std::string&& v) {
    city_ = std::move(v);
}

const std::string& suppliers::region() const {
    return region_;
}

std::string& suppliers::region() {
    return region_;
}

void suppliers::region(const std::string& v) {
    region_ = v;
}

void suppliers::region(const std::string&& v) {
    region_ = std::move(v);
}

const std::string& suppliers::postal_code() const {
    return postal_code_;
}

std::string& suppliers::postal_code() {
    return postal_code_;
}

void suppliers::postal_code(const std::string& v) {
    postal_code_ = v;
}

void suppliers::postal_code(const std::string&& v) {
    postal_code_ = std::move(v);
}

const std::string& suppliers::country() const {
    return country_;
}

std::string& suppliers::country() {
    return country_;
}

void suppliers::country(const std::string& v) {
    country_ = v;
}

void suppliers::country(const std::string&& v) {
    country_ = std::move(v);
}

const std::string& suppliers::phone() const {
    return phone_;
}

std::string& suppliers::phone() {
    return phone_;
}

void suppliers::phone(const std::string& v) {
    phone_ = v;
}

void suppliers::phone(const std::string&& v) {
    phone_ = std::move(v);
}

const std::string& suppliers::fax() const {
    return fax_;
}

std::string& suppliers::fax() {
    return fax_;
}

void suppliers::fax(const std::string& v) {
    fax_ = v;
}

void suppliers::fax(const std::string&& v) {
    fax_ = std::move(v);
}

const std::string& suppliers::home_page() const {
    return home_page_;
}

std::string& suppliers::home_page() {
    return home_page_;
}

void suppliers::home_page(const std::string& v) {
    home_page_ = v;
}

void suppliers::home_page(const std::string&& v) {
    home_page_ = std::move(v);
}

} } }
