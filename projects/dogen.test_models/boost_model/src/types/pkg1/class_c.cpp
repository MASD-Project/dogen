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
#include "dogen/test_models/boost_model/types/pkg1/class_c.hpp"

namespace dogen {
namespace test_models {
namespace boost_model {
namespace pkg1 {

class_c::class_c()
    : prop_0_(static_cast<int>(0)) { }

class_c::class_c(
    const int prop_0,
    const std::vector<dogen::test_models::boost_model::class_a>& prop_1)
    : prop_0_(prop_0),
      prop_1_(prop_1) { }

void class_c::swap(class_c& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(prop_1_, other.prop_1_);
}

bool class_c::operator==(const class_c& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        prop_1_ == rhs.prop_1_;
}

class_c& class_c::operator=(class_c other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

int class_c::prop_0() const {
    return prop_0_;
}

void class_c::prop_0(const int v) {
    prop_0_ = v;
}

const std::vector<dogen::test_models::boost_model::class_a>& class_c::prop_1() const {
    return prop_1_;
}

std::vector<dogen::test_models::boost_model::class_a>& class_c::prop_1() {
    return prop_1_;
}

void class_c::prop_1(const std::vector<dogen::test_models::boost_model::class_a>& v) {
    prop_1_ = v;
}

void class_c::prop_1(const std::vector<dogen::test_models::boost_model::class_a>&& v) {
    prop_1_ = std::move(v);
}

} } } }
