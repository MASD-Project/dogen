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
#include <ostream>
#include "dogen/trivial_inheritance/io/parent_outside_versioned_key_io.hpp"
#include "dogen/trivial_inheritance/types/parent_outside.hpp"

namespace dogen {
namespace trivial_inheritance {

parent_outside::parent_outside(const dogen::trivial_inheritance::parent_outside_versioned_key& versioned_key)
    : versioned_key_(versioned_key) { }

void parent_outside::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::trivial_inheritance::parent_outside\"" << ", "
      << "\"versioned_key\": " << versioned_key_
      << " }";
}

void parent_outside::swap(parent_outside& other) noexcept {
    using std::swap;
    swap(versioned_key_, other.versioned_key_);
}

bool parent_outside::compare(const parent_outside& rhs) const {
    return versioned_key_ == rhs.versioned_key_;
}

} }