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
      requires_stream_manipulators_(static_cast<bool>(0)) { }

technical_space_properties::technical_space_properties(
    const bool requires_manual_default_constructor,
    const bool requires_manual_move_constructor,
    const bool requires_stream_manipulators)
    : requires_manual_default_constructor_(requires_manual_default_constructor),
      requires_manual_move_constructor_(requires_manual_move_constructor),
      requires_stream_manipulators_(requires_stream_manipulators) { }

void technical_space_properties::swap(technical_space_properties& other) noexcept {
    using std::swap;
    swap(requires_manual_default_constructor_, other.requires_manual_default_constructor_);
    swap(requires_manual_move_constructor_, other.requires_manual_move_constructor_);
    swap(requires_stream_manipulators_, other.requires_stream_manipulators_);
}

bool technical_space_properties::operator==(const technical_space_properties& rhs) const {
    return requires_manual_default_constructor_ == rhs.requires_manual_default_constructor_ &&
        requires_manual_move_constructor_ == rhs.requires_manual_move_constructor_ &&
        requires_stream_manipulators_ == rhs.requires_stream_manipulators_;
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

}
