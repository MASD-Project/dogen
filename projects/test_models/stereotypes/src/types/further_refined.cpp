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
#include "dogen/test_models/stereotypes/types/further_refined.hpp"
#include "dogen/test_models/stereotypes/io/base_with_concept_io.hpp"

namespace dogen {
namespace test_models {
namespace stereotypes {

further_refined::further_refined()
    : prop_3_(static_cast<int>(0)),
      prop_1_(static_cast<int>(0)) { }

further_refined::further_refined(
    const int prop_2,
    const std::string& prop_0,
    const int prop_3,
    const int prop_1)
    : dogen::test_models::stereotypes::base_with_concept(
      prop_2,
      prop_0),
      prop_3_(prop_3),
      prop_1_(prop_1) { }

void further_refined::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::test_models::stereotypes::further_refined\"" << ", "
      << "\"__parent_0__\": ";
    dogen::test_models::stereotypes::base_with_concept::to_stream(s);
    s << ", "
      << "\"prop_3\": " << prop_3_ << ", "
      << "\"prop_1\": " << prop_1_
      << " }";
}

void further_refined::swap(further_refined& other) noexcept {
    dogen::test_models::stereotypes::base_with_concept::swap(other);

    using std::swap;
    swap(prop_3_, other.prop_3_);
    swap(prop_1_, other.prop_1_);
}

bool further_refined::equals(const dogen::test_models::stereotypes::base_with_concept& other) const {
    const further_refined* const p(dynamic_cast<const further_refined* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool further_refined::operator==(const further_refined& rhs) const {
    return dogen::test_models::stereotypes::base_with_concept::compare(rhs) &&
        prop_3_ == rhs.prop_3_ &&
        prop_1_ == rhs.prop_1_;
}

further_refined& further_refined::operator=(further_refined other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

int further_refined::prop_3() const {
    return prop_3_;
}

void further_refined::prop_3(const int v) {
    prop_3_ = v;
}

int further_refined::prop_1() const {
    return prop_1_;
}

void further_refined::prop_1(const int v) {
    prop_1_ = v;
}

} } }
