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
#include <ostream>
#include "dogen/test_models/cpp_model/types/child_with_members.hpp"
#include "dogen/test_models/cpp_model/io/parent_without_members_io.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

child_with_members::child_with_members()
    : prop_0_(static_cast<unsigned int>(0)) { }

child_with_members::child_with_members(const unsigned int prop_0)
    : dogen::test_models::cpp_model::parent_without_members(),
      prop_0_(prop_0) { }

void child_with_members::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::cpp_model::child_with_members\"" << ", "
      << "\"__parent_0__\": ";
    dogen::test_models::cpp_model::parent_without_members::to_stream(s);
    s << ", "
      << "\"prop_0\": " << prop_0_
      << " }";
}

void child_with_members::swap(child_with_members& other) noexcept {
    dogen::test_models::cpp_model::parent_without_members::swap(other);

    using std::swap;
    swap(prop_0_, other.prop_0_);
}

bool child_with_members::equals(const dogen::test_models::cpp_model::parent_without_members& other) const {
    const child_with_members* const p(dynamic_cast<const child_with_members* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool child_with_members::operator==(const child_with_members& rhs) const {
    return dogen::test_models::cpp_model::parent_without_members::compare(rhs) &&
        prop_0_ == rhs.prop_0_;
}

child_with_members& child_with_members::operator=(child_with_members other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

unsigned int child_with_members::prop_0() const {
    return prop_0_;
}

void child_with_members::prop_0(const unsigned int v) {
    prop_0_ = v;
}

} } }
