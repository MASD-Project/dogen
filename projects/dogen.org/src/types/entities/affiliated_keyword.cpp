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
#include "dogen.org/types/entities/affiliated_keyword.hpp"

namespace dogen::org::entities {

affiliated_keyword::affiliated_keyword(
    const std::string& key,
    const std::string& value)
    : key_(key),
      value_(value) { }

void affiliated_keyword::swap(affiliated_keyword& other) noexcept {
    using std::swap;
    swap(key_, other.key_);
    swap(value_, other.value_);
}

bool affiliated_keyword::operator==(const affiliated_keyword& rhs) const {
    return key_ == rhs.key_ &&
        value_ == rhs.value_;
}

affiliated_keyword& affiliated_keyword::operator=(affiliated_keyword other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& affiliated_keyword::key() const {
    return key_;
}

std::string& affiliated_keyword::key() {
    return key_;
}

void affiliated_keyword::key(const std::string& v) {
    key_ = v;
}

void affiliated_keyword::key(const std::string&& v) {
    key_ = std::move(v);
}

const std::string& affiliated_keyword::value() const {
    return value_;
}

std::string& affiliated_keyword::value() {
    return value_;
}

void affiliated_keyword::value(const std::string& v) {
    value_ = v;
}

void affiliated_keyword::value(const std::string&& v) {
    value_ = std::move(v);
}

}
