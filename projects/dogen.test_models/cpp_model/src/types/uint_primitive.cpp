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
#include "dogen/test_models/cpp_model/types/uint_primitive.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

uint_primitive::uint_primitive(const unsigned int value)
    : value_(value) { }

unsigned int uint_primitive::value() const {
    return value_;
}

void uint_primitive::value(const unsigned int v) {
    value_ = v;
}

bool uint_primitive::operator==(const uint_primitive& rhs) const {
    return value_ == rhs.value_;
}

void uint_primitive::swap(uint_primitive& other) noexcept {
    using std::swap;
    swap(value_, other.value_);
}

uint_primitive& uint_primitive::operator=(uint_primitive other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} } }
