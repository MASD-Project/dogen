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
#include "dogen/std_model/domain/class_g.hpp"

namespace dogen {
namespace std_model {

class_g::class_g(
    const std::unordered_map<dogen::std_model::class_a, std::vector<dogen::std_model::pkg1::class_c> >& prop_0,
    const std::unordered_map<dogen::std_model::pkg1::class_c, std::list<dogen::std_model::class_a> >& prop_1,
    const dogen::std_model::versioned_key& versioned_key)
    : prop_0_(prop_0),
      prop_1_(prop_1),
      versioned_key_(versioned_key) { }

void class_g::swap(class_g& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(prop_1_, other.prop_1_);
    swap(versioned_key_, other.versioned_key_);
}

bool class_g::operator==(const class_g& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        prop_1_ == rhs.prop_1_ &&
        versioned_key_ == rhs.versioned_key_;
}

class_g& class_g::operator=(class_g other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }