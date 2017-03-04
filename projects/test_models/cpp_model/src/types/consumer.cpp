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
#include "dogen/test_models/cpp_model/types/consumer.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

consumer::consumer(
    const dogen::test_models::cpp_model::short_primitive& prop0,
    const dogen::test_models::cpp_model::ushort_primitive& prop1,
    const dogen::test_models::cpp_model::long_primitive& prop2,
    const dogen::test_models::cpp_model::ulong_primitive& prop3,
    const dogen::test_models::cpp_model::int_primitive& prop4,
    const dogen::test_models::cpp_model::uint_primitive& prop5,
    const dogen::test_models::cpp_model::char_primitive& prop6,
    const dogen::test_models::cpp_model::uchar_primitive& prop7,
    const dogen::test_models::cpp_model::double_primitive& prop8,
    const dogen::test_models::cpp_model::float_primitive& prop9,
    const dogen::test_models::cpp_model::bool_primitive& prop10)
    : prop0_(prop0),
      prop1_(prop1),
      prop2_(prop2),
      prop3_(prop3),
      prop4_(prop4),
      prop5_(prop5),
      prop6_(prop6),
      prop7_(prop7),
      prop8_(prop8),
      prop9_(prop9),
      prop10_(prop10) { }

void consumer::swap(consumer& other) noexcept {
    using std::swap;
    swap(prop0_, other.prop0_);
    swap(prop1_, other.prop1_);
    swap(prop2_, other.prop2_);
    swap(prop3_, other.prop3_);
    swap(prop4_, other.prop4_);
    swap(prop5_, other.prop5_);
    swap(prop6_, other.prop6_);
    swap(prop7_, other.prop7_);
    swap(prop8_, other.prop8_);
    swap(prop9_, other.prop9_);
    swap(prop10_, other.prop10_);
}

bool consumer::operator==(const consumer& rhs) const {
    return prop0_ == rhs.prop0_ &&
        prop1_ == rhs.prop1_ &&
        prop2_ == rhs.prop2_ &&
        prop3_ == rhs.prop3_ &&
        prop4_ == rhs.prop4_ &&
        prop5_ == rhs.prop5_ &&
        prop6_ == rhs.prop6_ &&
        prop7_ == rhs.prop7_ &&
        prop8_ == rhs.prop8_ &&
        prop9_ == rhs.prop9_ &&
        prop10_ == rhs.prop10_;
}

consumer& consumer::operator=(consumer other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::test_models::cpp_model::short_primitive& consumer::prop0() const {
    return prop0_;
}

dogen::test_models::cpp_model::short_primitive& consumer::prop0() {
    return prop0_;
}

void consumer::prop0(const dogen::test_models::cpp_model::short_primitive& v) {
    prop0_ = v;
}

void consumer::prop0(const dogen::test_models::cpp_model::short_primitive&& v) {
    prop0_ = std::move(v);
}

const dogen::test_models::cpp_model::ushort_primitive& consumer::prop1() const {
    return prop1_;
}

dogen::test_models::cpp_model::ushort_primitive& consumer::prop1() {
    return prop1_;
}

void consumer::prop1(const dogen::test_models::cpp_model::ushort_primitive& v) {
    prop1_ = v;
}

void consumer::prop1(const dogen::test_models::cpp_model::ushort_primitive&& v) {
    prop1_ = std::move(v);
}

const dogen::test_models::cpp_model::long_primitive& consumer::prop2() const {
    return prop2_;
}

dogen::test_models::cpp_model::long_primitive& consumer::prop2() {
    return prop2_;
}

void consumer::prop2(const dogen::test_models::cpp_model::long_primitive& v) {
    prop2_ = v;
}

void consumer::prop2(const dogen::test_models::cpp_model::long_primitive&& v) {
    prop2_ = std::move(v);
}

const dogen::test_models::cpp_model::ulong_primitive& consumer::prop3() const {
    return prop3_;
}

dogen::test_models::cpp_model::ulong_primitive& consumer::prop3() {
    return prop3_;
}

void consumer::prop3(const dogen::test_models::cpp_model::ulong_primitive& v) {
    prop3_ = v;
}

void consumer::prop3(const dogen::test_models::cpp_model::ulong_primitive&& v) {
    prop3_ = std::move(v);
}

const dogen::test_models::cpp_model::int_primitive& consumer::prop4() const {
    return prop4_;
}

dogen::test_models::cpp_model::int_primitive& consumer::prop4() {
    return prop4_;
}

void consumer::prop4(const dogen::test_models::cpp_model::int_primitive& v) {
    prop4_ = v;
}

void consumer::prop4(const dogen::test_models::cpp_model::int_primitive&& v) {
    prop4_ = std::move(v);
}

const dogen::test_models::cpp_model::uint_primitive& consumer::prop5() const {
    return prop5_;
}

dogen::test_models::cpp_model::uint_primitive& consumer::prop5() {
    return prop5_;
}

void consumer::prop5(const dogen::test_models::cpp_model::uint_primitive& v) {
    prop5_ = v;
}

void consumer::prop5(const dogen::test_models::cpp_model::uint_primitive&& v) {
    prop5_ = std::move(v);
}

const dogen::test_models::cpp_model::char_primitive& consumer::prop6() const {
    return prop6_;
}

dogen::test_models::cpp_model::char_primitive& consumer::prop6() {
    return prop6_;
}

void consumer::prop6(const dogen::test_models::cpp_model::char_primitive& v) {
    prop6_ = v;
}

void consumer::prop6(const dogen::test_models::cpp_model::char_primitive&& v) {
    prop6_ = std::move(v);
}

const dogen::test_models::cpp_model::uchar_primitive& consumer::prop7() const {
    return prop7_;
}

dogen::test_models::cpp_model::uchar_primitive& consumer::prop7() {
    return prop7_;
}

void consumer::prop7(const dogen::test_models::cpp_model::uchar_primitive& v) {
    prop7_ = v;
}

void consumer::prop7(const dogen::test_models::cpp_model::uchar_primitive&& v) {
    prop7_ = std::move(v);
}

const dogen::test_models::cpp_model::double_primitive& consumer::prop8() const {
    return prop8_;
}

dogen::test_models::cpp_model::double_primitive& consumer::prop8() {
    return prop8_;
}

void consumer::prop8(const dogen::test_models::cpp_model::double_primitive& v) {
    prop8_ = v;
}

void consumer::prop8(const dogen::test_models::cpp_model::double_primitive&& v) {
    prop8_ = std::move(v);
}

const dogen::test_models::cpp_model::float_primitive& consumer::prop9() const {
    return prop9_;
}

dogen::test_models::cpp_model::float_primitive& consumer::prop9() {
    return prop9_;
}

void consumer::prop9(const dogen::test_models::cpp_model::float_primitive& v) {
    prop9_ = v;
}

void consumer::prop9(const dogen::test_models::cpp_model::float_primitive&& v) {
    prop9_ = std::move(v);
}

const dogen::test_models::cpp_model::bool_primitive& consumer::prop10() const {
    return prop10_;
}

dogen::test_models::cpp_model::bool_primitive& consumer::prop10() {
    return prop10_;
}

void consumer::prop10(const dogen::test_models::cpp_model::bool_primitive& v) {
    prop10_ = v;
}

void consumer::prop10(const dogen::test_models::cpp_model::bool_primitive&& v) {
    prop10_ = std::move(v);
}

} } }
