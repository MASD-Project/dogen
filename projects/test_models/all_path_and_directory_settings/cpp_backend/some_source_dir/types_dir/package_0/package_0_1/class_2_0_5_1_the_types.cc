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
#include "dogen/test_models/all_path_and_directory_settings/types_dir/package_0/package_0_1/class_2_0_5_0_the_types.hh"

namespace dogen {
namespace test_models {
namespace all_path_and_directory_settings {
namespace package_0 {
namespace package_0_1 {

class_2::class_2()
    : prop_0_(static_cast<int>(0)) { }

class_2::class_2(const int prop_0)
    : prop_0_(prop_0) { }

void class_2::swap(class_2& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
}

bool class_2::operator==(const class_2& rhs) const {
    return prop_0_ == rhs.prop_0_;
}

class_2& class_2::operator=(class_2 other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

int class_2::prop_0() const {
    return prop_0_;
}

void class_2::prop_0(const int v) {
    prop_0_ = v;
}

} } } } }
