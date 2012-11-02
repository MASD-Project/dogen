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
#include "dogen/trivial_inheritance/domain/child_of_a_child2.hpp"
#include "dogen/trivial_inheritance/io/third_child_with_members_io.hpp"

namespace dogen {
namespace trivial_inheritance {

child_of_a_child2::child_of_a_child2()
    : prop_2_(static_cast<unsigned int>(0)) { }

child_of_a_child2::child_of_a_child2(
    const int prop_0,
    const dogen::trivial_inheritance::versioned_key& versioned_key,
    const unsigned int prop_1,
    const unsigned int prop_2)
    : dogen::trivial_inheritance::third_child_with_members(prop_0,
      versioned_key,
      prop_1),
      prop_2_(prop_2) { }

void child_of_a_child2::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"child_of_a_child2\"" << ", "
      << "\"__parent_0__\": ";
    third_child_with_members::to_stream(s);
    s << ", "
      << "\"prop_2\": " << prop_2_
      << " }";
}

void child_of_a_child2::swap(child_of_a_child2& other) noexcept {
    third_child_with_members::swap(other);

    using std::swap;
    swap(prop_2_, other.prop_2_);
}

bool child_of_a_child2::equals(const dogen::trivial_inheritance::parent_with_members& other) const {
    const child_of_a_child2* const p(dynamic_cast<const child_of_a_child2* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool child_of_a_child2::operator==(const child_of_a_child2& rhs) const {
    return third_child_with_members::operator==(rhs) &&
        prop_2_ == rhs.prop_2_;
}

child_of_a_child2& child_of_a_child2::operator=(child_of_a_child2 other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }