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
#include "dogen/test_models/std_model/types/string_primitive.hpp"

namespace dogen {
namespace test_models {
namespace std_model {

string_primitive::string_primitive(const std::string& value)
    : value_(value) { }

const std::string& string_primitive::value() const {
    return value_;
}

std::string& string_primitive::value() {
    return value_;
}

void string_primitive::value(const std::string& v) {
    value_ = v;
}

void string_primitive::value(const std::string&& v) {
    value_ = std::move(v);
}

bool string_primitive::operator==(const string_primitive& rhs) const {
    return value_ == rhs.value_;
}

void string_primitive::swap(string_primitive& other) noexcept {
    using std::swap;
    swap(value_, other.value_);
}

string_primitive& string_primitive::operator=(string_primitive other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} } }
