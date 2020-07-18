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
#include "dogen.identification/types/entities/tagged_value.hpp"

namespace dogen::identification::entities {

tagged_value::tagged_value(
    const std::string& tag,
    const std::string& value)
    : tag_(tag),
      value_(value) { }

void tagged_value::swap(tagged_value& other) noexcept {
    using std::swap;
    swap(tag_, other.tag_);
    swap(value_, other.value_);
}

bool tagged_value::operator==(const tagged_value& rhs) const {
    return tag_ == rhs.tag_ &&
        value_ == rhs.value_;
}

tagged_value& tagged_value::operator=(tagged_value other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& tagged_value::tag() const {
    return tag_;
}

std::string& tagged_value::tag() {
    return tag_;
}

void tagged_value::tag(const std::string& v) {
    tag_ = v;
}

void tagged_value::tag(const std::string&& v) {
    tag_ = std::move(v);
}

const std::string& tagged_value::value() const {
    return value_;
}

std::string& tagged_value::value() {
    return value_;
}

void tagged_value::value(const std::string& v) {
    value_ = v;
}

void tagged_value::value(const std::string&& v) {
    value_ = std::move(v);
}

}
