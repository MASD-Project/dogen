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
#include "dogen/test_models/cpp_model/types/non_final_orphan.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

non_final_orphan::non_final_orphan()
    : prop_0_(static_cast<int>(0)) { }

non_final_orphan::non_final_orphan(const int prop_0)
    : prop_0_(prop_0) { }

void non_final_orphan::swap(non_final_orphan& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
}

bool non_final_orphan::operator==(const non_final_orphan& rhs) const {
    return prop_0_ == rhs.prop_0_;
}

non_final_orphan& non_final_orphan::operator=(non_final_orphan other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

int non_final_orphan::prop_0() const {
    return prop_0_;
}

void non_final_orphan::prop_0(const int v) {
    prop_0_ = v;
}

} } }
