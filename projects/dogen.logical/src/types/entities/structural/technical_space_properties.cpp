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
#include "dogen.logical/types/entities/structural/technical_space_properties.hpp"

namespace dogen::logical::entities::structural {

technical_space_properties::technical_space_properties()
    : requires_manual_default_constructor_(static_cast<bool>(0)),
      requires_manual_move_constructor_(static_cast<bool>(0)),
      requires_stream_manipulators_(static_cast<bool>(0)),
      is_floating_point_(static_cast<bool>(0)),
      requires_static_reference_equals_(static_cast<bool>(0)) { }

technical_space_properties::technical_space_properties(
    const bool requires_manual_default_constructor,
    const bool requires_manual_move_constructor,
    const bool requires_stream_manipulators,
    const bool is_floating_point,
    const bool requires_static_reference_equals)
    : requires_manual_default_constructor_(requires_manual_default_constructor),
      requires_manual_move_constructor_(requires_manual_move_constructor),
      requires_stream_manipulators_(requires_stream_manipulators),
      is_floating_point_(is_floating_point),
      requires_static_reference_equals_(requires_static_reference_equals) { }

void technical_space_properties::swap(technical_space_properties& other) noexcept {
    using std::swap;
    swap(requires_manual_default_constructor_, other.requires_manual_default_constructor_);
    swap(requires_manual_move_constructor_, other.requires_manual_move_constructor_);
    swap(requires_stream_manipulators_, other.requires_stream_manipulators_);
    swap(is_floating_point_, other.is_floating_point_);
    swap(requires_static_reference_equals_, other.requires_static_reference_equals_);
}

bool technical_space_properties::operator==(const technical_space_properties& rhs) const {
    return requires_manual_default_constructor_ == rhs.requires_manual_default_constructor_ &&
        requires_manual_move_constructor_ == rhs.requires_manual_move_constructor_ &&
        requires_stream_manipulators_ == rhs.requires_stream_manipulators_ &&
        is_floating_point_ == rhs.is_floating_point_ &&
        requires_static_reference_equals_ == rhs.requires_static_reference_equals_;
}

technical_space_properties& technical_space_properties::operator=(technical_space_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool technical_space_properties::requires_manual_default_constructor() const {
    return requires_manual_default_constructor_;
}

void technical_space_properties::requires_manual_default_constructor(const bool v) {
    requires_manual_default_constructor_ = v;
}

bool technical_space_properties::requires_manual_move_constructor() const {
    return requires_manual_move_constructor_;
}

void technical_space_properties::requires_manual_move_constructor(const bool v) {
    requires_manual_move_constructor_ = v;
}

bool technical_space_properties::requires_stream_manipulators() const {
    return requires_stream_manipulators_;
}

void technical_space_properties::requires_stream_manipulators(const bool v) {
    requires_stream_manipulators_ = v;
}

bool technical_space_properties::is_floating_point() const {
    return is_floating_point_;
}

void technical_space_properties::is_floating_point(const bool v) {
    is_floating_point_ = v;
}

bool technical_space_properties::requires_static_reference_equals() const {
    return requires_static_reference_equals_;
}

void technical_space_properties::requires_static_reference_equals(const bool v) {
    requires_static_reference_equals_ = v;
}

}
