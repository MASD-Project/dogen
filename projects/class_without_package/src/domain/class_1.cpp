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
#include "dogen/class_without_package/domain/class_1.hpp"
#include "dogen/utility/io/jsonify_io.hpp"

namespace dogen {
namespace class_without_package {

class_1::class_1()
    : an_attribute_(static_cast<int>(0)) { }

class_1::class_1(
    int an_attribute,
    dogen::class_without_package::versioned_key versioned_key)
    : an_attribute_(an_attribute),
      versioned_key_(versioned_key) { }

void class_1::swap(class_1& other) {
    std::swap(an_attribute_, other.an_attribute_);
    std::swap(versioned_key_, other.versioned_key_);
}

bool class_1::operator==(const class_1& rhs) const {
    return an_attribute_ == rhs.an_attribute_ &&
        versioned_key_ == rhs.versioned_key_;
}

class_1& class_1::operator=(class_1 other) {
    std::swap(*this, other);
    return *this;
}

} }