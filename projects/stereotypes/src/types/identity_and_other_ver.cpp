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
#include "dogen/stereotypes/types/identity_and_other_ver.hpp"

namespace dogen {
namespace stereotypes {

identity_and_other_ver::identity_and_other_ver()
    : prop_0_(static_cast<int>(0)),
      prop_1_(static_cast<int>(0)),
      version_(static_cast<unsigned int>(0)) { }

identity_and_other_ver::identity_and_other_ver(
    const int prop_0,
    const int prop_1,
    const unsigned int version)
    : prop_0_(prop_0),
      prop_1_(prop_1),
      version_(version) { }

void identity_and_other_ver::swap(identity_and_other_ver& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(prop_1_, other.prop_1_);
    swap(version_, other.version_);
}

bool identity_and_other_ver::operator==(const identity_and_other_ver& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        prop_1_ == rhs.prop_1_ &&
        version_ == rhs.version_;
}

identity_and_other_ver& identity_and_other_ver::operator=(identity_and_other_ver other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

int identity_and_other_ver::prop_0() const {
    return prop_0_;
}

void identity_and_other_ver::prop_0(const int v) {
    prop_0_ = v;
}

int identity_and_other_ver::prop_1() const {
    return prop_1_;
}

void identity_and_other_ver::prop_1(const int v) {
    prop_1_ = v;
}

unsigned int identity_and_other_ver::version() const {
    return version_;
}

void identity_and_other_ver::version(const unsigned int v) {
    version_ = v;
}

} }