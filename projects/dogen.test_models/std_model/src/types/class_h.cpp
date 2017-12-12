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
#include "dogen/test_models/std_model/types/class_h.hpp"

namespace dogen {
namespace test_models {
namespace std_model {

class_h::class_h(
    const std::unordered_set<dogen::test_models::std_model::class_a>& prop_0,
    const std::unordered_set<dogen::test_models::std_model::pkg1::class_c>& prop_1)
    : prop_0_(prop_0),
      prop_1_(prop_1) { }

void class_h::swap(class_h& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(prop_1_, other.prop_1_);
}

bool class_h::operator==(const class_h& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        prop_1_ == rhs.prop_1_;
}

class_h& class_h::operator=(class_h other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_set<dogen::test_models::std_model::class_a>& class_h::prop_0() const {
    return prop_0_;
}

std::unordered_set<dogen::test_models::std_model::class_a>& class_h::prop_0() {
    return prop_0_;
}

void class_h::prop_0(const std::unordered_set<dogen::test_models::std_model::class_a>& v) {
    prop_0_ = v;
}

void class_h::prop_0(const std::unordered_set<dogen::test_models::std_model::class_a>&& v) {
    prop_0_ = std::move(v);
}

const std::unordered_set<dogen::test_models::std_model::pkg1::class_c>& class_h::prop_1() const {
    return prop_1_;
}

std::unordered_set<dogen::test_models::std_model::pkg1::class_c>& class_h::prop_1() {
    return prop_1_;
}

void class_h::prop_1(const std::unordered_set<dogen::test_models::std_model::pkg1::class_c>& v) {
    prop_1_ = v;
}

void class_h::prop_1(const std::unordered_set<dogen::test_models::std_model::pkg1::class_c>&& v) {
    prop_1_ = std::move(v);
}

} } }
