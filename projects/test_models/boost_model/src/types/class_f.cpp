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
#include "dogen/test_models/boost_model/types/class_f.hpp"

namespace dogen {
namespace test_models {
namespace boost_model {

class_f::class_f(class_f&& rhs)
    : prop_0_(std::move(rhs.prop_0_)),
      prop_1_(std::move(rhs.prop_1_)),
      prop_2_(std::move(rhs.prop_2_)),
      prop_3_(std::move(rhs.prop_3_)),
      prop_4_(std::move(rhs.prop_4_)),
      prop_5_(std::move(rhs.prop_5_)) { }

class_f::class_f(
    const boost::gregorian::date& prop_0,
    const boost::posix_time::ptime& prop_1,
    const boost::posix_time::time_duration& prop_2,
    const std::list<boost::gregorian::date>& prop_3,
    const std::list<boost::posix_time::ptime>& prop_4,
    const std::list<boost::posix_time::time_duration>& prop_5)
    : prop_0_(prop_0),
      prop_1_(prop_1),
      prop_2_(prop_2),
      prop_3_(prop_3),
      prop_4_(prop_4),
      prop_5_(prop_5) { }

void class_f::swap(class_f& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(prop_1_, other.prop_1_);
    swap(prop_2_, other.prop_2_);
    swap(prop_3_, other.prop_3_);
    swap(prop_4_, other.prop_4_);
    swap(prop_5_, other.prop_5_);
}

bool class_f::operator==(const class_f& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        prop_1_ == rhs.prop_1_ &&
        prop_2_ == rhs.prop_2_ &&
        prop_3_ == rhs.prop_3_ &&
        prop_4_ == rhs.prop_4_ &&
        prop_5_ == rhs.prop_5_;
}

class_f& class_f::operator=(class_f other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::gregorian::date& class_f::prop_0() const {
    return prop_0_;
}

boost::gregorian::date& class_f::prop_0() {
    return prop_0_;
}

void class_f::prop_0(const boost::gregorian::date& v) {
    prop_0_ = v;
}

void class_f::prop_0(const boost::gregorian::date&& v) {
    prop_0_ = std::move(v);
}

const boost::posix_time::ptime& class_f::prop_1() const {
    return prop_1_;
}

boost::posix_time::ptime& class_f::prop_1() {
    return prop_1_;
}

void class_f::prop_1(const boost::posix_time::ptime& v) {
    prop_1_ = v;
}

void class_f::prop_1(const boost::posix_time::ptime&& v) {
    prop_1_ = std::move(v);
}

const boost::posix_time::time_duration& class_f::prop_2() const {
    return prop_2_;
}

boost::posix_time::time_duration& class_f::prop_2() {
    return prop_2_;
}

void class_f::prop_2(const boost::posix_time::time_duration& v) {
    prop_2_ = v;
}

void class_f::prop_2(const boost::posix_time::time_duration&& v) {
    prop_2_ = std::move(v);
}

const std::list<boost::gregorian::date>& class_f::prop_3() const {
    return prop_3_;
}

std::list<boost::gregorian::date>& class_f::prop_3() {
    return prop_3_;
}

void class_f::prop_3(const std::list<boost::gregorian::date>& v) {
    prop_3_ = v;
}

void class_f::prop_3(const std::list<boost::gregorian::date>&& v) {
    prop_3_ = std::move(v);
}

const std::list<boost::posix_time::ptime>& class_f::prop_4() const {
    return prop_4_;
}

std::list<boost::posix_time::ptime>& class_f::prop_4() {
    return prop_4_;
}

void class_f::prop_4(const std::list<boost::posix_time::ptime>& v) {
    prop_4_ = v;
}

void class_f::prop_4(const std::list<boost::posix_time::ptime>&& v) {
    prop_4_ = std::move(v);
}

const std::list<boost::posix_time::time_duration>& class_f::prop_5() const {
    return prop_5_;
}

std::list<boost::posix_time::time_duration>& class_f::prop_5() {
    return prop_5_;
}

void class_f::prop_5(const std::list<boost::posix_time::time_duration>& v) {
    prop_5_ = v;
}

void class_f::prop_5(const std::list<boost::posix_time::time_duration>&& v) {
    prop_5_ = std::move(v);
}

} } }
