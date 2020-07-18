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
#include "dogen.identification/types/entities/sha1_hash.hpp"

namespace dogen::identification::entities {

sha1_hash::sha1_hash(const std::string& value)
    : value_(value) { }

const std::string& sha1_hash::value() const {
    return value_;
}

std::string& sha1_hash::value() {
    return value_;
}

void sha1_hash::value(const std::string& v) {
    value_ = v;
}

void sha1_hash::value(const std::string&& v) {
    value_ = std::move(v);
}

bool sha1_hash::operator==(const sha1_hash& rhs) const {
    return value_ == rhs.value_;
}

void sha1_hash::swap(sha1_hash& other) noexcept {
    using std::swap;
    swap(value_, other.value_);
}

sha1_hash& sha1_hash::operator=(sha1_hash other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

}
