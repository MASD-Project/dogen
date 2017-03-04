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
#include "dogen/test_models/cpp_model/types/simple_concept_model.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

simple_concept_model::simple_concept_model()
    : prop_0_(static_cast<int>(0)),
      prop_10_(static_cast<int>(0)) { }

simple_concept_model::simple_concept_model(
    const int prop_0,
    const dogen::test_models::cpp_model::value& prop_1,
    const int prop_10)
    : prop_0_(prop_0),
      prop_1_(prop_1),
      prop_10_(prop_10) { }

void simple_concept_model::swap(simple_concept_model& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(prop_1_, other.prop_1_);
    swap(prop_10_, other.prop_10_);
}

bool simple_concept_model::operator==(const simple_concept_model& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        prop_1_ == rhs.prop_1_ &&
        prop_10_ == rhs.prop_10_;
}

simple_concept_model& simple_concept_model::operator=(simple_concept_model other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

int simple_concept_model::prop_0() const {
    return prop_0_;
}

void simple_concept_model::prop_0(const int v) {
    prop_0_ = v;
}

const dogen::test_models::cpp_model::value& simple_concept_model::prop_1() const {
    return prop_1_;
}

dogen::test_models::cpp_model::value& simple_concept_model::prop_1() {
    return prop_1_;
}

void simple_concept_model::prop_1(const dogen::test_models::cpp_model::value& v) {
    prop_1_ = v;
}

void simple_concept_model::prop_1(const dogen::test_models::cpp_model::value&& v) {
    prop_1_ = std::move(v);
}

int simple_concept_model::prop_10() const {
    return prop_10_;
}

void simple_concept_model::prop_10(const int v) {
    prop_10_ = v;
}

} } }
