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
#include "dogen.physical/types/entities/label.hpp"

namespace dogen::physical::entities {

label::label(
    const std::string& key,
    const std::string& value)
    : key_(key),
      value_(value) { }

void label::swap(label& other) noexcept {
    using std::swap;
    swap(key_, other.key_);
    swap(value_, other.value_);
}

bool label::operator==(const label& rhs) const {
    return key_ == rhs.key_ &&
        value_ == rhs.value_;
}

label& label::operator=(label other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& label::key() const {
    return key_;
}

std::string& label::key() {
    return key_;
}

void label::key(const std::string& v) {
    key_ = v;
}

void label::key(const std::string&& v) {
    key_ = std::move(v);
}

const std::string& label::value() const {
    return value_;
}

std::string& label::value() {
    return value_;
}

void label::value(const std::string& v) {
    value_ = v;
}

void label::value(const std::string&& v) {
    value_ = std::move(v);
}

}
