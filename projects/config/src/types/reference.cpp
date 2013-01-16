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
#include "dogen/config/types/reference.hpp"

namespace dogen {
namespace config {

reference::reference(reference&& rhs)
    : path_(std::move(rhs.path_)),
      external_package_path_(std::move(rhs.external_package_path_)) { }

reference::reference(
    const boost::filesystem::path& path,
    const std::string& external_package_path)
    : path_(path),
      external_package_path_(external_package_path) { }

void reference::swap(reference& other) noexcept {
    using std::swap;
    swap(path_, other.path_);
    swap(external_package_path_, other.external_package_path_);
}

bool reference::operator==(const reference& rhs) const {
    return path_ == rhs.path_ &&
        external_package_path_ == rhs.external_package_path_;
}

reference& reference::operator=(reference other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& reference::path() const {
    return path_;
}

boost::filesystem::path& reference::path() {
    return path_;
}

void reference::path(const boost::filesystem::path& v) {
    path_ = v;
}

void reference::path(const boost::filesystem::path&& v) {
    path_ = std::move(v);
}

const std::string& reference::external_package_path() const {
    return external_package_path_;
}

std::string& reference::external_package_path() {
    return external_package_path_;
}

void reference::external_package_path(const std::string& v) {
    external_package_path_ = v;
}

void reference::external_package_path(const std::string&& v) {
    external_package_path_ = std::move(v);
}

} }