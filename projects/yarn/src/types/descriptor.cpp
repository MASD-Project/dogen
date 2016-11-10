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
#include "dogen/yarn/types/descriptor.hpp"

namespace dogen {
namespace yarn {

descriptor::descriptor()
    : is_target_(static_cast<bool>(0)) { }

descriptor::descriptor(descriptor&& rhs)
    : path_(std::move(rhs.path_)),
      extension_(std::move(rhs.extension_)),
      is_target_(std::move(rhs.is_target_)) { }

descriptor::descriptor(
    const boost::filesystem::path& path,
    const std::string& extension,
    const bool is_target)
    : path_(path),
      extension_(extension),
      is_target_(is_target) { }

void descriptor::swap(descriptor& other) noexcept {
    using std::swap;
    swap(path_, other.path_);
    swap(extension_, other.extension_);
    swap(is_target_, other.is_target_);
}

bool descriptor::operator==(const descriptor& rhs) const {
    return path_ == rhs.path_ &&
        extension_ == rhs.extension_ &&
        is_target_ == rhs.is_target_;
}

descriptor& descriptor::operator=(descriptor other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& descriptor::path() const {
    return path_;
}

boost::filesystem::path& descriptor::path() {
    return path_;
}

void descriptor::path(const boost::filesystem::path& v) {
    path_ = v;
}

void descriptor::path(const boost::filesystem::path&& v) {
    path_ = std::move(v);
}

const std::string& descriptor::extension() const {
    return extension_;
}

std::string& descriptor::extension() {
    return extension_;
}

void descriptor::extension(const std::string& v) {
    extension_ = v;
}

void descriptor::extension(const std::string&& v) {
    extension_ = std::move(v);
}

bool descriptor::is_target() const {
    return is_target_;
}

void descriptor::is_target(const bool v) {
    is_target_ = v;
}

} }
