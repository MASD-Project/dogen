/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/trivial_association/types/class_a.hpp"

namespace dogen {
namespace trivial_association {

class_a::class_a()
    : prop_0_(static_cast<int>(0)) { }

class_a::class_a(const int prop_0)
    : prop_0_(prop_0) { }

void class_a::swap(class_a& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
}

bool class_a::operator==(const class_a& rhs) const {
    return prop_0_ == rhs.prop_0_;
}

class_a& class_a::operator=(class_a other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }