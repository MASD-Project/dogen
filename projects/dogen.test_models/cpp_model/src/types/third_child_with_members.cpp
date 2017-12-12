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
#include "dogen/test_models/cpp_model/io/parent_with_members_io.hpp"
#include "dogen/test_models/cpp_model/types/third_child_with_members.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

third_child_with_members::third_child_with_members()
    : prop_1_(static_cast<unsigned int>(0)) { }

third_child_with_members::third_child_with_members(
    const int prop_0,
    const unsigned int prop_1)
    : dogen::test_models::cpp_model::parent_with_members(prop_0),
      prop_1_(prop_1) { }

void third_child_with_members::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::cpp_model::third_child_with_members\"" << ", "
      << "\"__parent_0__\": ";
    dogen::test_models::cpp_model::parent_with_members::to_stream(s);
    s << ", "
      << "\"prop_1\": " << prop_1_
      << " }";
}

void third_child_with_members::swap(third_child_with_members& other) noexcept {
    dogen::test_models::cpp_model::parent_with_members::swap(other);

    using std::swap;
    swap(prop_1_, other.prop_1_);
}

bool third_child_with_members::compare(const third_child_with_members& rhs) const {
    return dogen::test_models::cpp_model::parent_with_members::compare(rhs) &&
        prop_1_ == rhs.prop_1_;
}

unsigned int third_child_with_members::prop_1() const {
    return prop_1_;
}

void third_child_with_members::prop_1(const unsigned int v) {
    prop_1_ = v;
}

} } }
