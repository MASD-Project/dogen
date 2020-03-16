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
#include "dogen.logical/types/entities/variability/default_value_override.hpp"

namespace dogen::logical::entities::variability {

default_value_override::default_value_override(
    const std::string& key_ends_with,
    const std::string& default_value)
    : key_ends_with_(key_ends_with),
      default_value_(default_value) { }

void default_value_override::swap(default_value_override& other) noexcept {
    using std::swap;
    swap(key_ends_with_, other.key_ends_with_);
    swap(default_value_, other.default_value_);
}

bool default_value_override::operator==(const default_value_override& rhs) const {
    return key_ends_with_ == rhs.key_ends_with_ &&
        default_value_ == rhs.default_value_;
}

default_value_override& default_value_override::operator=(default_value_override other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& default_value_override::key_ends_with() const {
    return key_ends_with_;
}

std::string& default_value_override::key_ends_with() {
    return key_ends_with_;
}

void default_value_override::key_ends_with(const std::string& v) {
    key_ends_with_ = v;
}

void default_value_override::key_ends_with(const std::string&& v) {
    key_ends_with_ = std::move(v);
}

const std::string& default_value_override::default_value() const {
    return default_value_;
}

std::string& default_value_override::default_value() {
    return default_value_;
}

void default_value_override::default_value(const std::string& v) {
    default_value_ = v;
}

void default_value_override::default_value(const std::string&& v) {
    default_value_ = std::move(v);
}

}
