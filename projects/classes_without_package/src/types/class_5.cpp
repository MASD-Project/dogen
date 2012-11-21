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
#include "dogen/classes_without_package/types/class_5.hpp"

namespace dogen {
namespace classes_without_package {

class_5::class_5()
    : prop_0_(static_cast<int>(0)) { }

class_5::class_5(const int prop_0)
    : prop_0_(prop_0) { }

void class_5::swap(class_5& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
}

bool class_5::operator==(const class_5& rhs) const {
    return prop_0_ == rhs.prop_0_;
}

class_5& class_5::operator=(class_5 other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }