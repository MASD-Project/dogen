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
#include "dogen/std_model/domain/class_d.hpp"

namespace dogen {
namespace std_model {

class_d::class_d(
    const std::list<std::string>& prop_0,
    const std::list<dogen::std_model::class_a>& prop_1,
    const std::list<dogen::std_model::pkg1::class_c>& prop_2,
    const std::list<unsigned int>& prop_3,
    const std::list<dogen::std_model::class_a>& prop_4,
    const std::list<std::list<unsigned int> >& prop_5,
    const dogen::std_model::versioned_key& versioned_key)
    : prop_0_(prop_0),
      prop_1_(prop_1),
      prop_2_(prop_2),
      prop_3_(prop_3),
      prop_4_(prop_4),
      prop_5_(prop_5),
      versioned_key_(versioned_key) { }

void class_d::swap(class_d& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
    swap(prop_1_, other.prop_1_);
    swap(prop_2_, other.prop_2_);
    swap(prop_3_, other.prop_3_);
    swap(prop_4_, other.prop_4_);
    swap(prop_5_, other.prop_5_);
    swap(versioned_key_, other.versioned_key_);
}

bool class_d::operator==(const class_d& rhs) const {
    return prop_0_ == rhs.prop_0_ &&
        prop_1_ == rhs.prop_1_ &&
        prop_2_ == rhs.prop_2_ &&
        prop_3_ == rhs.prop_3_ &&
        prop_4_ == rhs.prop_4_ &&
        prop_5_ == rhs.prop_5_ &&
        versioned_key_ == rhs.versioned_key_;
}

class_d& class_d::operator=(class_d other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }