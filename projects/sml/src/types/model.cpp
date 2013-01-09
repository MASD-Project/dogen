/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/sml/types/model.hpp"

namespace dogen {
namespace sml {

model::model()
    : is_system_(static_cast<bool>(0)) { }

model::model(
    const std::string& name,
    const std::unordered_map<dogen::sml::qname, dogen::sml::package>& packages,
    const std::unordered_map<dogen::sml::qname, dogen::sml::pod>& pods,
    const std::unordered_map<dogen::sml::qname, dogen::sml::primitive>& primitives,
    const std::unordered_map<dogen::sml::qname, dogen::sml::enumeration>& enumerations,
    const std::unordered_map<dogen::sml::qname, dogen::sml::exception>& exceptions,
    const std::list<std::string>& external_package_path,
    const std::string& schema_name,
    const bool is_system,
    const std::unordered_map<std::string, dogen::sml::reference>& dependencies,
    const std::unordered_set<dogen::sml::qname>& leaves)
    : name_(name),
      packages_(packages),
      pods_(pods),
      primitives_(primitives),
      enumerations_(enumerations),
      exceptions_(exceptions),
      external_package_path_(external_package_path),
      schema_name_(schema_name),
      is_system_(is_system),
      dependencies_(dependencies),
      leaves_(leaves) { }

void model::swap(model& other) noexcept {
    using std::swap;
    swap(name_, other.name_);
    swap(packages_, other.packages_);
    swap(pods_, other.pods_);
    swap(primitives_, other.primitives_);
    swap(enumerations_, other.enumerations_);
    swap(exceptions_, other.exceptions_);
    swap(external_package_path_, other.external_package_path_);
    swap(schema_name_, other.schema_name_);
    swap(is_system_, other.is_system_);
    swap(dependencies_, other.dependencies_);
    swap(leaves_, other.leaves_);
}

bool model::operator==(const model& rhs) const {
    return name_ == rhs.name_ &&
        packages_ == rhs.packages_ &&
        pods_ == rhs.pods_ &&
        primitives_ == rhs.primitives_ &&
        enumerations_ == rhs.enumerations_ &&
        exceptions_ == rhs.exceptions_ &&
        external_package_path_ == rhs.external_package_path_ &&
        schema_name_ == rhs.schema_name_ &&
        is_system_ == rhs.is_system_ &&
        dependencies_ == rhs.dependencies_ &&
        leaves_ == rhs.leaves_;
}

model& model::operator=(model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& model::name() const {
    return name_;
}

std::string& model::name() {
    return name_;
}

void model::name(const std::string& v) {
    name_ = v;
}

void model::name(const std::string&& v) {
    name_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, dogen::sml::package>& model::packages() const {
    return packages_;
}

std::unordered_map<dogen::sml::qname, dogen::sml::package>& model::packages() {
    return packages_;
}

void model::packages(const std::unordered_map<dogen::sml::qname, dogen::sml::package>& v) {
    packages_ = v;
}

void model::packages(const std::unordered_map<dogen::sml::qname, dogen::sml::package>&& v) {
    packages_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, dogen::sml::pod>& model::pods() const {
    return pods_;
}

std::unordered_map<dogen::sml::qname, dogen::sml::pod>& model::pods() {
    return pods_;
}

void model::pods(const std::unordered_map<dogen::sml::qname, dogen::sml::pod>& v) {
    pods_ = v;
}

void model::pods(const std::unordered_map<dogen::sml::qname, dogen::sml::pod>&& v) {
    pods_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, dogen::sml::primitive>& model::primitives() const {
    return primitives_;
}

std::unordered_map<dogen::sml::qname, dogen::sml::primitive>& model::primitives() {
    return primitives_;
}

void model::primitives(const std::unordered_map<dogen::sml::qname, dogen::sml::primitive>& v) {
    primitives_ = v;
}

void model::primitives(const std::unordered_map<dogen::sml::qname, dogen::sml::primitive>&& v) {
    primitives_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, dogen::sml::enumeration>& model::enumerations() const {
    return enumerations_;
}

std::unordered_map<dogen::sml::qname, dogen::sml::enumeration>& model::enumerations() {
    return enumerations_;
}

void model::enumerations(const std::unordered_map<dogen::sml::qname, dogen::sml::enumeration>& v) {
    enumerations_ = v;
}

void model::enumerations(const std::unordered_map<dogen::sml::qname, dogen::sml::enumeration>&& v) {
    enumerations_ = std::move(v);
}

const std::unordered_map<dogen::sml::qname, dogen::sml::exception>& model::exceptions() const {
    return exceptions_;
}

std::unordered_map<dogen::sml::qname, dogen::sml::exception>& model::exceptions() {
    return exceptions_;
}

void model::exceptions(const std::unordered_map<dogen::sml::qname, dogen::sml::exception>& v) {
    exceptions_ = v;
}

void model::exceptions(const std::unordered_map<dogen::sml::qname, dogen::sml::exception>&& v) {
    exceptions_ = std::move(v);
}

const std::list<std::string>& model::external_package_path() const {
    return external_package_path_;
}

std::list<std::string>& model::external_package_path() {
    return external_package_path_;
}

void model::external_package_path(const std::list<std::string>& v) {
    external_package_path_ = v;
}

void model::external_package_path(const std::list<std::string>&& v) {
    external_package_path_ = std::move(v);
}

const std::string& model::schema_name() const {
    return schema_name_;
}

std::string& model::schema_name() {
    return schema_name_;
}

void model::schema_name(const std::string& v) {
    schema_name_ = v;
}

void model::schema_name(const std::string&& v) {
    schema_name_ = std::move(v);
}

bool model::is_system() const {
    return is_system_;
}

void model::is_system(const bool v) {
    is_system_ = v;
}

const std::unordered_map<std::string, dogen::sml::reference>& model::dependencies() const {
    return dependencies_;
}

std::unordered_map<std::string, dogen::sml::reference>& model::dependencies() {
    return dependencies_;
}

void model::dependencies(const std::unordered_map<std::string, dogen::sml::reference>& v) {
    dependencies_ = v;
}

void model::dependencies(const std::unordered_map<std::string, dogen::sml::reference>&& v) {
    dependencies_ = std::move(v);
}

const std::unordered_set<dogen::sml::qname>& model::leaves() const {
    return leaves_;
}

std::unordered_set<dogen::sml::qname>& model::leaves() {
    return leaves_;
}

void model::leaves(const std::unordered_set<dogen::sml::qname>& v) {
    leaves_ = v;
}

void model::leaves(const std::unordered_set<dogen::sml::qname>&& v) {
    leaves_ = std::move(v);
}

} }