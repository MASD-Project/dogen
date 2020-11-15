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
#include "dogen.logical/types/entities/aspect_properties.hpp"

namespace dogen::logical::entities {

aspect_properties::aspect_properties()
    : is_floating_point_(static_cast<bool>(0)),
      requires_static_reference_equals_(static_cast<bool>(0)) { }

aspect_properties::aspect_properties(
    const bool is_floating_point,
    const bool requires_static_reference_equals)
    : is_floating_point_(is_floating_point),
      requires_static_reference_equals_(requires_static_reference_equals) { }

void aspect_properties::swap(aspect_properties& other) noexcept {
    using std::swap;
    swap(is_floating_point_, other.is_floating_point_);
    swap(requires_static_reference_equals_, other.requires_static_reference_equals_);
}

bool aspect_properties::operator==(const aspect_properties& rhs) const {
    return is_floating_point_ == rhs.is_floating_point_ &&
        requires_static_reference_equals_ == rhs.requires_static_reference_equals_;
}

aspect_properties& aspect_properties::operator=(aspect_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool aspect_properties::is_floating_point() const {
    return is_floating_point_;
}

void aspect_properties::is_floating_point(const bool v) {
    is_floating_point_ = v;
}

bool aspect_properties::requires_static_reference_equals() const {
    return requires_static_reference_equals_;
}

void aspect_properties::requires_static_reference_equals(const bool v) {
    requires_static_reference_equals_ = v;
}

}
