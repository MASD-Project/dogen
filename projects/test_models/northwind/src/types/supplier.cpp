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
#include "zango/northwind/types/supplier.hpp"

namespace zango {
namespace northwind {

supplier::supplier(
    const zango::northwind::supplier_id& supplier_id,
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

void supplier::swap(supplier& other) noexcept {
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

bool supplier::operator==(const supplier& rhs) const {
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

supplier& supplier::operator=(supplier other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const zango::northwind::supplier_id& supplier::supplier_id() const {
    return supplier_id_;
}

zango::northwind::supplier_id& supplier::supplier_id() {
    return supplier_id_;
}

void supplier::supplier_id(const zango::northwind::supplier_id& v) {
    supplier_id_ = v;
}

void supplier::supplier_id(const zango::northwind::supplier_id&& v) {
    supplier_id_ = std::move(v);
}

const std::string& supplier::company_name() const {
    return company_name_;
}

std::string& supplier::company_name() {
    return company_name_;
}

void supplier::company_name(const std::string& v) {
    company_name_ = v;
}

void supplier::company_name(const std::string&& v) {
    company_name_ = std::move(v);
}

const std::string& supplier::contact_name() const {
    return contact_name_;
}

std::string& supplier::contact_name() {
    return contact_name_;
}

void supplier::contact_name(const std::string& v) {
    contact_name_ = v;
}

void supplier::contact_name(const std::string&& v) {
    contact_name_ = std::move(v);
}

const std::string& supplier::contact_title() const {
    return contact_title_;
}

std::string& supplier::contact_title() {
    return contact_title_;
}

void supplier::contact_title(const std::string& v) {
    contact_title_ = v;
}

void supplier::contact_title(const std::string&& v) {
    contact_title_ = std::move(v);
}

const std::string& supplier::address() const {
    return address_;
}

std::string& supplier::address() {
    return address_;
}

void supplier::address(const std::string& v) {
    address_ = v;
}

void supplier::address(const std::string&& v) {
    address_ = std::move(v);
}

const std::string& supplier::city() const {
    return city_;
}

std::string& supplier::city() {
    return city_;
}

void supplier::city(const std::string& v) {
    city_ = v;
}

void supplier::city(const std::string&& v) {
    city_ = std::move(v);
}

const std::string& supplier::region() const {
    return region_;
}

std::string& supplier::region() {
    return region_;
}

void supplier::region(const std::string& v) {
    region_ = v;
}

void supplier::region(const std::string&& v) {
    region_ = std::move(v);
}

const std::string& supplier::postal_code() const {
    return postal_code_;
}

std::string& supplier::postal_code() {
    return postal_code_;
}

void supplier::postal_code(const std::string& v) {
    postal_code_ = v;
}

void supplier::postal_code(const std::string&& v) {
    postal_code_ = std::move(v);
}

const std::string& supplier::country() const {
    return country_;
}

std::string& supplier::country() {
    return country_;
}

void supplier::country(const std::string& v) {
    country_ = v;
}

void supplier::country(const std::string&& v) {
    country_ = std::move(v);
}

const std::string& supplier::phone() const {
    return phone_;
}

std::string& supplier::phone() {
    return phone_;
}

void supplier::phone(const std::string& v) {
    phone_ = v;
}

void supplier::phone(const std::string&& v) {
    phone_ = std::move(v);
}

const std::string& supplier::fax() const {
    return fax_;
}

std::string& supplier::fax() {
    return fax_;
}

void supplier::fax(const std::string& v) {
    fax_ = v;
}

void supplier::fax(const std::string&& v) {
    fax_ = std::move(v);
}

const std::string& supplier::home_page() const {
    return home_page_;
}

std::string& supplier::home_page() {
    return home_page_;
}

void supplier::home_page(const std::string& v) {
    home_page_ = v;
}

void supplier::home_page(const std::string&& v) {
    home_page_ = std::move(v);
}

} }
