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
#include "dogen/sml/types/reference.hpp"

namespace dogen {
namespace sml {

reference::reference()
    : is_system_(static_cast<bool>(0)) { }

reference::reference(
    const std::string& model_name,
    const std::list<std::string>& external_package_path,
    const bool is_system)
    : model_name_(model_name),
      external_package_path_(external_package_path),
      is_system_(is_system) { }

void reference::swap(reference& other) noexcept {
    using std::swap;
    swap(model_name_, other.model_name_);
    swap(external_package_path_, other.external_package_path_);
    swap(is_system_, other.is_system_);
}

bool reference::operator==(const reference& rhs) const {
    return model_name_ == rhs.model_name_ &&
        external_package_path_ == rhs.external_package_path_ &&
        is_system_ == rhs.is_system_;
}

reference& reference::operator=(reference other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& reference::model_name() const {
    return model_name_;
}

std::string& reference::model_name() {
    return model_name_;
}

void reference::model_name(const std::string& v) {
    model_name_ = v;
}

void reference::model_name(const std::string&& v) {
    model_name_ = std::move(v);
}

const std::list<std::string>& reference::external_package_path() const {
    return external_package_path_;
}

std::list<std::string>& reference::external_package_path() {
    return external_package_path_;
}

void reference::external_package_path(const std::list<std::string>& v) {
    external_package_path_ = v;
}

void reference::external_package_path(const std::list<std::string>&& v) {
    external_package_path_ = std::move(v);
}

bool reference::is_system() const {
    return is_system_;
}

void reference::is_system(const bool v) {
    is_system_ = v;
}

} }