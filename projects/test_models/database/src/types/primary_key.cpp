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
#include "dogen/test_models/database/types/primary_key.hpp"

namespace dogen {
namespace test_models {
namespace database {

primary_key::primary_key()
    : prop_0_(static_cast<unsigned int>(0)) { }

primary_key::primary_key(
    const unsigned int prop_0,
    const std::string& prop_1)
    : prop_0_(prop_0),
      prop_1_(prop_1) { }

void primary_key::swap(primary_key& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(prop_1_, other.prop_1_);
}

bool primary_key::operator==(const primary_key& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        prop_1_ == rhs.prop_1_;
}

primary_key& primary_key::operator=(primary_key other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

unsigned int primary_key::prop_0() const {
    return prop_0_;
}

void primary_key::prop_0(const unsigned int v) {
    prop_0_ = v;
}

const std::string& primary_key::prop_1() const {
    return prop_1_;
}

std::string& primary_key::prop_1() {
    return prop_1_;
}

void primary_key::prop_1(const std::string& v) {
    prop_1_ = v;
}

void primary_key::prop_1(const std::string&& v) {
    prop_1_ = std::move(v);
}

} } }
