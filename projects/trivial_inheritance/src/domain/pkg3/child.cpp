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
#include "dogen/trivial_inheritance/domain/pkg3/child.hpp"
#include "dogen/trivial_inheritance/io/pkg2/parent_io.hpp"

namespace dogen {
namespace trivial_inheritance {
namespace pkg3 {

child::child()
    : prop_1_(static_cast<int>(0)) { }

child::child(
    const int prop_0,
    const dogen::trivial_inheritance::versioned_key& versioned_key,
    const int prop_1)
    : dogen::trivial_inheritance::pkg2::parent(prop_0,
      versioned_key),
      prop_1_(prop_1) { }

void child::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"child\"" << ", "
      << "\"__parent_0__\": ";
    parent::to_stream(s);
    s << ", "
      << "\"prop_1\": " << prop_1_
      << " }";
}

void child::swap(child& other) noexcept {
    parent::swap(other);

    using std::swap;
    swap(prop_1_, other.prop_1_);
}

bool child::operator==(const child& rhs) const {
    return parent::operator==(rhs) &&
        prop_1_ == rhs.prop_1_;
}

child& child::operator=(child other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} } }