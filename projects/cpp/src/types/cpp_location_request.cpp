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
#include "dogen/cpp/types/cpp_location_request.hpp"

namespace dogen {
namespace cpp {

cpp_location_request::cpp_location_request()
    : facet_type_(static_cast<dogen::config::cpp_facet_types>(0)),
      file_type_(static_cast<dogen::cpp::file_types>(0)),
      aspect_type_(static_cast<dogen::cpp::aspect_types>(0)) { }

cpp_location_request::cpp_location_request(
    const dogen::config::cpp_facet_types& facet_type,
    const dogen::cpp::file_types& file_type,
    const dogen::cpp::aspect_types& aspect_type,
    const std::string& model_name,
    const std::list<std::string>& external_package_path,
    const std::list<std::string>& package_path,
    const std::string& file_name)
    : facet_type_(facet_type),
      file_type_(file_type),
      aspect_type_(aspect_type),
      model_name_(model_name),
      external_package_path_(external_package_path),
      package_path_(package_path),
      file_name_(file_name) { }

void cpp_location_request::swap(cpp_location_request& other) noexcept {
    using std::swap;
    swap(facet_type_, other.facet_type_);
    swap(file_type_, other.file_type_);
    swap(aspect_type_, other.aspect_type_);
    swap(model_name_, other.model_name_);
    swap(external_package_path_, other.external_package_path_);
    swap(package_path_, other.package_path_);
    swap(file_name_, other.file_name_);
}

bool cpp_location_request::operator==(const cpp_location_request& rhs) const {
    return facet_type_ == rhs.facet_type_ &&
        file_type_ == rhs.file_type_ &&
        aspect_type_ == rhs.aspect_type_ &&
        model_name_ == rhs.model_name_ &&
        external_package_path_ == rhs.external_package_path_ &&
        package_path_ == rhs.package_path_ &&
        file_name_ == rhs.file_name_;
}

cpp_location_request& cpp_location_request::operator=(cpp_location_request other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::config::cpp_facet_types cpp_location_request::facet_type() const {
    return facet_type_;
}

void cpp_location_request::facet_type(const dogen::config::cpp_facet_types& v) {
    facet_type_ = v;
}

dogen::cpp::file_types cpp_location_request::file_type() const {
    return file_type_;
}

void cpp_location_request::file_type(const dogen::cpp::file_types& v) {
    file_type_ = v;
}

dogen::cpp::aspect_types cpp_location_request::aspect_type() const {
    return aspect_type_;
}

void cpp_location_request::aspect_type(const dogen::cpp::aspect_types& v) {
    aspect_type_ = v;
}

const std::string& cpp_location_request::model_name() const {
    return model_name_;
}

std::string& cpp_location_request::model_name() {
    return model_name_;
}

void cpp_location_request::model_name(const std::string& v) {
    model_name_ = v;
}

void cpp_location_request::model_name(const std::string&& v) {
    model_name_ = std::move(v);
}

const std::list<std::string>& cpp_location_request::external_package_path() const {
    return external_package_path_;
}

std::list<std::string>& cpp_location_request::external_package_path() {
    return external_package_path_;
}

void cpp_location_request::external_package_path(const std::list<std::string>& v) {
    external_package_path_ = v;
}

void cpp_location_request::external_package_path(const std::list<std::string>&& v) {
    external_package_path_ = std::move(v);
}

const std::list<std::string>& cpp_location_request::package_path() const {
    return package_path_;
}

std::list<std::string>& cpp_location_request::package_path() {
    return package_path_;
}

void cpp_location_request::package_path(const std::list<std::string>& v) {
    package_path_ = v;
}

void cpp_location_request::package_path(const std::list<std::string>&& v) {
    package_path_ = std::move(v);
}

const std::string& cpp_location_request::file_name() const {
    return file_name_;
}

std::string& cpp_location_request::file_name() {
    return file_name_;
}

void cpp_location_request::file_name(const std::string& v) {
    file_name_ = v;
}

void cpp_location_request::file_name(const std::string&& v) {
    file_name_ = std::move(v);
}

} }