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
#include "dogen/test_models/class_without_package/types/class_1.hpp"

namespace dogen {
namespace test_models {
namespace class_without_package {

class_1::class_1()
    : an_attribute_(static_cast<int>(0)) { }

class_1::class_1(const int an_attribute)
    : an_attribute_(an_attribute) { }

void class_1::swap(class_1& other) noexcept {
    using std::swap;
    swap(an_attribute_, other.an_attribute_);
}

bool class_1::operator==(const class_1& rhs) const {
    return an_attribute_ == rhs.an_attribute_;
}

class_1& class_1::operator=(class_1 other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

int class_1::an_attribute() const {
    return an_attribute_;
}

void class_1::an_attribute(const int v) {
    an_attribute_ = v;
}

} } }
