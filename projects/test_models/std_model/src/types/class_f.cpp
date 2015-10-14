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
#include "dogen/test_models/std_model/types/class_f.hpp"

namespace dogen {
namespace test_models {
namespace std_model {

class_f::class_f(
    const std::unordered_map<std::string, std::string>& prop_0,
    const std::unordered_map<std::string, dogen::test_models::std_model::class_a>& prop_1,
    const std::unordered_map<dogen::test_models::std_model::class_a, dogen::test_models::std_model::pkg1::class_c>& prop_2)
    : prop_0_(prop_0),
      prop_1_(prop_1),
      prop_2_(prop_2) { }

void class_f::swap(class_f& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(prop_1_, other.prop_1_);
    swap(prop_2_, other.prop_2_);
}

bool class_f::operator==(const class_f& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        prop_1_ == rhs.prop_1_ &&
        prop_2_ == rhs.prop_2_;
}

class_f& class_f::operator=(class_f other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, std::string>& class_f::prop_0() const {
    return prop_0_;
}

std::unordered_map<std::string, std::string>& class_f::prop_0() {
    return prop_0_;
}

void class_f::prop_0(const std::unordered_map<std::string, std::string>& v) {
    prop_0_ = v;
}

void class_f::prop_0(const std::unordered_map<std::string, std::string>&& v) {
    prop_0_ = std::move(v);
}

const std::unordered_map<std::string, dogen::test_models::std_model::class_a>& class_f::prop_1() const {
    return prop_1_;
}

std::unordered_map<std::string, dogen::test_models::std_model::class_a>& class_f::prop_1() {
    return prop_1_;
}

void class_f::prop_1(const std::unordered_map<std::string, dogen::test_models::std_model::class_a>& v) {
    prop_1_ = v;
}

void class_f::prop_1(const std::unordered_map<std::string, dogen::test_models::std_model::class_a>&& v) {
    prop_1_ = std::move(v);
}

const std::unordered_map<dogen::test_models::std_model::class_a, dogen::test_models::std_model::pkg1::class_c>& class_f::prop_2() const {
    return prop_2_;
}

std::unordered_map<dogen::test_models::std_model::class_a, dogen::test_models::std_model::pkg1::class_c>& class_f::prop_2() {
    return prop_2_;
}

void class_f::prop_2(const std::unordered_map<dogen::test_models::std_model::class_a, dogen::test_models::std_model::pkg1::class_c>& v) {
    prop_2_ = v;
}

void class_f::prop_2(const std::unordered_map<dogen::test_models::std_model::class_a, dogen::test_models::std_model::pkg1::class_c>&& v) {
    prop_2_ = std::move(v);
}

} } }
