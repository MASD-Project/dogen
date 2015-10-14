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
#include "dogen/test_models/database/types/primary_key_2.hpp"

namespace dogen {
namespace test_models {
namespace database {

primary_key_2::primary_key_2()
    : prop_0_(static_cast<unsigned int>(0)) { }

primary_key_2::primary_key_2(const unsigned int prop_0)
    : prop_0_(prop_0) { }

void primary_key_2::swap(primary_key_2& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
}

bool primary_key_2::operator==(const primary_key_2& rhs) const {
    return prop_0_ == rhs.prop_0_;
}

primary_key_2& primary_key_2::operator=(primary_key_2 other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

unsigned int primary_key_2::prop_0() const {
    return prop_0_;
}

void primary_key_2::prop_0(const unsigned int v) {
    prop_0_ = v;
}

} } }
