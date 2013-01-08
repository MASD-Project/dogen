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
#include "dogen/std_model/types/class_a.hpp"

namespace dogen {
namespace std_model {

class_a::class_a(
    const std::string& prop0,
    const std::string& prop1,
    const dogen::std_model::class_a_versioned_key& versioned_key)
    : prop0_(prop0),
      prop1_(prop1),
      versioned_key_(versioned_key) { }

void class_a::swap(class_a& other) noexcept {
    using std::swap;
    swap(prop0_, other.prop0_);
    swap(prop1_, other.prop1_);
    swap(versioned_key_, other.versioned_key_);
}

bool class_a::operator==(const class_a& rhs) const {
    return prop0_ == rhs.prop0_ &&
        prop1_ == rhs.prop1_ &&
        versioned_key_ == rhs.versioned_key_;
}

class_a& class_a::operator=(class_a other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& class_a::prop0() const {
    return prop0_;
}

std::string& class_a::prop0() {
    return prop0_;
}

void class_a::prop0(const std::string& v) {
    prop0_ = v;
}

void class_a::prop0(const std::string&& v) {
    prop0_ = std::move(v);
}

const std::string& class_a::prop1() const {
    return prop1_;
}

std::string& class_a::prop1() {
    return prop1_;
}

void class_a::prop1(const std::string& v) {
    prop1_ = v;
}

void class_a::prop1(const std::string&& v) {
    prop1_ = std::move(v);
}

const dogen::std_model::class_a_versioned_key& class_a::versioned_key() const {
    return versioned_key_;
}

dogen::std_model::class_a_versioned_key& class_a::versioned_key() {
    return versioned_key_;
}

void class_a::versioned_key(const dogen::std_model::class_a_versioned_key& v) {
    versioned_key_ = v;
}

void class_a::versioned_key(const dogen::std_model::class_a_versioned_key&& v) {
    versioned_key_ = std::move(v);
}

} }