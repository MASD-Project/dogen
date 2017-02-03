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
#include "dogen/test_models/boost_model/types/time_duration_primitive.hpp"

namespace dogen {
namespace test_models {
namespace boost_model {

time_duration_primitive::time_duration_primitive(const boost::posix_time::time_duration& value)
    : value_(value) { }

const boost::posix_time::time_duration& time_duration_primitive::value() const {
    return value_;
}

boost::posix_time::time_duration& time_duration_primitive::value() {
    return value_;
}

void time_duration_primitive::value(const boost::posix_time::time_duration& v) {
    value_ = v;
}

void time_duration_primitive::value(const boost::posix_time::time_duration&& v) {
    value_ = std::move(v);
}

bool time_duration_primitive::operator==(const time_duration_primitive& rhs) const {
    return value_ == rhs.value_;
}

void time_duration_primitive::swap(time_duration_primitive& other) noexcept {
    using std::swap;
    swap(value_, other.value_);
}

time_duration_primitive& time_duration_primitive::operator=(time_duration_primitive other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} } }
