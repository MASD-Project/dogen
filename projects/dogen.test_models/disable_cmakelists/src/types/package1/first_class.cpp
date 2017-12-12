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
#include "dogen/test_models/disable_cmakelists/types/package1/first_class.hpp"

namespace dogen {
namespace test_models {
namespace disable_cmakelists {
namespace package1 {

first_class::first_class()
    : public_attribute_(static_cast<int>(0)),
      private_attribute_(static_cast<int>(0)) { }

first_class::first_class(
    const int public_attribute,
    const int private_attribute)
    : public_attribute_(public_attribute),
      private_attribute_(private_attribute) { }

void first_class::swap(first_class& other) noexcept {
    using std::swap;
    swap(public_attribute_, other.public_attribute_);
    swap(private_attribute_, other.private_attribute_);
}

bool first_class::operator==(const first_class& rhs) const {
    return public_attribute_ == rhs.public_attribute_ &&
        private_attribute_ == rhs.private_attribute_;
}

first_class& first_class::operator=(first_class other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

int first_class::public_attribute() const {
    return public_attribute_;
}

void first_class::public_attribute(const int v) {
    public_attribute_ = v;
}

int first_class::private_attribute() const {
    return private_attribute_;
}

void first_class::private_attribute(const int v) {
    private_attribute_ = v;
}

} } } }
