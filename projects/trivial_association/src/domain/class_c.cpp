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
#include "dogen/trivial_association/domain/class_c.hpp"

namespace dogen {
namespace trivial_association {

class_c::class_c(const dogen::trivial_association::versioned_key& versioned_key)
    : versioned_key_(versioned_key) { }

void class_c::swap(class_c& other) noexcept {
    using std::swap;
    swap(versioned_key_, other.versioned_key_);
}

bool class_c::operator==(const class_c& rhs) const {
    return versioned_key_ == rhs.versioned_key_;
}

class_c& class_c::operator=(class_c other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }