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
#include "dogen/test_models/northwind/types/employees.hpp"

namespace dogen {
namespace test_models {
namespace northwind {

employees::employees(
    const dogen::test_models::northwind::employee_id& employee_id,
    const std::string& last_name,
    const std::string& first_name,
    const std::string& title,
    const std::string& title_of_courtesy,
    const boost::gregorian::date& birth_date,
    const boost::gregorian::date& hire_date,
    const std::string& address,
    const std::string& city,
    const std::string& region,
    const std::string& postal_code,
    const std::string& country,
    const std::string& home_phone,
    const std::string& extension,
    const std::string& photo,
    const std::string& notes,
    const dogen::test_models::northwind::employee_id& reports_to)
    : employee_id_(employee_id),
      last_name_(last_name),
      first_name_(first_name),
      title_(title),
      title_of_courtesy_(title_of_courtesy),
      birth_date_(birth_date),
      hire_date_(hire_date),
      address_(address),
      city_(city),
      region_(region),
      postal_code_(postal_code),
      country_(country),
      home_phone_(home_phone),
      extension_(extension),
      photo_(photo),
      notes_(notes),
      reports_to_(reports_to) { }

void employees::swap(employees& other) noexcept {
    using std::swap;
    swap(employee_id_, other.employee_id_);
    swap(last_name_, other.last_name_);
    swap(first_name_, other.first_name_);
    swap(title_, other.title_);
    swap(title_of_courtesy_, other.title_of_courtesy_);
    swap(birth_date_, other.birth_date_);
    swap(hire_date_, other.hire_date_);
    swap(address_, other.address_);
    swap(city_, other.city_);
    swap(region_, other.region_);
    swap(postal_code_, other.postal_code_);
    swap(country_, other.country_);
    swap(home_phone_, other.home_phone_);
    swap(extension_, other.extension_);
    swap(photo_, other.photo_);
    swap(notes_, other.notes_);
    swap(reports_to_, other.reports_to_);
}

bool employees::operator==(const employees& rhs) const {
    return employee_id_ == rhs.employee_id_ &&
        last_name_ == rhs.last_name_ &&
        first_name_ == rhs.first_name_ &&
        title_ == rhs.title_ &&
        title_of_courtesy_ == rhs.title_of_courtesy_ &&
        birth_date_ == rhs.birth_date_ &&
        hire_date_ == rhs.hire_date_ &&
        address_ == rhs.address_ &&
        city_ == rhs.city_ &&
        region_ == rhs.region_ &&
        postal_code_ == rhs.postal_code_ &&
        country_ == rhs.country_ &&
        home_phone_ == rhs.home_phone_ &&
        extension_ == rhs.extension_ &&
        photo_ == rhs.photo_ &&
        notes_ == rhs.notes_ &&
        reports_to_ == rhs.reports_to_;
}

employees& employees::operator=(employees other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::test_models::northwind::employee_id& employees::employee_id() const {
    return employee_id_;
}

dogen::test_models::northwind::employee_id& employees::employee_id() {
    return employee_id_;
}

void employees::employee_id(const dogen::test_models::northwind::employee_id& v) {
    employee_id_ = v;
}

void employees::employee_id(const dogen::test_models::northwind::employee_id&& v) {
    employee_id_ = std::move(v);
}

const std::string& employees::last_name() const {
    return last_name_;
}

std::string& employees::last_name() {
    return last_name_;
}

void employees::last_name(const std::string& v) {
    last_name_ = v;
}

void employees::last_name(const std::string&& v) {
    last_name_ = std::move(v);
}

const std::string& employees::first_name() const {
    return first_name_;
}

std::string& employees::first_name() {
    return first_name_;
}

void employees::first_name(const std::string& v) {
    first_name_ = v;
}

void employees::first_name(const std::string&& v) {
    first_name_ = std::move(v);
}

const std::string& employees::title() const {
    return title_;
}

std::string& employees::title() {
    return title_;
}

void employees::title(const std::string& v) {
    title_ = v;
}

void employees::title(const std::string&& v) {
    title_ = std::move(v);
}

const std::string& employees::title_of_courtesy() const {
    return title_of_courtesy_;
}

std::string& employees::title_of_courtesy() {
    return title_of_courtesy_;
}

void employees::title_of_courtesy(const std::string& v) {
    title_of_courtesy_ = v;
}

void employees::title_of_courtesy(const std::string&& v) {
    title_of_courtesy_ = std::move(v);
}

const boost::gregorian::date& employees::birth_date() const {
    return birth_date_;
}

boost::gregorian::date& employees::birth_date() {
    return birth_date_;
}

void employees::birth_date(const boost::gregorian::date& v) {
    birth_date_ = v;
}

void employees::birth_date(const boost::gregorian::date&& v) {
    birth_date_ = std::move(v);
}

const boost::gregorian::date& employees::hire_date() const {
    return hire_date_;
}

boost::gregorian::date& employees::hire_date() {
    return hire_date_;
}

void employees::hire_date(const boost::gregorian::date& v) {
    hire_date_ = v;
}

void employees::hire_date(const boost::gregorian::date&& v) {
    hire_date_ = std::move(v);
}

const std::string& employees::address() const {
    return address_;
}

std::string& employees::address() {
    return address_;
}

void employees::address(const std::string& v) {
    address_ = v;
}

void employees::address(const std::string&& v) {
    address_ = std::move(v);
}

const std::string& employees::city() const {
    return city_;
}

std::string& employees::city() {
    return city_;
}

void employees::city(const std::string& v) {
    city_ = v;
}

void employees::city(const std::string&& v) {
    city_ = std::move(v);
}

const std::string& employees::region() const {
    return region_;
}

std::string& employees::region() {
    return region_;
}

void employees::region(const std::string& v) {
    region_ = v;
}

void employees::region(const std::string&& v) {
    region_ = std::move(v);
}

const std::string& employees::postal_code() const {
    return postal_code_;
}

std::string& employees::postal_code() {
    return postal_code_;
}

void employees::postal_code(const std::string& v) {
    postal_code_ = v;
}

void employees::postal_code(const std::string&& v) {
    postal_code_ = std::move(v);
}

const std::string& employees::country() const {
    return country_;
}

std::string& employees::country() {
    return country_;
}

void employees::country(const std::string& v) {
    country_ = v;
}

void employees::country(const std::string&& v) {
    country_ = std::move(v);
}

const std::string& employees::home_phone() const {
    return home_phone_;
}

std::string& employees::home_phone() {
    return home_phone_;
}

void employees::home_phone(const std::string& v) {
    home_phone_ = v;
}

void employees::home_phone(const std::string&& v) {
    home_phone_ = std::move(v);
}

const std::string& employees::extension() const {
    return extension_;
}

std::string& employees::extension() {
    return extension_;
}

void employees::extension(const std::string& v) {
    extension_ = v;
}

void employees::extension(const std::string&& v) {
    extension_ = std::move(v);
}

const std::string& employees::photo() const {
    return photo_;
}

std::string& employees::photo() {
    return photo_;
}

void employees::photo(const std::string& v) {
    photo_ = v;
}

void employees::photo(const std::string&& v) {
    photo_ = std::move(v);
}

const std::string& employees::notes() const {
    return notes_;
}

std::string& employees::notes() {
    return notes_;
}

void employees::notes(const std::string& v) {
    notes_ = v;
}

void employees::notes(const std::string&& v) {
    notes_ = std::move(v);
}

const dogen::test_models::northwind::employee_id& employees::reports_to() const {
    return reports_to_;
}

dogen::test_models::northwind::employee_id& employees::reports_to() {
    return reports_to_;
}

void employees::reports_to(const dogen::test_models::northwind::employee_id& v) {
    reports_to_ = v;
}

void employees::reports_to(const dogen::test_models::northwind::employee_id&& v) {
    reports_to_ = std::move(v);
}

} } }
