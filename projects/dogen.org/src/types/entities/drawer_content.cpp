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
#include "dogen.org/types/entities/drawer_content.hpp"

namespace dogen::org::entities {

drawer_content::drawer_content(
    const std::string& key,
    const std::string& value)
    : key_(key),
      value_(value) { }

void drawer_content::swap(drawer_content& other) noexcept {
    using std::swap;
    swap(key_, other.key_);
    swap(value_, other.value_);
}

bool drawer_content::operator==(const drawer_content& rhs) const {
    return key_ == rhs.key_ &&
        value_ == rhs.value_;
}

drawer_content& drawer_content::operator=(drawer_content other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& drawer_content::key() const {
    return key_;
}

std::string& drawer_content::key() {
    return key_;
}

void drawer_content::key(const std::string& v) {
    key_ = v;
}

void drawer_content::key(const std::string&& v) {
    key_ = std::move(v);
}

const std::string& drawer_content::value() const {
    return value_;
}

std::string& drawer_content::value() {
    return value_;
}

void drawer_content::value(const std::string& v) {
    value_ = v;
}

void drawer_content::value(const std::string&& v) {
    value_ = std::move(v);
}

}
