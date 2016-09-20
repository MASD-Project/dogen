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
#include "dogen/options/types/input.hpp"

namespace dogen {
namespace options {

input::input(input&& rhs)
    : path_(std::move(rhs.path_)),
      external_modules_(std::move(rhs.external_modules_)) { }

input::input(
    const boost::filesystem::path& path,
    const std::string& external_modules)
    : path_(path),
      external_modules_(external_modules) { }

void input::swap(input& other) noexcept {
    using std::swap;
    swap(path_, other.path_);
    swap(external_modules_, other.external_modules_);
}

bool input::operator==(const input& rhs) const {
    return path_ == rhs.path_ &&
        external_modules_ == rhs.external_modules_;
}

input& input::operator=(input other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& input::path() const {
    return path_;
}

boost::filesystem::path& input::path() {
    return path_;
}

void input::path(const boost::filesystem::path& v) {
    path_ = v;
}

void input::path(const boost::filesystem::path&& v) {
    path_ = std::move(v);
}

const std::string& input::external_modules() const {
    return external_modules_;
}

std::string& input::external_modules() {
    return external_modules_;
}

void input::external_modules(const std::string& v) {
    external_modules_ = v;
}

void input::external_modules(const std::string&& v) {
    external_modules_ = std::move(v);
}

} }
