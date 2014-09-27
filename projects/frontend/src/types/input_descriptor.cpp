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
#include "dogen/frontend/types/input_descriptor.hpp"

namespace dogen {
namespace frontend {

input_descriptor::input_descriptor()
    : is_target_(static_cast<bool>(0)) { }

input_descriptor::input_descriptor(input_descriptor&& rhs)
    : path_(std::move(rhs.path_)),
      external_module_path_(std::move(rhs.external_module_path_)),
      is_target_(std::move(rhs.is_target_)) { }

input_descriptor::input_descriptor(
    const boost::filesystem::path& path,
    const std::string& external_module_path,
    const bool is_target)
    : path_(path),
      external_module_path_(external_module_path),
      is_target_(is_target) { }

void input_descriptor::swap(input_descriptor& other) noexcept {
    using std::swap;
    swap(path_, other.path_);
    swap(external_module_path_, other.external_module_path_);
    swap(is_target_, other.is_target_);
}

bool input_descriptor::operator==(const input_descriptor& rhs) const {
    return path_ == rhs.path_ &&
        external_module_path_ == rhs.external_module_path_ &&
        is_target_ == rhs.is_target_;
}

input_descriptor& input_descriptor::operator=(input_descriptor other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& input_descriptor::path() const {
    return path_;
}

boost::filesystem::path& input_descriptor::path() {
    return path_;
}

void input_descriptor::path(const boost::filesystem::path& v) {
    path_ = v;
}

void input_descriptor::path(const boost::filesystem::path&& v) {
    path_ = std::move(v);
}

const std::string& input_descriptor::external_module_path() const {
    return external_module_path_;
}

std::string& input_descriptor::external_module_path() {
    return external_module_path_;
}

void input_descriptor::external_module_path(const std::string& v) {
    external_module_path_ = v;
}

void input_descriptor::external_module_path(const std::string&& v) {
    external_module_path_ = std::move(v);
}

bool input_descriptor::is_target() const {
    return is_target_;
}

void input_descriptor::is_target(const bool v) {
    is_target_ = v;
}

} }