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
#include "dogen/test_models/cpp_model/types/second_child_without_members.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

second_child_without_members::second_child_without_members(const int prop_0)
    : dogen::test_models::cpp_model::parent_with_members(prop_0) { }

void second_child_without_members::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::cpp_model::second_child_without_members\"" << ", "
      << "\"__parent_0__\": ";
    dogen::test_models::cpp_model::parent_with_members::to_stream(s);
    s << " }";
}

void second_child_without_members::swap(second_child_without_members& other) noexcept {
    dogen::test_models::cpp_model::parent_with_members::swap(other);

}

bool second_child_without_members::equals(const dogen::test_models::cpp_model::parent_with_members& other) const {
    const second_child_without_members* const p(dynamic_cast<const second_child_without_members* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool second_child_without_members::operator==(const second_child_without_members& rhs) const {
    return dogen::test_models::cpp_model::parent_with_members::compare(rhs);
}

second_child_without_members& second_child_without_members::operator=(second_child_without_members other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} } }
