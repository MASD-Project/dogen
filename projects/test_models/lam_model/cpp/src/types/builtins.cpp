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
#include "dogen/test_models/lam_model/types/builtins.hpp"

namespace dogen {
namespace test_models {
namespace lam_model {

builtins::builtins()
    : prop_0_(static_cast<char>(0)),
      prop_1_(static_cast<unsigned char>(0)),
      prop_2_(static_cast<std::int8_t>(0)),
      prop_3_(static_cast<std::int16_t>(0)),
      prop_4_(static_cast<std::int32_t>(0)),
      prop_5_(static_cast<std::int64_t>(0)),
      prop_6_(static_cast<int>(0)),
      prop_7_(static_cast<float>(0)),
      prop_8_(static_cast<double>(0)),
      prop_9_(static_cast<bool>(0)) { }

builtins::builtins(
    const char prop_0,
    const unsigned char prop_1,
    const std::int8_t prop_2,
    const std::int16_t prop_3,
    const std::int32_t prop_4,
    const std::int64_t prop_5,
    const int prop_6,
    const float prop_7,
    const double prop_8,
    const bool prop_9)
    : prop_0_(prop_0),
      prop_1_(prop_1),
      prop_2_(prop_2),
      prop_3_(prop_3),
      prop_4_(prop_4),
      prop_5_(prop_5),
      prop_6_(prop_6),
      prop_7_(prop_7),
      prop_8_(prop_8),
      prop_9_(prop_9) { }

void builtins::swap(builtins& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(prop_1_, other.prop_1_);
    swap(prop_2_, other.prop_2_);
    swap(prop_3_, other.prop_3_);
    swap(prop_4_, other.prop_4_);
    swap(prop_5_, other.prop_5_);
    swap(prop_6_, other.prop_6_);
    swap(prop_7_, other.prop_7_);
    swap(prop_8_, other.prop_8_);
    swap(prop_9_, other.prop_9_);
}

bool builtins::operator==(const builtins& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        prop_1_ == rhs.prop_1_ &&
        prop_2_ == rhs.prop_2_ &&
        prop_3_ == rhs.prop_3_ &&
        prop_4_ == rhs.prop_4_ &&
        prop_5_ == rhs.prop_5_ &&
        prop_6_ == rhs.prop_6_ &&
        prop_7_ == rhs.prop_7_ &&
        prop_8_ == rhs.prop_8_ &&
        prop_9_ == rhs.prop_9_;
}

builtins& builtins::operator=(builtins other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

char builtins::prop_0() const {
    return prop_0_;
}

void builtins::prop_0(const char v) {
    prop_0_ = v;
}

unsigned char builtins::prop_1() const {
    return prop_1_;
}

void builtins::prop_1(const unsigned char v) {
    prop_1_ = v;
}

std::int8_t builtins::prop_2() const {
    return prop_2_;
}

void builtins::prop_2(const std::int8_t v) {
    prop_2_ = v;
}

std::int16_t builtins::prop_3() const {
    return prop_3_;
}

void builtins::prop_3(const std::int16_t v) {
    prop_3_ = v;
}

std::int32_t builtins::prop_4() const {
    return prop_4_;
}

void builtins::prop_4(const std::int32_t v) {
    prop_4_ = v;
}

std::int64_t builtins::prop_5() const {
    return prop_5_;
}

void builtins::prop_5(const std::int64_t v) {
    prop_5_ = v;
}

int builtins::prop_6() const {
    return prop_6_;
}

void builtins::prop_6(const int v) {
    prop_6_ = v;
}

float builtins::prop_7() const {
    return prop_7_;
}

void builtins::prop_7(const float v) {
    prop_7_ = v;
}

double builtins::prop_8() const {
    return prop_8_;
}

void builtins::prop_8(const double v) {
    prop_8_ = v;
}

bool builtins::prop_9() const {
    return prop_9_;
}

void builtins::prop_9(const bool v) {
    prop_9_ = v;
}

} } }
