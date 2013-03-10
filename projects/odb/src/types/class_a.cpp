/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/odb/types/class_a.hpp"

namespace dogen {
namespace odb {

class_a::class_a()
    : prop_0_(static_cast<int>(0)),
      prop_1_(static_cast<unsigned int>(0)) { }

class_a::class_a(
    const int prop_0,
    const unsigned int prop_1,
    const std::string& prop_2,
    const boost::posix_time::ptime& prop_3)
    : prop_0_(prop_0),
      prop_1_(prop_1),
      prop_2_(prop_2),
      prop_3_(prop_3) { }

void class_a::swap(class_a& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(prop_1_, other.prop_1_);
    swap(prop_2_, other.prop_2_);
    swap(prop_3_, other.prop_3_);
}

bool class_a::operator==(const class_a& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        prop_1_ == rhs.prop_1_ &&
        prop_2_ == rhs.prop_2_ &&
        prop_3_ == rhs.prop_3_;
}

class_a& class_a::operator=(class_a other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

int class_a::prop_0() const {
    return prop_0_;
}

void class_a::prop_0(const int v) {
    prop_0_ = v;
}

unsigned int class_a::prop_1() const {
    return prop_1_;
}

void class_a::prop_1(const unsigned int v) {
    prop_1_ = v;
}

const std::string& class_a::prop_2() const {
    return prop_2_;
}

std::string& class_a::prop_2() {
    return prop_2_;
}

void class_a::prop_2(const std::string& v) {
    prop_2_ = v;
}

void class_a::prop_2(const std::string&& v) {
    prop_2_ = std::move(v);
}

const boost::posix_time::ptime& class_a::prop_3() const {
    return prop_3_;
}

boost::posix_time::ptime& class_a::prop_3() {
    return prop_3_;
}

void class_a::prop_3(const boost::posix_time::ptime& v) {
    prop_3_ = v;
}

void class_a::prop_3(const boost::posix_time::ptime&& v) {
    prop_3_ = std::move(v);
}

} }