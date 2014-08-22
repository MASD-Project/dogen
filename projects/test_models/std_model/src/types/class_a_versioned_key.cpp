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
#include "dogen/test_models/std_model/types/class_a_versioned_key.hpp"

namespace dogen {
namespace test_models {
namespace std_model {

class_a_versioned_key::class_a_versioned_key()
    : version_(static_cast<unsigned int>(0)) { }

class_a_versioned_key::class_a_versioned_key(
    const std::string& prop0,
    const unsigned int version)
    : prop0_(prop0),
      version_(version) { }

void class_a_versioned_key::swap(class_a_versioned_key& other) noexcept {
    using std::swap;
    swap(prop0_, other.prop0_);
    swap(version_, other.version_);
}

bool class_a_versioned_key::operator==(const class_a_versioned_key& rhs) const {
    return prop0_ == rhs.prop0_ &&
        version_ == rhs.version_;
}

class_a_versioned_key& class_a_versioned_key::operator=(class_a_versioned_key other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& class_a_versioned_key::prop0() const {
    return prop0_;
}

std::string& class_a_versioned_key::prop0() {
    return prop0_;
}

void class_a_versioned_key::prop0(const std::string& v) {
    prop0_ = v;
}

void class_a_versioned_key::prop0(const std::string&& v) {
    prop0_ = std::move(v);
}

unsigned int class_a_versioned_key::version() const {
    return version_;
}

void class_a_versioned_key::version(const unsigned int v) {
    version_ = v;
}

} } }