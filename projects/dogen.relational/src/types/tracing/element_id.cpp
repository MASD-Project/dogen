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
#include "dogen.relational/types/tracing/element_id.hpp"

namespace dogen::relational::tracing {

element_id::element_id(const std::string& value)
    : value_(value) { }

const std::string& element_id::value() const {
    return value_;
}

std::string& element_id::value() {
    return value_;
}

void element_id::value(const std::string& v) {
    value_ = v;
}

void element_id::value(const std::string&& v) {
    value_ = std::move(v);
}

bool element_id::operator==(const element_id& rhs) const {
    return value_ == rhs.value_;
}

void element_id::swap(element_id& other) noexcept {
    using std::swap;
    swap(value_, other.value_);
}

element_id& element_id::operator=(element_id other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

}
