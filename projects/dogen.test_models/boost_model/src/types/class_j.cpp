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
#include "dogen/test_models/boost_model/types/class_j.hpp"

namespace dogen {
namespace test_models {
namespace boost_model {

class_j::class_j(
    const dogen::test_models::boost_model::ptime_primitive& prop_0,
    const dogen::test_models::boost_model::time_duration_primitive& prop_1,
    const dogen::test_models::boost_model::date_primitive& prop_2)
    : prop_0_(prop_0),
      prop_1_(prop_1),
      prop_2_(prop_2) { }

void class_j::swap(class_j& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(prop_1_, other.prop_1_);
    swap(prop_2_, other.prop_2_);
}

bool class_j::operator==(const class_j& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        prop_1_ == rhs.prop_1_ &&
        prop_2_ == rhs.prop_2_;
}

class_j& class_j::operator=(class_j other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::test_models::boost_model::ptime_primitive& class_j::prop_0() const {
    return prop_0_;
}

dogen::test_models::boost_model::ptime_primitive& class_j::prop_0() {
    return prop_0_;
}

void class_j::prop_0(const dogen::test_models::boost_model::ptime_primitive& v) {
    prop_0_ = v;
}

void class_j::prop_0(const dogen::test_models::boost_model::ptime_primitive&& v) {
    prop_0_ = std::move(v);
}

const dogen::test_models::boost_model::time_duration_primitive& class_j::prop_1() const {
    return prop_1_;
}

dogen::test_models::boost_model::time_duration_primitive& class_j::prop_1() {
    return prop_1_;
}

void class_j::prop_1(const dogen::test_models::boost_model::time_duration_primitive& v) {
    prop_1_ = v;
}

void class_j::prop_1(const dogen::test_models::boost_model::time_duration_primitive&& v) {
    prop_1_ = std::move(v);
}

const dogen::test_models::boost_model::date_primitive& class_j::prop_2() const {
    return prop_2_;
}

dogen::test_models::boost_model::date_primitive& class_j::prop_2() {
    return prop_2_;
}

void class_j::prop_2(const dogen::test_models::boost_model::date_primitive& v) {
    prop_2_ = v;
}

void class_j::prop_2(const dogen::test_models::boost_model::date_primitive&& v) {
    prop_2_ = std::move(v);
}

} } }
