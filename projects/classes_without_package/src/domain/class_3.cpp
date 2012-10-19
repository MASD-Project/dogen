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
#include "dogen/classes_without_package/domain/class_3.hpp"

namespace dogen {
namespace classes_without_package {

class_3::class_3(const dogen::classes_without_package::versioned_key& versioned_key)
    : versioned_key_(versioned_key) { }

void class_3::swap(class_3& other) noexcept {
    using std::swap;
    swap(versioned_key_, other.versioned_key_);
}

bool class_3::operator==(const class_3& rhs) const {
    return versioned_key_ == rhs.versioned_key_;
}

class_3& class_3::operator=(class_3 other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }