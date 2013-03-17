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
#include "dogen/database/types/no_keys.hpp"

namespace dogen {
namespace database {

no_keys::no_keys()
    : prop_0_(static_cast<int>(0)),
      prop_1_(static_cast<unsigned int>(0)) { }

no_keys::no_keys(
    const int prop_0,
    const unsigned int prop_1,
    const std::string& prop_2,
    const boost::posix_time::ptime& prop_3)
    : prop_0_(prop_0),
      prop_1_(prop_1),
      prop_2_(prop_2),
      prop_3_(prop_3) { }

void no_keys::swap(no_keys& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(prop_1_, other.prop_1_);
    swap(prop_2_, other.prop_2_);
    swap(prop_3_, other.prop_3_);
}

bool no_keys::operator==(const no_keys& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        prop_1_ == rhs.prop_1_ &&
        prop_2_ == rhs.prop_2_ &&
        prop_3_ == rhs.prop_3_;
}

no_keys& no_keys::operator=(no_keys other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

int no_keys::prop_0() const {
    return prop_0_;
}

void no_keys::prop_0(const int v) {
    prop_0_ = v;
}

unsigned int no_keys::prop_1() const {
    return prop_1_;
}

void no_keys::prop_1(const unsigned int v) {
    prop_1_ = v;
}

const std::string& no_keys::prop_2() const {
    return prop_2_;
}

std::string& no_keys::prop_2() {
    return prop_2_;
}

void no_keys::prop_2(const std::string& v) {
    prop_2_ = v;
}

void no_keys::prop_2(const std::string&& v) {
    prop_2_ = std::move(v);
}

const boost::posix_time::ptime& no_keys::prop_3() const {
    return prop_3_;
}

boost::posix_time::ptime& no_keys::prop_3() {
    return prop_3_;
}

void no_keys::prop_3(const boost::posix_time::ptime& v) {
    prop_3_ = v;
}

void no_keys::prop_3(const boost::posix_time::ptime&& v) {
    prop_3_ = std::move(v);
}

} }