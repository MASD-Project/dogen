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
#include "dogen/std_model/domain/class_a.hpp"

namespace dogen {
namespace std_model {

class_a::class_a(
    const std::string& prop0,
    const std::string& prop1)
    : prop0_(prop0),
      prop1_(prop1) { }

void class_a::swap(class_a& other) noexcept {
    using std::swap;
    swap(prop0_, other.prop0_);
    swap(prop1_, other.prop1_);
}

bool class_a::operator==(const class_a& rhs) const {
    return prop0_ == rhs.prop0_ &&
        prop1_ == rhs.prop1_;
}

class_a& class_a::operator=(class_a other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }