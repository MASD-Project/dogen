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
#include "dogen/test_models/boost_model/types/date_primitive.hpp"

namespace dogen {
namespace test_models {
namespace boost_model {

date_primitive::date_primitive(const boost::gregorian::date& value)
    : value_(value) { }

const boost::gregorian::date& date_primitive::value() const {
    return value_;
}

boost::gregorian::date& date_primitive::value() {
    return value_;
}

void date_primitive::value(const boost::gregorian::date& v) {
    value_ = v;
}

void date_primitive::value(const boost::gregorian::date&& v) {
    value_ = std::move(v);
}

bool date_primitive::operator==(const date_primitive& rhs) const {
    return value_ == rhs.value_;
}

void date_primitive::swap(date_primitive& other) noexcept {
    using std::swap;
    swap(value_, other.value_);
}

date_primitive& date_primitive::operator=(date_primitive other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} } }
