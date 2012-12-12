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
#include "dogen/boost_model/types/class_e.hpp"

namespace dogen {
namespace boost_model {

class_e::class_e(class_e&& rhs)
    : prop_0_(std::move(rhs.prop_0_)) { }

class_e::class_e(const boost::variant<int, double>& prop_0)
    : prop_0_(prop_0) { }

void class_e::swap(class_e& other) noexcept {
    using std::swap;
    swap(prop_0_, other.prop_0_);
}

bool class_e::operator==(const class_e& rhs) const {
    return prop_0_ == rhs.prop_0_;
}

class_e& class_e::operator=(class_e other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }