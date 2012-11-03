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
#include <ostream>
#include "dogen/trivial_inheritance/domain/pkg4/child.hpp"
#include "dogen/trivial_inheritance/io/parent_outside_io.hpp"

namespace dogen {
namespace trivial_inheritance {
namespace pkg4 {

child::child(const dogen::trivial_inheritance::versioned_key& versioned_key)
    : dogen::trivial_inheritance::parent_outside(versioned_key) { }

void child::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"child\"" << ", "
      << "\"__parent_0__\": ";
    parent_outside::to_stream(s);
    s << " }";
}

void child::swap(child& other) noexcept {
    parent_outside::swap(other);

}

bool child::equals(const dogen::trivial_inheritance::parent_outside& other) const {
    const child* const p(dynamic_cast<const child* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool child::operator==(const child& rhs) const {
    return parent_outside::compare(rhs);
}

child& child::operator=(child other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} } }