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
#include "dogen/test_models/cpp_model/types/int_primitive.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

int_primitive::int_primitive(const int value)
    : value_(value) { }

int int_primitive::value() const {
    return value_;
}

void int_primitive::value(const int v) {
    value_ = v;
}

bool int_primitive::operator==(const int_primitive& rhs) const {
    return value_ == rhs.value_;
}

void int_primitive::swap(int_primitive& other) noexcept {
    using std::swap;
    swap(value_, other.value_);
}

int_primitive& int_primitive::operator=(int_primitive other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} } }
